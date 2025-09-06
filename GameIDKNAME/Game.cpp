#include "Game.h"

Game::Game()
{
	Init_Var();
	Init_Window();
	Init_Game();
}

Game::~Game()
{
}

void Game::Init_Var()
{
	window = nullptr;
	mouseheld = false;
	inMenu = true;
	paused = false;
	loadGame = false;
	spawninterval = 0.0f;
	dt = dt_clock.restart().asSeconds();
}

void Game::Init_Window()
{
	videomode = VideoMode::getDesktopMode();
	window = new RenderWindow(videomode, "DIKKE GAME", State::Fullscreen);
	window->setVerticalSyncEnabled(true);

	menu = new Menu(GetWindowSize());
}

void Game::Init_Game()
{
	srand(time(NULL));
	grid = new Grid(GetWindowSize());
	player = new Player(GetWindowSize());
}

bool Game::Running()
{
	return window->isOpen();
}

void Game::Pollevents()
{
	while (const std::optional event = window->pollEvent())
	{
		if (event->is<sf::Event::Closed>())
		{
			window->close();
		}
		else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
		{
			switch (keyPressed->scancode)
			{
			case Keyboard::Scancode::Escape:
				SaveGame();
				window->close();
				break;
			case Keyboard::Scancode::P:
				if (!inMenu)
				{
					paused = !paused;
				}
				break;
			}
		}
	}
}

void Game::UpdateDeltaTime()
{
	dt = dt_clock.restart().asSeconds();
}

const Vector2f Game::GetWindowSize()
{
    return static_cast<Vector2f>(this->window->getSize());
}

const Vector2f Game::GetMousePos()
{
	return window->mapPixelToCoords(Mouse::getPosition(*this->window));
}

void Game::LoadGame()
{
	char key = 0xA5;
	std::ifstream file("Saves/save.dat", std::ios::binary);

	// Treat as char*
	char* data_player = reinterpret_cast<char*>(&player->stats);
	size_t dataSize_player = sizeof(Stats);
	// Read file
	file.read(data_player, dataSize_player);

	// Decryption
	for (size_t i = 0; i < dataSize_player; i++)
	{
		data_player[i] ^= key;
	}

	// Place towers
	for (size_t i = 0; i < TOWER_AMOUNT_; i++)
	{
		grid->buildplots[i].build = player->stats.towerstats[i].towerplaced;
		std::cout << grid->buildplots[i].build << std::endl;
		switch (player->stats.towerstats[i].type)
		{
		case 'T':
			grid->towers.push_back(new Turret({ player->stats.towerstats[i].x ,player->stats.towerstats[i].y },
				{ player->stats.towerstats[i].sizeX ,player->stats.towerstats[i].sizeY }, GetWindowSize().y / 2.5));
			grid->towers[i]->level = player->stats.towerstats[i].towerlevel;
			grid->towers[i]->Tower_UpdateDamage();
			break;
		case 'S':
			grid->towers.push_back(new Sniper({ player->stats.towerstats[i].x ,player->stats.towerstats[i].y },
				{ player->stats.towerstats[i].sizeX ,player->stats.towerstats[i].sizeY }, GetWindowSize().y / 0.5));
			grid->towers[i]->level = player->stats.towerstats[i].towerlevel;
			grid->towers[i]->Tower_UpdateDamage();
			break;
		case 'R':
			grid->towers.push_back(new Rocket({ player->stats.towerstats[i].x ,player->stats.towerstats[i].y },
				{ player->stats.towerstats[i].sizeX ,player->stats.towerstats[i].sizeY }, GetWindowSize().y / 5));
			grid->towers[i]->level = player->stats.towerstats[i].towerlevel;
			grid->towers[i]->Tower_UpdateDamage();
			break;
		default:
			break;
		}
	}
}

void Game::SaveGame()
{
	char key = 0xA5;
	std::ofstream file("Saves/save.dat", std::ios::binary);

	for (size_t i = 0; i < TOWER_AMOUNT; i++)
	{
		player->stats.towerstats[i].towerplaced = grid->buildplots[i].build;
		std::cout << grid->buildplots[i].build << std::endl;
	}
	// Get placed towers
	for (size_t i = 0; i < grid->towers.size(); i++)
	{
		player->stats.towerstats[i].x = grid->towers[i]->shape.getPosition().x;
		player->stats.towerstats[i].y = grid->towers[i]->shape.getPosition().y;
		player->stats.towerstats[i].sizeX = grid->towers[i]->shape.getSize().x;
		player->stats.towerstats[i].sizeY = grid->towers[i]->shape.getSize().y;
		player->stats.towerstats[i].type = grid->towers[i]->type;
		player->stats.towerstats[i].towerlevel = grid->towers[i]->level;
	}

	// Treat as char*
	char* data_player = reinterpret_cast<char*>(&player->stats);
	size_t dataSize_player = sizeof(Stats);

	// Encryption
	for (size_t i = 0; i < dataSize_player; i++)
	{
		data_player[i] ^= key;
	}

	// Write to file
	file.write(data_player, dataSize_player);
}

void Game::EntitySpawn()
{
	spawninterval += dt;

	if (spawninterval >= 1.0)
	{
		uint8_t random = rand() % 100;

		switch (random)
		{
		case 99:
			entities.push_back(new Boss(GetWindowSize()));
			break;
		default:
			entities.push_back(new Enemy(GetWindowSize()));
			break;
		}
		spawninterval = 0.0f;
	}
}

void Game::EntityHitDetection(size_t index)
{
	bool entityDied = false;

	// Check if entities have been hit by bullets
	for (size_t i = 0; i < grid->towers.size(); i++)
	{
		for (size_t j = 0; j < grid->towers[i]->bullets.size(); j++)
		{
			if (entities[index]->sprite->getGlobalBounds().contains(grid->towers[i]->bullets[j].shape.getPosition()))
			{
				entities[index]->TakeDmg(grid->towers[i]->bullets[j].damage);
				grid->towers[i]->bullets.erase(grid->towers[i]->bullets.begin() + j);
				
				if (entities[index]->GetHealth() <= 0)
				{
					entityDied = true;
				}
				break;
			}
		}
	}

	if (entityDied)
	{
		switch (entities[index]->GetID())
		{
		case 'E':
			player->stats.resources.copper = player->stats.resources.copper + 1;
			break;
		case 'B':
			player->stats.resources.gold = player->stats.resources.gold + 1;
			break;
		default:
			std::cout << "Error at switch case entities GetID\n";
			break;
		}

		player->Player_Proccess_Loot(entities[index]->DropLoot());

		entities.erase(entities.begin() + index);
	}
}

void Game::EntityEscaped(size_t index)
{
	if (entities[index]->sprite->getPosition().x < 0)
	{
		entities.erase(entities.begin() + index);
		player->stats.health = player->stats.health - 1;
	}
}

void Game::Update()
{
	UpdateDeltaTime();
	Pollevents();

	if (inMenu)
	{
		menu->Menu_Update(GetMousePos(), GetWindowSize(), &inMenu, &loadGame);
		if (loadGame)
		{
			LoadGame();
			loadGame = false;
			inMenu = false;
		}
	}
	else if (paused)
	{
		menu->Menu_Update(GetMousePos(), GetWindowSize(), &inMenu, &loadGame);
	}
	else
	{
		EntitySpawn();

		player->Player_Update(GetWindowSize());
		grid->Grid_Update(GetMousePos(), GetWindowSize(), dt,&player->stats);
		
		for (size_t index = 0; index < entities.size(); index++)
		{
			entities[index]->ChangeDirection(GetWindowSize());
			entities[index]->MoveEnemy(GetWindowSize(),dt);

			EntityHitDetection(index);
		}

		for (size_t index = 0; index < entities.size(); index++)
		{
			EntityEscaped(index);
		}
	}
}

void Game::Render()
{
	window->clear();

	if (inMenu)
	{
		menu->Menu_Render(this->window);
	}
	else if (paused)
	{
		menu->Menu_Render(this->window);
	}
	else
	{
		grid->Grid_Render(this->window);
		player->Player_Render(this->window);

		for (size_t e = 0; e < entities.size(); e++)
		{
			window->draw(*entities[e]->sprite);
		}
	}

	window->display();
}

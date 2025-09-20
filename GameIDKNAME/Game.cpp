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
	quit = false;
	save = false;
	entityLevel = 1;
	entities.reserve(100);
	levelupinterval = 0.f;

	// Font
	if (!font.openFromFile("Fonts/PixeloidSans.ttf"))
	{
		std::cout << "Error: Can't load Font! -> Menu_Init" << std::endl;

	}

	spawninterval = 0.0f;
	dt = dt_clock.restart().asSeconds();
}

void Game::Init_Window()
{
	videomode = VideoMode::getDesktopMode();
	window = new RenderWindow(videomode, "DIKKE GAME", State::Fullscreen);
	window->setVerticalSyncEnabled(true);

	menu = new Menu(GetWindowSize(), &font);
}

void Game::Init_Game()
{
	srand(time(NULL));
	grid = new Grid(GetWindowSize());
	player = new Player(GetWindowSize(), &font);
	settings = new Settings(GetWindowSize(), &font);
	pause = new Pause(GetWindowSize(), &font);
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

	if (quit)
	{
		SaveGame();
		window->close();
	}
	if (save)
	{
		SaveGame();
		save = false;
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

	// Set up entity stats
	entityLevel = player->stats.entitystats.level;

	// Place towers
	for (size_t i = 0; i < TOWER_AMOUNT_; i++)
	{
		grid->buildplots[i].build = player->stats.towerstats[i].towerplaced;

		switch (player->stats.towerstats[i].type)
		{
		case 'T':
			grid->towers.push_back(new Turret({ grid->buildplots[player->stats.towerstats[i].index].shape.getPosition().x,
					grid->buildplots[player->stats.towerstats[i].index].shape.getPosition().y },
				{ grid->buildplots[player->stats.towerstats[i].index].shape.getSize().x,
				grid->buildplots[player->stats.towerstats[i].index].shape.getSize().y },
				GetWindowSize().y / 2.5));
			grid->towers.back()->index = player->stats.towerstats[i].index;
			grid->towers.back()->level = player->stats.towerstats[i].towerlevel;
			grid->towers.back()->Tower_UpdateDamage();
			break;
		case 'S':
			grid->towers.push_back(new Sniper({ grid->buildplots[player->stats.towerstats[i].index].shape.getPosition().x,
					grid->buildplots[player->stats.towerstats[i].index].shape.getPosition().y },
				{ grid->buildplots[player->stats.towerstats[i].index].shape.getSize().x,
				grid->buildplots[player->stats.towerstats[i].index].shape.getSize().y },
				GetWindowSize().y / 0.5));
			grid->towers.back()->index = player->stats.towerstats[i].index;
			grid->towers.back()->level = player->stats.towerstats[i].towerlevel;
			grid->towers.back()->Tower_UpdateDamage();
			break;
		case 'R':
			grid->towers.push_back(new Rocket({ grid->buildplots[player->stats.towerstats[i].index].shape.getPosition().x,
					grid->buildplots[player->stats.towerstats[i].index].shape.getPosition().y },
				{ grid->buildplots[player->stats.towerstats[i].index].shape.getSize().x,
				grid->buildplots[player->stats.towerstats[i].index].shape.getSize().y },
				GetWindowSize().y / 5));
			grid->towers.back()->index = player->stats.towerstats[i].index;
			grid->towers.back()->level = player->stats.towerstats[i].towerlevel;
			grid->towers.back()->Tower_UpdateDamage();
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
	}

	// Get placed towers
	for (size_t i = 0; i < grid->towers.size(); i++)
	{
		player->stats.towerstats[i].index = grid->towers[i]->index;
		player->stats.towerstats[i].type = grid->towers[i]->type;
		player->stats.towerstats[i].towerlevel = grid->towers[i]->level;
	}

	// Get Entity stats
	player->stats.entitystats.level = entityLevel;

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

	// Decryption (for manual saving)
	for (size_t i = 0; i < dataSize_player; i++)
	{
		data_player[i] ^= key;
	}
}

void Game::CreateDmgNumber(int32_t dmg, Vector2f pos)
{
	dmgnumbers.emplace_back();
	dmgnumbers.back().text.emplace(font);
	dmgnumbers.back().text->setCharacterSize(GetWindowSize().x / 100);
	dmgnumbers.back().text->setPosition({ pos.x,pos.y });
	dmgnumbers.back().text->setFillColor(Color::Red);

	std::stringstream ss_dmg;
	ss_dmg << dmg << std::endl;
	dmgnumbers.back().text->setString(ss_dmg.str());
}

void Game::UpdateDmgNumbers()
{
	for (size_t i = 0; i < dmgnumbers.size(); i++)
	{
		dmgnumbers[i].dt += dt;

		if (dmgnumbers[i].dt >= 0.5)
		{
			dmgnumbers.erase(dmgnumbers.begin() + i);
		}
	}
}

void Game::RenderDmgNumbers()
{
	for (size_t i = 0; i < dmgnumbers.size(); i++)
	{
		window->draw(*dmgnumbers[i].text);
	}
}

void Game::EntitySpawn()
{
	spawninterval += dt;

	if (spawninterval >= SPAWN_INTERVAL)
	{
		uint8_t random = rand() % 100;

		if (random >= 95)
		{
			entities.push_back(std::make_unique<Rare>(GetWindowSize(), entityLevel, &font));
		}
		else if (random >= 85)
		{
			entities.push_back(std::make_unique<Magic>(GetWindowSize(), entityLevel, &font));
		}
		else
		{
			entities.push_back(std::make_unique<Normal>(GetWindowSize(), entityLevel, &font));
		}
		spawninterval = 0.0f;
	}
}

void Game::EntityLevelUp()
{
	levelupinterval += dt;

	if (levelupinterval >= LEVELUP_INTERVAL)
	{
		entityLevel++;
		levelupinterval = 0.0f;
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
				entities[index]->Entity_TakeDmg(grid->towers[i]->bullets[j].damage);
				CreateDmgNumber(grid->towers[i]->bullets[j].damage, grid->towers[i]->bullets[j].shape.getPosition());
				grid->towers[i]->bullets.erase(grid->towers[i]->bullets.begin() + j);

				if (entities[index]->Entity_GetHealth() <= 0)
				{
					entityDied = true;
				}
				break;
			}
		}
	}

	if (entityDied)
	{
		switch (entities[index]->Entity_GetID())
		{
		case 'N':
			player->stats.resources.copper += 1;
			player->Player_UpdateLevel(10, GetWindowSize());
			break;
		case 'M':
			player->stats.resources.silver += 1;
			player->Player_UpdateLevel(50, GetWindowSize());
			break;
		case 'R':
			player->stats.resources.gold += 1;
			player->Player_UpdateLevel(200, GetWindowSize());
			break;
		case 'B':
			player->stats.resources.gold += 1;
			player->stats.resources.copper += 15;
			player->Player_UpdateLevel(100, GetWindowSize());
			break;
		default:
			std::cout << "Error at switch case entities GetID\n";
			break;
		}

		player->Player_ProccessLoot(entities[index]->Entity_DropLoot());

		entities[index] = std::move(entities.back());
		entities.pop_back();
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
		pause->Pause_Update(GetMousePos(), GetWindowSize());
		settings->Settings_Update(GetWindowSize(), GetMousePos(), &paused, &save, &quit);
	}
	else
	{
		EntitySpawn();
		EntityLevelUp();
		UpdateDmgNumbers();

		grid->Grid_Update(GetMousePos(), GetWindowSize(), dt, &player->stats);
		settings->Settings_Update(GetWindowSize(), GetMousePos(), &paused, &save, &quit);
		player->Player_Update(GetWindowSize());

		for (size_t index = 0; index < entities.size(); index++)
		{
			entities[index]->Entity_Update(GetWindowSize(), dt);
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
		pause->Pause_Render(this->window);
		settings->Settings_Render(this->window);
	}
	else
	{
		grid->Grid_Render(this->window);
		settings->Settings_Render(this->window);
		player->Player_Render(this->window);

		for (size_t e = 0; e < entities.size(); e++)
		{
			entities[e]->Entity_Render(window);
		}

		RenderDmgNumbers();
	}

	window->display();
}

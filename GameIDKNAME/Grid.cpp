#include "Grid.h"

Grid::Grid(Vector2f windowsize)
{
	Grid_Init(windowsize);
	leftMousepressed = false;
	rightMousepressed = false;
	shaderclock.restart();
}

Grid::~Grid()
{
}

void Grid::Grid_Init(Vector2f windowsize)
{
	// Load Textures
	turretTexture.loadFromFile("Textures/Turret.png");
	sniperTexture.loadFromFile("Textures/Sniper.png");
	rocketTexture.loadFromFile("Textures/Rocket.png");


	// Background sandish
	sand.setFillColor(Color::White);
	sand.setSize(windowsize);
	
	// Wall GREEN TOP
	top.setSize({ windowsize.x,  windowsize.y / 8 });
	top.setPosition({ 0,0 });
	backgroundshapes.push_back(top);

	// Wall GREEN HORIZONTAL SECOND
	second.setSize({ windowsize.x / 2,  windowsize.y / 8 });
	second.setPosition({ windowsize.x / 2,windowsize.y /4}); 
	backgroundshapes.push_back(second);

	// Wall GREEN HORIZONTAL THIRD
	third.setSize({ windowsize.x / 2 - (windowsize.y / 8),  windowsize.y / 8});
	third.setPosition({ windowsize.x / 2 - (windowsize.y / 8),windowsize.y / 2});
	backgroundshapes.push_back(third);

	// Wall GREEN VERTICAL MIDDLE
	vertmid.setSize({ windowsize.y / 8,  windowsize.y / 2 });
	vertmid.setPosition({ (windowsize.x / 2) - (windowsize.y/4),windowsize.y / 8 });
	backgroundshapes.push_back(vertmid);

	// Wall GREEN VERTICAL RIGHT
	vertright.setSize({ windowsize.y / 8,  windowsize.y/2 - (windowsize.y/8)}); 
	vertright.setPosition({ (windowsize.x - (windowsize.y/8)),(windowsize.y / 2)-(windowsize.y /8)});
	backgroundshapes.push_back(vertright);

	// Wall GREEN BOTTOM
	bottom.setSize({ windowsize.x,  windowsize.y/8 });
	bottom.setPosition({0, windowsize.y / 2 + (windowsize.y / 4) });
	backgroundshapes.push_back(bottom);

	// Wall GREEN CUBE
	cube.setSize({ windowsize.x/3, (windowsize.y / 2) }); // size x part goes offscreen but this will do.
	cube.setPosition({ (windowsize.x / 2) - (windowsize.y / 4) - (windowsize.y / 8),(windowsize.y / 4) });
	cube.setOrigin({ cube.getSize().x,0 }); // Makes it easier to have the same size enemy paths.
	backgroundshapes.push_back(cube);

	// BOTTOM SECTION
	section.setSize({ windowsize.x, windowsize.y / 8 }); 
	section.setPosition({ 0, bottom.getPosition().y + (windowsize.y /8)});

	// Building squares
	float k = 0;
	for (size_t s = 0; s <= TOWER_AMOUNT; s++)
	{
		buildplot bottom;
		bottom.build = false;
		bottom.shape.setFillColor(Color::White);
		bottom.shape.setSize({ windowsize.x/TOWER_SIZE, windowsize.x/TOWER_SIZE });
		bottom.shape.setPosition({(windowsize.x/TOWER_START_POS)+k,windowsize.y - (windowsize.y/9)});
		buildplots.push_back(bottom);
		k = k + (windowsize.x / TOWER_SPACE);
	}

	// Tower Options
	for (size_t s = 0; s < TOWER_TYPES; s++)
	{
		RectangleShape option;
		option.setOutlineColor(Color::Black);
		switch (s)
		{
		case 0:
			option.setTexture(&turretTexture);
			break;
		case 1:
			option.setTexture(&rocketTexture);
			break;
		case 2:
			option.setTexture(&sniperTexture);
			break;
		case 3:
			break;
		default:
			break;
		}
		option.setOutlineThickness(windowsize.x / 1000);
		option.setSize({ windowsize.x / 50, windowsize.x / 50 });
		toweroptionsrect.push_back(option);
	}

	Grid_LoadShaders(windowsize);
}

void Grid::Grid_LoadShaders(Vector2f windowsize)
{
	sandshader.loadFromFile("Shaders/path.frag", Shader::Type::Fragment);
	sandshader.setUniform("resolution", windowsize);
	grassshader.loadFromFile("Shaders/grass.frag", Shader::Type::Fragment);
	grassshader.setUniform("resolution", windowsize);
	towerplotshader.loadFromFile("Shaders/buildings.frag", Shader::Type::Fragment);
	towerplotshader.setUniform("resolution", section.getSize());
	bottomsectionshader.loadFromFile("Shaders/buildarea.frag", Shader::Type::Fragment);
	bottomsectionshader.setUniform("resolution", windowsize);
}

void Grid::Grid_SelectTower(Vector2f Mousepos, Vector2f windowsize, size_t index)
{
	TowerOptions = true;
	Index_ = index;

	for (size_t s = 0; s < toweroptionsrect.size(); s++)
	{
		toweroptionsrect[s].setPosition({ buildplots[index].shape.getPosition().x + (s * toweroptionsrect[s].getSize().x),
			buildplots[index].shape.getPosition().y + buildplots[index].shape.getSize().y});
	}
}

void Grid::Grid_UpdateShaders()
{
	float time = shaderclock.getElapsedTime().asSeconds();
	sandshader.setUniform("time", time);
	grassshader.setUniform("time", time);
	towerplotshader.setUniform("time", time);
	bottomsectionshader.setUniform("time", time);
}

void Grid::Grid_Update(Vector2f Mousepos,Vector2f windowsize, float dt, Stats* stats)
{
	Grid_UpdateShaders();

	// Place towers
	if (Mouse::isButtonPressed(Mouse::Button::Left))
	{
		if (!leftMousepressed)
		{
			leftMousepressed = true;
			for (size_t m = 0; m < buildplots.size(); m++)
			{
				if (buildplots[m].shape.getGlobalBounds().contains(Mousepos) && (!buildplots[m].build))
				{
					Grid_SelectTower(Mousepos, windowsize, m);
				}
			}
			if (TowerOptions)
			{
				for (size_t m = 0; m < toweroptionsrect.size(); m++)
				{
					if (toweroptionsrect[m].getGlobalBounds().contains(Mousepos) && (!buildplots[Index_].build))
					{
						switch (m)
						{
						case 0:
							if (stats->resources.copper >= _TURRET_T_PRICE)
							{
								stats->resources.copper = stats->resources.copper - _TURRET_T_PRICE;
								towers.push_back(new Turret(buildplots[Index_].shape.getPosition(), buildplots[Index_].shape.getSize(), windowsize.y / 2.5));
								buildplots[Index_].build = true;
							}
							break;
						case 1:
							if (stats->resources.copper >= _ROCKET_T_PRICE)
							{
								stats->resources.copper = stats->resources.copper - _ROCKET_T_PRICE;
								towers.push_back(new Rocket(buildplots[Index_].shape.getPosition(), buildplots[Index_].shape.getSize(), windowsize.y / 5));
								buildplots[Index_].build = true;
							}
							break;
						case 2:
							if (stats->resources.copper >= _SNIPER_T_PRICE)
							{
								stats->resources.copper = stats->resources.copper - _SNIPER_T_PRICE;
								towers.push_back(new Sniper(buildplots[Index_].shape.getPosition(), buildplots[Index_].shape.getSize(), windowsize.y / 0.5));
								buildplots[Index_].build = true;
							}
							break;
						default:
							break;

						}
					}
				}
			}
		}
	}
	else
	{
		leftMousepressed = false;
	}

	// Upgrade towers
	if (Mouse::isButtonPressed(Mouse::Button::Right))
	{
		if (!rightMousepressed)
		{
			rightMousepressed = true;
			for (size_t m = 0; m < towers.size(); m++)
			{
				if (towers[m]->shape.getGlobalBounds().contains(Mousepos))
				{
					if (stats->resources.copper >= towers[m]->upgradePrice)
					{
						stats->resources.copper = stats->resources.copper - towers[m]->upgradePrice;
						towers[m]->level++;
						towers[m]->Tower_UpdateDamage();
					}
				}
			}

		}
	}
	else
	{
		rightMousepressed = false;
	}

	// Update towers
	for (size_t t = 0; t < towers.size(); t++)
	{
		towers[t]->Tower_Update(windowsize,dt);
	}
}

void Grid::Grid_Render(RenderWindow* window)
{
	// Render yellow background 
	window->draw(sand,&sandshader);

	// Render green areas
	for (size_t r = 0; r < backgroundshapes.size(); r++)
	{
		window->draw(backgroundshapes[r],&grassshader);
	}

	// Bottom section
	window->draw(section, &bottomsectionshader);

	// Render construction sites
	for (size_t r = 0; r < buildplots.size(); r++)
	{
		window->draw(buildplots[r].shape, &towerplotshader);
	}

	// Render tower options 
	if (TowerOptions)
	{
		for (size_t t = 0; t < toweroptionsrect.size(); t++)
		{
			window->draw(toweroptionsrect[t]);
		}
	}

	// Render towers
	for (size_t t = 0; t < towers.size(); t++)
	{
		towers[t]->Tower_Render(window);
	}
}

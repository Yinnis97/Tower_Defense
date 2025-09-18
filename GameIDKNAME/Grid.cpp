#include "Grid.h"

Grid::Grid(Vector2f windowsize)
{
	Grid_Init(windowsize);
	GP_mousepressed = false;
	GU_mousepressed = false;
	towerOptionsPressed = false;
	selectTowerPressed = false;
	showingTowerOptions = false;
	levelOptionsPressed = false;
	levelUpPressed = false;
	showingLevelOptions = false;
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

	level1Texture.loadFromFile("Textures/Upgrade_lvl_1.png");
	level10Texture.loadFromFile("Textures/Upgrade_lvl_10.png");
	level100Texture.loadFromFile("Textures/Upgrade_lvl_100.png");

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
		bottom.shape.setPosition({(windowsize.x/TOWER_START_POS)+k,windowsize.y - (windowsize.y/8)});
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

	// Level Up Options
	for (size_t s = 0; s < LEVEL_UP_OPTIONS; s++)
	{
		RectangleShape leveloption;
		leveloption.setOutlineColor(Color::Black);
		// verander texture
		switch (s)
		{
		case 0:
			leveloption.setTexture(&level1Texture); // 1 level
			break;
		case 1:
			leveloption.setTexture(&level10Texture); // 10 levels
			break;
		case 2:
			leveloption.setTexture(&level100Texture); // 100 levels
			break;
		default:
			break;
		}
		leveloption.setOutlineThickness(windowsize.x / 1000);
		leveloption.setSize({ windowsize.x / 50, windowsize.x / 50 });
		leveloptionsrect.push_back(leveloption);
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

void Grid::Grid_UpdateShaders()
{
	float time = shaderclock.getElapsedTime().asSeconds();
	sandshader.setUniform("time", time);
	grassshader.setUniform("time", time);
	towerplotshader.setUniform("time", time);
	bottomsectionshader.setUniform("time", time);

}

void Grid::Grid_ShowTowerOptions(Vector2f mousepos, Vector2f windowsize)
{
	for (size_t index = 0; index < buildplots.size(); index++)
	{
		if (buildplots[index].shape.getGlobalBounds().contains(mousepos))
		{
			showingTowerOptions = true;
			Index_ = index;
			for (size_t s = 0; s < toweroptionsrect.size(); s++)
			{
				toweroptionsrect[s].setPosition({ buildplots[Index_].shape.getPosition().x + (s * toweroptionsrect[s].getSize().x),
					buildplots[Index_].shape.getPosition().y + buildplots[Index_].shape.getSize().y + (windowsize.x / 1000) });
			}
		}
	}
}

void Grid::Grid_SelectTower(Vector2f mousepos, Vector2f windowsize, Stats* stats)
{
	for (size_t m = 0; m < toweroptionsrect.size(); m++)
	{
		if (toweroptionsrect[m].getGlobalBounds().contains(mousepos) && (!buildplots[Index_].build))
		{
			switch (m)
			{
			case 0:
				if (stats->resources.copper >= _TURRET_T_PRICE)
				{
					stats->resources.copper = stats->resources.copper - _TURRET_T_PRICE;
					towers.push_back(new Turret(buildplots[Index_].shape.getPosition(), buildplots[Index_].shape.getSize(), windowsize.y / 2.5));
					buildplots[Index_].build = true;
					towers.back()->index = Index_;
				}
				break;
			case 1:
				if (stats->resources.copper >= _ROCKET_T_PRICE)
				{
					stats->resources.copper = stats->resources.copper - _ROCKET_T_PRICE;
					towers.push_back(new Rocket(buildplots[Index_].shape.getPosition(), buildplots[Index_].shape.getSize(), windowsize.y / 5));
					buildplots[Index_].build = true;
					towers.back()->index = Index_;
				}
				break;
			case 2:
				if (stats->resources.copper >= _SNIPER_T_PRICE)
				{
					stats->resources.copper = stats->resources.copper - _SNIPER_T_PRICE;
					towers.push_back(new Sniper(buildplots[Index_].shape.getPosition(), buildplots[Index_].shape.getSize(), windowsize.y / 0.5));
					buildplots[Index_].build = true;
					towers.back()->index = Index_;
				}
				break;
			default:
				break;

			}
			showingTowerOptions = false;
		}
	}
}

void Grid::Grid_PlaceTowers(Vector2f mousepos, Vector2f windowsize, Stats* stats)
{
	if (Mouse::isButtonPressed(Mouse::Button::Left))
	{
		if (!GP_mousepressed)
		{
			GP_mousepressed = true;
			for (size_t index = 0; index < buildplots.size(); index++)
			{
				if (buildplots[index].shape.getGlobalBounds().contains(mousepos) && (!buildplots[index].build))
				{
					towerOptionsPressed = true;
				}
			}

			if (showingTowerOptions)
			{
				for (size_t m = 0; m < toweroptionsrect.size(); m++)
				{
					if (toweroptionsrect[m].getGlobalBounds().contains(mousepos))
					{
						selectTowerPressed = true;
					}
				}
			}
		}
	}
	else
	{
		if (towerOptionsPressed)
		{
			Grid_ShowTowerOptions(mousepos, windowsize);
		}
		if (selectTowerPressed)
		{
			Grid_SelectTower(mousepos, windowsize, stats);
		}

		selectTowerPressed = false;
		towerOptionsPressed = false;
		GP_mousepressed = false;
	}
}

void Grid::Grid_ShowLevelUpOptions(Vector2f mousepos, Vector2f windowsize)
{
	for (size_t m = 0; m < towers.size(); m++)
	{
		if (towers[m]->shape.getGlobalBounds().contains(mousepos))
		{
			showingLevelOptions = true;
			TowerIndexLevelUp = m;
			for (size_t s = 0; s < leveloptionsrect.size(); s++)
			{
				leveloptionsrect[s].setPosition({ towers[m]->shape.getPosition().x + (s * leveloptionsrect[s].getSize().x),
					towers[m]->shape.getPosition().y + towers[m]->shape.getSize().y + (windowsize.x / 1000) });
			}
		}
	}
}

void Grid::Grid_SelectLevelUp(Vector2f mousepos, Vector2f windowsize, Stats* stats)
{
	for (size_t m = 0; m < leveloptionsrect.size(); m++)
	{
		if (leveloptionsrect[m].getGlobalBounds().contains(mousepos))
		{
			switch (m)
			{
			case 0:
				if (stats->resources.copper >= towers[TowerIndexLevelUp]->upgradePrice)
				{
					stats->resources.copper = stats->resources.copper - towers[TowerIndexLevelUp]->upgradePrice;
					towers[TowerIndexLevelUp]->level++;
					towers[TowerIndexLevelUp]->Tower_UpdateDamage();
				}
				break;
			case 1:
				if (stats->resources.copper >= (towers[TowerIndexLevelUp]->upgradePrice * 10))
				{
					stats->resources.copper = stats->resources.copper - (towers[TowerIndexLevelUp]->upgradePrice * 10);
					towers[TowerIndexLevelUp]->level+=10;
					towers[TowerIndexLevelUp]->Tower_UpdateDamage();
				}
				break;
			case 2:
				if (stats->resources.copper >= (towers[TowerIndexLevelUp]->upgradePrice * 100))
				{
					stats->resources.copper = stats->resources.copper - (towers[TowerIndexLevelUp]->upgradePrice * 100);
					towers[TowerIndexLevelUp]->level+=100;
					towers[TowerIndexLevelUp]->Tower_UpdateDamage();
				}
				break;
			default:
				break;

			}
			showingLevelOptions = false;
		}
	}
}

void Grid::Grid_UpgradeTowers(Vector2f mousepos, Vector2f windowsize, Stats* stats)
{
	if (Mouse::isButtonPressed(Mouse::Button::Left))
	{
		if (!GU_mousepressed)
		{
			GU_mousepressed = true;
			for (size_t m = 0; m < towers.size(); m++)
			{
				if (towers[m]->shape.getGlobalBounds().contains(mousepos))
				{
					levelOptionsPressed = true;
				}
			}

			if (showingLevelOptions)
			{
				for (size_t m = 0; m < leveloptionsrect.size(); m++)
				{
					if (leveloptionsrect[m].getGlobalBounds().contains(mousepos))
					{
						levelUpPressed = true;
					}
				}
			}

		}
	}
	else
	{
		if (levelOptionsPressed)
		{
			Grid_ShowLevelUpOptions(mousepos, windowsize);
		}
		if (levelUpPressed)
		{
			Grid_SelectLevelUp(mousepos, windowsize, stats);
		}

		levelOptionsPressed = false;
		levelUpPressed = false;
		GU_mousepressed = false;
	}
}

void Grid::Grid_Update(Vector2f mousepos,Vector2f windowsize, float dt, Stats* stats)
{
	Grid_UpdateShaders();
	Grid_PlaceTowers(mousepos, windowsize, stats);
	Grid_UpgradeTowers(mousepos, windowsize, stats);

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
	if (showingTowerOptions)
	{
		for (size_t t = 0; t < toweroptionsrect.size(); t++)
		{
			window->draw(toweroptionsrect[t]);
		}
	}

	// Render level options 
	if (showingLevelOptions)
	{
		for (size_t t = 0; t < leveloptionsrect.size(); t++)
		{
			window->draw(leveloptionsrect[t]);
		}
	}

	// Render towers
	for (size_t t = 0; t < towers.size(); t++)
	{
		towers[t]->Tower_Render(window);
	}
}

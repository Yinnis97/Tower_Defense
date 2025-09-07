#include "Player.h"

Player::Player(Vector2f windowsize)
{
	Player_Init(windowsize);
}

Player::~Player()
{
}

void Player::Player_Init(Vector2f windowsize)
{
	Color color_health(150,0,0,255);
	Color color_copper(184, 115, 51, 255);
	Color color_silver(192,192,192,255);
	Color color_gold(211,175,55,255);
	Color color_blue_sapphire(0,99,213,255);
	Color color_green_sapphire(0,183,10,255);
	Color color_yellow_sapphire(224,232,0,255);
	Color color_orange_sapphire(225, 110, 0,255);

	stats.resources.gold = 1;
	stats.resources.silver = 2;
	stats.resources.copper = 20;
	stats.health = 10;
	stats.xp = 0;
	stats.level = 1;

	stats.resources.blue_sapphire = 0;
	stats.resources.green_sapphire = 0;
	stats.resources.yellow_sapphire = 0;
	stats.resources.orange_sapphire = 0;

	if (!font.openFromFile("Fonts/PixeloidSans.ttf"))
	{
		std::cout << "Error: Can't load Font! -> Player_Init" << std::endl;
	}

	spacing = windowsize.x / 25;
	
	std::stringstream ss_gold, ss_silver, ss_copper, ss_health, ss_b_sapphire, ss_g_sapphire, ss_y_sapphire, ss_o_sapphire;
	ss_gold << "Gold: " << stats.resources.gold << std::endl;
	ss_silver << "Silver: " << stats.resources.silver << std::endl;
	ss_copper << "Copper: " << stats.resources.copper << std::endl;
	ss_health << "Health: " << stats.health << std::endl;

	ss_b_sapphire << "Blue Sapphire: " << stats.resources.blue_sapphire << std::endl;
	ss_g_sapphire << "Green Sapphire: " << stats.resources.green_sapphire << std::endl;
	ss_y_sapphire << "Yellow Sapphire: " << stats.resources.yellow_sapphire << std::endl;
	ss_o_sapphire << "Orange Sapphire: " << stats.resources.orange_sapphire << std::endl;

	gold_text.emplace(font);
	gold_text->setCharacterSize(windowsize.x / 100);
	gold_text->setPosition({spacing, windowsize.y - (windowsize.y/40)});
	gold_text->setFillColor(color_gold);
	gold_text->setString(ss_gold.str());

	silver_text.emplace(font);
	silver_text->setCharacterSize(windowsize.x / 100);
	silver_text->setPosition({ (gold_text->getGlobalBounds().position.x + gold_text->getGlobalBounds().size.x) + spacing, windowsize.y - (windowsize.y / 40) });
	silver_text->setFillColor(color_silver);
	silver_text->setString(ss_silver.str());

	copper_text.emplace(font);
	copper_text->setCharacterSize(windowsize.x / 100);
	copper_text->setPosition({ (silver_text->getGlobalBounds().position.x + silver_text->getGlobalBounds().size.x) + spacing, windowsize.y - (windowsize.y / 40)});
	copper_text->setFillColor(color_copper);
	copper_text->setString(ss_copper.str());

	health_text.emplace(font);
	health_text->setCharacterSize(windowsize.x / 100);
	health_text->setPosition({ (windowsize.x / STATS_POS_INDEX) * 11,windowsize.y - (windowsize.y / 40)});
	health_text->setFillColor(color_health);
	health_text->setString(ss_health.str());

	blue_sapphire_text.emplace(font);
	blue_sapphire_text->setCharacterSize(windowsize.x / 100);
	blue_sapphire_text->setPosition({ (copper_text->getGlobalBounds().position.x + copper_text->getGlobalBounds().size.x) + spacing,windowsize.y - (windowsize.y / 40) });
	blue_sapphire_text->setFillColor(color_blue_sapphire);
	blue_sapphire_text->setString(ss_b_sapphire.str());

	green_sapphire_text.emplace(font);
	green_sapphire_text->setCharacterSize(windowsize.x / 100);
	green_sapphire_text->setPosition({ (blue_sapphire_text->getGlobalBounds().position.x + blue_sapphire_text->getGlobalBounds().size.x) + spacing,windowsize.y - (windowsize.y / 40) });
	green_sapphire_text->setFillColor(color_green_sapphire);
	green_sapphire_text->setString(ss_g_sapphire.str());

	yellow_sapphire_text.emplace(font);
	yellow_sapphire_text->setCharacterSize(windowsize.x / 100);
	yellow_sapphire_text->setPosition({ (green_sapphire_text->getGlobalBounds().position.x + green_sapphire_text->getGlobalBounds().size.x) + spacing,windowsize.y - (windowsize.y / 40) });
	yellow_sapphire_text->setFillColor(color_yellow_sapphire);
	yellow_sapphire_text->setString(ss_y_sapphire.str());

	orange_sapphire_text.emplace(font);
	orange_sapphire_text->setCharacterSize(windowsize.x / 100);
	orange_sapphire_text->setPosition({ (yellow_sapphire_text->getGlobalBounds().position.x + yellow_sapphire_text->getGlobalBounds().size.x) + spacing,windowsize.y - (windowsize.y / 40) });
	orange_sapphire_text->setFillColor(color_orange_sapphire);
	orange_sapphire_text->setString(ss_o_sapphire.str());
}

void Player::Player_ProccessLoot(Vector2u loot)
{
	switch (loot.x)
	{
	case 1:
		stats.resources.blue_sapphire = stats.resources.blue_sapphire + loot.y;
		break;
	case 2:
		stats.resources.green_sapphire = stats.resources.green_sapphire + loot.y;
		break;
	case 3:
		stats.resources.yellow_sapphire = stats.resources.yellow_sapphire + loot.y;
		break;
	case 4:
		stats.resources.orange_sapphire = stats.resources.orange_sapphire + loot.y;
		break;
	}
}

void Player::Player_UpdateLevel(uint32_t xpGained)
{
	stats.xp += xpGained;

	if (stats.xp >= (stats.level * 100))
	{
		stats.level++;
		stats.xp = 0;
	}
	std::cout << "XP: " << stats.xp << " Level: " << stats.level << std::endl;
}

void Player::Player_Update(Vector2f windowsize)
{
	std::stringstream ss_gold, ss_silver, ss_copper, ss_health, ss_b_sapphire, ss_g_sapphire, ss_y_sapphire, ss_o_sapphire; 
	ss_gold << "Gold: " << stats.resources.gold << std::endl;
	ss_silver << "Silver: " << stats.resources.silver << std::endl;
	ss_copper << "Copper: " << stats.resources.copper << std::endl;
	ss_health << "Health: " << stats.health << std::endl;

	ss_b_sapphire << "Blue Sapphire: " << stats.resources.blue_sapphire << std::endl;
	ss_g_sapphire << "Green Sapphire: " << stats.resources.green_sapphire << std::endl;
	ss_y_sapphire << "Yellow Sapphire: " << stats.resources.yellow_sapphire << std::endl;
	ss_o_sapphire << "Orange Sapphire: " << stats.resources.orange_sapphire << std::endl;

	gold_text->setString(ss_gold.str());
	silver_text->setString(ss_silver.str());
	copper_text->setString(ss_copper.str());
	health_text->setString(ss_health.str());

	blue_sapphire_text->setString(ss_b_sapphire.str());
	green_sapphire_text->setString(ss_g_sapphire.str());
	yellow_sapphire_text->setString(ss_y_sapphire.str());
	orange_sapphire_text->setString(ss_o_sapphire.str());
}

void Player::Player_Render(RenderWindow* window)
{
	window->draw(*copper_text);
	window->draw(*silver_text);
	window->draw(*gold_text);
	window->draw(*health_text);
	window->draw(*blue_sapphire_text);
	window->draw(*green_sapphire_text);
	window->draw(*yellow_sapphire_text);
	window->draw(*orange_sapphire_text);
}

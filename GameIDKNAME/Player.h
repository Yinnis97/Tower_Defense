#pragma once
#include <iostream>
#include <sstream> 
#include "math.h"
#include <SFML/Graphics.hpp>

using namespace sf;
#define STATS_POS_INDEX		12
#define TOWER_AMOUNT_		14

struct Stats
{
	uint32_t xp;
	uint32_t xpNeeded;
	uint16_t level;
	int16_t health;

	struct Resources
	{
		uint32_t gold;
		uint32_t silver;
		uint32_t copper;
		uint32_t blue_sapphire;
		uint32_t green_sapphire;
		uint32_t yellow_sapphire;
		uint32_t orange_sapphire;
	} resources;

	struct TowerStats
	{
		size_t index;
		float x;
		float y;
		float sizeX;
		float sizeY;
		char type;
		bool towerplaced;
		uint8_t towerlevel;
	} towerstats[TOWER_AMOUNT_];
};

class Player
{
private:

public:

	Stats stats;
	
	float spacing;
	
	RectangleShape XP_needed;
	RectangleShape XP_current;
	std::optional<Text> level_text;

	std::optional<Text> health_text;
	std::optional<Text> gold_text;
	std::optional<Text> silver_text;
	std::optional<Text> copper_text;

	std::optional<Text> blue_sapphire_text;
	std::optional<Text> green_sapphire_text;
	std::optional<Text> yellow_sapphire_text;
	std::optional<Text> orange_sapphire_text;

	Player(Vector2f windowsize, Font* font);
	~Player();

	void Player_Init(Vector2f windowsize, Font* font);

	void Player_ProccessLoot(Vector2u loot);
	void Player_UpdateLevel(uint32_t xpGained, Vector2f windowsize);

	void Player_Update(Vector2f windowsize);
	void Player_Render(RenderWindow* window);
};


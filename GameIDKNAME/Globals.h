#pragma once
#include <iostream>
#include <sstream> 
#include <fstream>
#include "math.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// Namespace for SFML
using namespace sf;

/*
  -----------------------------
  ALL DEFINES ARE DEFINED HERE.
  -----------------------------
*/

// Used to define the pos of player stats
#define _STATS_POS_INDEX			12

// Used to define the size of the towers
#define _TOWER_SIZE					30

// Used to define the starting pos of towers
#define _TOWER_START_POS			50

// Used to define the spacing between each tower
#define _TOWER_SPACE				14

// Maximum amount of towers that can be placed
#define _TOWER_AMOUNT				14

// Amount of tower types
#define _TOWER_TYPES				3

// Amount of options to level a tower (x1,x10,x100)
#define _LEVEL_UP_OPTIONS			3

// Entity spawns and level up intervals
#define _SPAWN_INTERVAL				0.8
#define _LEVELUP_INTERVAL			20
#define _BOSS_SPAWN_INTERVAL		40

// Prices still up for change
#define _TURRET_T_PRICE				10
#define _ROCKET_T_PRICE				20
#define _SNIPER_T_PRICE				30


/*
	----------------------------
	ALL STRUCTS ARE DEFINED HERE
	----------------------------
*/

// Struct for all player data : used to save all data from player, tower placements and entity stats.
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
		char type;
		bool towerplaced;
		uint8_t towerlevel;
	} towerstats[_TOWER_AMOUNT];

	struct EntityStats
	{
		int level;
		float levelupinterval;
		float bossspawninterval;
	} entitystats;
};


// Struct for damage numbers : uses dt to show damage number text for a short time.
struct DamageNumbers
{
	std::optional<Text> text;
	float dt = 0.0;
};


// Struct for all the building spots for towers.
struct buildplot
{
	RectangleShape shape;
	bool build;
	char type;
};
#pragma once
#include "Globals.h"

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


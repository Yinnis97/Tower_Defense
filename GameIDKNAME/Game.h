#pragma once
#include <iostream>
#include <fstream>
#include "math.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Entity.h"
#include "Boss.h"
#include "Normal.h"
#include "Magic.h"
#include "Rare.h"
#include "Grid.h"
#include "Player.h"
#include "Menu.h"
#include "Settings.h"
#include "Pause.h"

using namespace sf;

#define SPAWN_INTERVAL 0.5
#define LEVELUP_INTERVAL 20

struct DamageNumbers
{
	std::optional<Text> text;
	float dt = 0.0;
};

class Game
{

private:
	RenderWindow *window;
	VideoMode videomode;
	std::vector<std::unique_ptr<Entity>> entities;
	bool mouseheld;
	float spawninterval;

	Grid* grid;
	Player* player;
	Menu* menu;
	Settings* settings;
	Pause* pause;

	Clock dt_clock;
	float dt;
	std::vector<DamageNumbers> dmgnumbers;
	int entityLevel;
	float levelupinterval;

public:
	bool loadGame;
	bool inMenu;
	bool paused;
	bool quit;
	bool save;

	Font font;

	Game();
	~Game();

	void Init_Var();
	void Init_Window();
	void Init_Game();

	bool Running();
	void Pollevents();
	void UpdateDeltaTime();

	const Vector2f GetWindowSize();
	const Vector2f GetMousePos();

	void LoadGame();
	void SaveGame();

	void CreateDmgNumber(int32_t dmg, Vector2f pos);
	void UpdateDmgNumbers();
	void RenderDmgNumbers();

	void EntitySpawn();
	void EntityLevelUp();
	void EntityHitDetection(size_t index);
	void EntityEscaped(size_t index);

	void Update();
	void Render();

};


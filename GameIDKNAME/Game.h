#pragma once
#include "Globals.h"

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


class Game
{

private:
	RenderWindow *window;
	VideoMode videomode;
	bool mouseheld;

	std::vector<std::unique_ptr<Entity>> entities;
	std::vector<DamageNumbers> dmgnumbers;
	int entityLevel;

	float spawninterval;
	float levelupinterval;
	float bossspawninterval;
	bool bossSpawned;

	Grid* grid;
	Player* player;
	Menu* menu;
	Settings* settings;
	Pause* pause;

	Clock dt_clock;
	float dt;

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


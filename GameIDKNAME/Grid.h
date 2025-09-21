#pragma once
#include "Globals.h"

#include "Tower.h"
#include "Rocket.h"
#include "Sniper.h"
#include "Turret.h"
#include "Player.h"

class Grid
{
private:
	bool GP_mousepressed;
	bool GU_mousepressed;

public:
	std::vector<Tower*> towers;
	std::vector<RectangleShape> backgroundshapes;
	std::vector<buildplot> buildplots;
	std::vector<RectangleShape> toweroptionsrect;
	std::vector<RectangleShape> leveloptionsrect;

	RectangleShape top;
	RectangleShape second;
	RectangleShape third;
	RectangleShape vertmid;
	RectangleShape vertright;
	RectangleShape bottom;
	RectangleShape cube;

	RectangleShape section;
	RectangleShape sand;
	RectangleShape water;

	Texture turretTexture;
	Texture sniperTexture;
	Texture rocketTexture;

	Texture level1Texture;
	Texture level10Texture;
	Texture level100Texture;

	bool towerOptionsPressed;
	bool selectTowerPressed;
	bool showingTowerOptions;

	bool levelOptionsPressed;
	bool levelUpPressed;
	bool showingLevelOptions;

	size_t Index_;
	size_t TowerIndexLevelUp;

	Clock shaderclock;

	Shader sandshader;
	Shader grassshader;
	Shader towerplotshader;
	Shader bottomsectionshader;

	Grid(Vector2f windowsize);
	~Grid();

	void Grid_Init(Vector2f windowsize);

	void Grid_LoadShaders(Vector2f windowsize);
	void Grid_UpdateShaders();

	void Grid_ShowTowerOptions(Vector2f mousepos, Vector2f windowsize);
	void Grid_SelectTower(Vector2f mousepos, Vector2f windowsize, Stats* stats);
	void Grid_PlaceTowers(Vector2f mousepos, Vector2f windowsize, Stats* stats);
	
	void Grid_ShowLevelUpOptions(Vector2f mousepos, Vector2f windowsize);
	void Grid_SelectLevelUp(Vector2f mousepos, Vector2f windowsize, Stats* stats);
	void Grid_UpgradeTowers(Vector2f mousepos, Vector2f windowsize, Stats* stats);

	void Grid_Update(Vector2f Mousepos, Vector2f windowsize, float dt, Stats* stats);
	void Grid_Render(RenderWindow* window);
};


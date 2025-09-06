#pragma once
#include <iostream>
#include "math.h"
#include <SFML/Graphics.hpp>
#include "Tower.h"
#include "Rocket.h"
#include "Sniper.h"
#include "Turret.h"

using namespace sf;

#define TOWER_AMOUNT		15
#define TOWER_SIZE			30
#define TOWER_START_POS		50
#define TOWER_SPACE			14
#define TOWER_TYPES			3

struct buildplot
{
	RectangleShape shape;
	bool build;
	char type;
};

class Grid
{
private:
	bool mousepressed;

public:
	std::vector<Tower*> towers;

	std::vector<RectangleShape> backgroundshapes;
	std::vector<buildplot> buildplots;
	std::vector<RectangleShape> toweroptionsrect;

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

	bool TowerOptions;
	size_t Index_;

	Clock shaderclock;

	Shader sandshader;
	Shader grassshader;
	Shader towerplotshader;
	Shader bottomsectionshader;

	Grid(Vector2f windowsize);
	~Grid();

	void Grid_Init(Vector2f windowsize);
	void Grid_LoadShaders(Vector2f windowsize);
	void Grid_SelectTower(Vector2f Mousepos, Vector2f windowsize, size_t index);
	void Grid_UpdateShaders();
	void Grid_Update(Vector2f Mousepos, Vector2f windowsize, float dt);
	void Grid_Render(RenderWindow* window);
};


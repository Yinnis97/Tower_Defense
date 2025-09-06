#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Bullet.h"
#include <iostream>
#include "math.h"
using namespace sf;

class Tower
{
private:
	Vector2f center;
	Vector2f direction;
	Vector2f position;
	Vector2f size;
	uint8_t damage;
	float firerate;
	float speed;
	float radius;
	Clock clock;
	float lastshot;

public:
	char type;
	RectangleShape shape;
	Texture texture;
	std::vector<Bullet> bullets;

	Tower(Vector2f pos, Vector2f size, float spd, char type, float firerate, uint8_t dmg, float rds) :
		position(pos), size(size), speed(spd), type(type), firerate(firerate), damage(dmg), radius(rds) {}

	~Tower();
	virtual void Tower_Init(Vector2f pos, Vector2f size) = 0;

	void Tower_Init_Variables(Vector2f pos, Vector2f size);
	void Tower_Shoot(Vector2f windowsize, float dt);
	void Tower_Update(Vector2f windowsize, float dt);
	void Tower_Render(RenderWindow* window);
};

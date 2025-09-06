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
	uint32_t damage;
	float firerate;
	float speed;
	float radius;
	Clock clock;
	float lastshot;

public:
	uint32_t upgradePrice;
	char type;
	uint8_t level;
	RectangleShape shape;
	Texture texture;
	std::vector<Bullet> bullets;

	Tower(Vector2f pos, Vector2f size, float spd, char type, float firerate, uint32_t dmg, float rds, uint32_t upPrice) :
		position(pos), size(size), speed(spd), type(type), firerate(firerate), damage(dmg), radius(rds), upgradePrice(upPrice), lastshot(0.0), level(1) {}

	~Tower();
	virtual void Tower_Init(Vector2f pos, Vector2f size) = 0;

	void Tower_Init_Variables(Vector2f pos, Vector2f size);
	void Tower_UpdateDamage();
	void Tower_Shoot(Vector2f windowsize, float dt);
	void Tower_Update(Vector2f windowsize, float dt);
	void Tower_Render(RenderWindow* window);
};

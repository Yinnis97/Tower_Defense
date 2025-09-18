#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;


class Bullet
{
public:
	CircleShape shape;
	int32_t damage;
	float speed;
	bool hitenemy;

	Bullet(float radius, Vector2f windowsize, int32_t dmg, float spd)
		: speed(spd), damage(dmg)
	{

		shape.setRadius(radius*(windowsize.x/1000));
		shape.setFillColor(Color::Black);
		shape.setOutlineThickness(windowsize.x/3000);
		shape.setOutlineColor(Color::Red);
		hitenemy = false;
	}
};

#include "Tower.h"

Tower::~Tower()
{
}

void Tower::Tower_Init_Variables(Vector2f pos, Vector2f size)
{
	shape.setSize(size);
	shape.setPosition(pos);
	shape.setTexture(&texture);
	center = shape.getPosition() + Vector2f{ size.x/2, size.y/2 };
	clock.restart();
}

void Tower::Tower_UpdateDamage()
{
	damage = damage + (level);
	std::cout << static_cast<uint16_t>(damage) << std::endl;
}

void Tower::Tower_Shoot(Vector2f windowsize, float dt)
{
	lastshot += dt;

	if (lastshot >= firerate)
	{
		bullets.push_back(Bullet(radius, windowsize, damage, speed));
		bullets.back().shape.setOrigin(bullets.back().shape.getGeometricCenter());
		bullets.back().shape.setPosition({center.x,center.y});
		
		lastshot = 0.0f;
	}
}

void Tower::Tower_Update(Vector2f windowsize, float dt)
{
	Tower_Shoot(windowsize, dt);

	// Move bullets according to bullet speed
	for (size_t i = 0; i < bullets.size(); i++)
	{
		bullets[i].shape.move({ 0,-bullets[i].speed*dt});
	}

	// Erase bullets when out off screen
	for (size_t i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].shape.getPosition().x > windowsize.x || bullets[i].shape.getPosition().x < 0
			|| bullets[i].shape.getPosition().y > windowsize.y || bullets[i].shape.getPosition().y < 0)
		{
			bullets.erase(bullets.begin() + i);
		}
	}
}

void Tower::Tower_Render(RenderWindow* window)
{
	for (size_t i = 0; i < bullets.size(); i++)
	{
		window->draw(bullets[i].shape);
	}
	window->draw(shape);
}

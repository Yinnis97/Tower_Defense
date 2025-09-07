#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;


class Entity
{
private:
	int8_t health;
	int8_t maxhealth;
	char ID;

public:

	Entity(const Vector2f windowsize, int hp, char type) : startpos(windowsize), health(hp), ID(type), direction(0), lastdir(6,false), ms(10), maxhealth(hp)
	{
		Entity_Init(windowsize);
	}

	const Vector2f startpos;
	Texture texture;
	std::optional<Sprite> sprite;

	RectangleShape fullhealthbar;
	RectangleShape healthbar;

	float ms;
	size_t direction;
	std::vector<bool> lastdir;

	virtual void Entity_InitSprite(Vector2f windowsize) = 0;
	void Entity_Init(Vector2f windowsize);

	int8_t Entity_GetHealth();
	char Entity_GetID();

	void Entity_TakeDmg(int8_t dmg);
	void Entity_UpdateHealthBar(Vector2f windowsize);

	Vector2u Entity_DropLoot();
	void Entity_ChangeDirection(Vector2f windowsize);
	void Entity_Move(Vector2f windowsize, float dt);

	void Entity_Update(Vector2f windowsize, float dt);
};


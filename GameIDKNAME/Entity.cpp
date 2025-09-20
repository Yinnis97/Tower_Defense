#include "Entity.h"


void Entity::Entity_Init(Vector2f windowsize, Font* font)
{
	Color lvltxtclr(100, 100, 100, 255);

	fullhealthbar.setFillColor(lvltxtclr);
	fullhealthbar.setSize({ windowsize.x / 30, windowsize.y / 120 });
	healthbar.setFillColor(Color::Red);
	healthbar.setSize({ windowsize.x / 30, windowsize.y / 120 });

	fullhealthbar.setOrigin({ fullhealthbar.getSize().x / 2,fullhealthbar.getSize().y/2 });
	healthbar.setOrigin(fullhealthbar.getOrigin());

	level_text.emplace(*font);
	level_text->setCharacterSize(windowsize.x / 150);
	level_text->setFillColor(lvltxtclr);

	Entity_UpdateLevel(windowsize);
}

int32_t Entity::Entity_GetHealth()
{
    return this->health;
}

char Entity::Entity_GetID()
{
    return this->ID;
}

void Entity::Entity_TakeDmg(int32_t dmg)
{
    this->health = this->health - dmg;
}

void Entity::Entity_UpdateUI(Vector2f windowsize)
{
	// Healthbar
	float r = float(health) / float(maxhealth);
	healthbar.setSize({ fullhealthbar.getSize().x * r, fullhealthbar.getSize().y });

	fullhealthbar.setPosition({ sprite->getPosition().x,sprite->getPosition().y - (sprite->getGlobalBounds().size.y/1.7f) });
	healthbar.setPosition(fullhealthbar.getPosition());

	// Level
	std::stringstream ss_lvl;
	ss_lvl << level << std::endl;

	level_text->setPosition({ fullhealthbar.getPosition().x + (fullhealthbar.getSize().x / 1.8f), fullhealthbar.getPosition().y });
	level_text->setString(ss_lvl.str());
}

void Entity::Entity_UpdateLevel(Vector2f windowsize)
{
	// Up for change
	maxhealth = basehealth * (level);
	health = maxhealth;
}

Vector2u Entity::Entity_DropLoot()
{
	uint8_t random = (rand() % 100) + 1; // 1 - 100
	uint8_t amount = (rand() % 10) + 1; // 1 - 10
	//std::cout << ID << "  " << static_cast<uint16_t>(random) << std::endl;

	if (ID == 'N') // Normal
	{
		if(random == 1) // 1%
		{
			return { 2,amount };
		}
		else if (random <= 6) // 5%
		{
			return { 3,amount };
		}
		else if (random <= 26) // 20%
		{
			return { 4,amount };
		}

		return { 0,0 };
	}
	else if (ID == 'M') // Magic
	{
		if (random == 1) // 1%
		{
			return { 1,amount };
		}
		else if (random <= 6) // 5%
		{
			return { 2,amount };
		}
		else if (random <= 26) // 20%
		{
			return { 3,amount };
		}

		return { 0,0 };
	}
	else if (ID == 'R') // Rare
	{
		if (random <= 20) // 20%
		{
			return { 1,amount };
		}
		else // 80%
		{
			return { 2,amount };
		}

		return { 0,0 };
	}
	else if (ID == 'B') // Boss
	{
		if (random <= 50) // 50%
		{
			return { 1,amount };
		}
		else // 50%
		{
			return { 2,amount };
		}
		return { 0,0 };
	}
	else
	{
		std::cout << "Error Entity::DropLoot" << std::endl;
		return { 0,0 };
	}
}

void Entity::Entity_ChangeDirection(Vector2f windowsize)
{
	// 0 = left , 1 = down , 2 = up, 3 = right
	// A horrible way of doing this.

	if ((sprite->getPosition().x) <= (windowsize.x / 2) - (windowsize.y / 16) && !lastdir[0])
	{
		direction = 1;
		lastdir[0] = true;
	}
	else if (sprite->getPosition().y >= (windowsize.y / 2) - (windowsize.y/16) && !lastdir[1])
	{
		direction = 3;
		lastdir[1] = true;
	}
	else if (sprite->getPosition().x >= (windowsize.x - (windowsize.y / 8) - (windowsize.y /16)) && !lastdir[2] && lastdir[1])
	{
		direction = 1;
		lastdir[2] = true;
	}
	else if (sprite->getPosition().y >= (windowsize.y - (windowsize.y / 4) - (windowsize.y / 16)) && !lastdir[3] && lastdir[2])
	{
		direction = 0;
		lastdir[3] = true;
	}
	else if (sprite->getPosition().x <= (windowsize.x/2 - windowsize.y/4 - windowsize.y/16) && !lastdir[4] && lastdir[3])
	{
		direction = 2;
		lastdir[4] = true;
	}
	else if (sprite->getPosition().y <= (windowsize.y/8 + windowsize.y/16) && !lastdir[5] && lastdir[4])
	{
		direction = 0;
		lastdir[5] = true;
	}

}

void Entity::Entity_Move(Vector2f windowsize,float dt)
{
	switch (direction)
	{
	case 0:
		sprite->move({ -(windowsize.x / ms)*dt, 0 });
		break;
	case 1:
		sprite->move({ 0, (windowsize.x / ms)*dt });
		break;
	case 2:
		sprite->move({ 0, -(windowsize.x / ms)*dt });
		break;
	case 3:
		sprite->move({ (windowsize.x / ms)*dt, 0 });
		break;
	default:
		std::cout << "Error Switch case Game::Update -> Entities direction" << std::endl;
		break;
	}
}

void Entity::Entity_Update(Vector2f windowsize, float dt)
{
	Entity_ChangeDirection(windowsize);
	Entity_Move(windowsize, dt);
	Entity_UpdateUI(windowsize);
}

void Entity::Entity_Render(RenderWindow* window)
{
	window->draw(*sprite);
	window->draw(fullhealthbar);
	window->draw(healthbar);
	window->draw(*level_text);
}


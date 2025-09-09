#pragma once
#include "Entity.h"
class Enemy :
    public Entity
{
private:

public:
    Enemy(Vector2f windowsize, uint16_t lvl, int8_t hp = 2, char type = 'E') : Entity(windowsize, lvl, hp, type)
    {
        this->Entity_InitSprite(windowsize);
    }

    void Entity_InitSprite(Vector2f windowsize) override
    {
        texture.loadFromFile("Textures/baby-export.png");
        sprite.emplace(texture);
        auto x = windowsize.x / 2000;
 
        sprite->setOrigin({ sprite->getGlobalBounds().getCenter() });
        sprite->setScale({ x, x });
        sprite->setPosition({ startpos.x,((startpos.y / 8) + (startpos.y / 16)) });
    }
};


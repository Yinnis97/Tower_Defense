#pragma once
#include "Entity.h"

class Boss :
    public Entity
{
private:

public:
    Boss(const Vector2f windowsize, uint16_t lvl, int8_t hp = 10, char type = 'B') : Entity(windowsize, lvl, hp, type)
    {
        this->Entity_InitSprite(windowsize);
    }

    void Entity_InitSprite(Vector2f windowsize) override
    {
        texture.loadFromFile("Textures/Boss.png");
        sprite.emplace(texture);
        auto x = windowsize.x / 2000;
        sprite->setOrigin({ sprite->getGlobalBounds().getCenter() });
        sprite->setScale({ x, x });
        sprite->setPosition({ startpos.x,((startpos.y / 8) + (startpos.y / 16)) });
    }
};


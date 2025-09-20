#pragma once
#include "Entity.h"

class Normal :
    public Entity
{
private:

public:
    Normal(Vector2f windowsize, uint16_t lvl, Font* font, int32_t hp = 2, char type = 'N') : Entity(windowsize, lvl, hp, type, font)
    {
        this->Entity_InitSprite(windowsize);
    }

    void Entity_InitSprite(Vector2f windowsize) override
    {
        static_cast<void>(texture.loadFromFile("Textures/Normal_Entity.png"));
        sprite.emplace(texture);
        auto x = windowsize.x / 2000;

        sprite->setOrigin({ sprite->getGlobalBounds().getCenter() });
        sprite->setScale({ x, x });
        sprite->setPosition({ startpos.x,((startpos.y / 8) + (startpos.y / 16)) });
    }
};


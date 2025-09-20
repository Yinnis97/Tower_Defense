#pragma once
#include "Entity.h"
class Rare :
    public Entity
{
private:

public:
    Rare(Vector2f windowsize, uint16_t lvl, Font* font, int32_t hp = 10, char type = 'R') : Entity(windowsize, lvl, hp, type, font)
    {
        this->Entity_InitSprite(windowsize);
    }

    void Entity_InitSprite(Vector2f windowsize) override
    {
        static_cast<void>(texture.loadFromFile("Textures/Rare_Entity.png"));
        sprite.emplace(texture);
        auto x = windowsize.x / 2000;

        sprite->setOrigin({ sprite->getGlobalBounds().getCenter() });
        sprite->setScale({ x, x });
        sprite->setPosition({ startpos.x,((startpos.y / 8) + (startpos.y / 16)) });
    }
};


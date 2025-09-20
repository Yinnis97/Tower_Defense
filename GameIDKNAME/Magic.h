#pragma once
#include "Entity.h"
class Magic :
    public Entity
{
private:

public:
    Magic(Vector2f windowsize, uint16_t lvl, Font* font, int32_t hp = 5, char type = 'M') : Entity(windowsize, lvl, hp, type, font)
    {
        this->Entity_InitSprite(windowsize);
    }

    void Entity_InitSprite(Vector2f windowsize) override
    {
        static_cast<void>(texture.loadFromFile("Textures/Magic_Entity.png"));
        sprite.emplace(texture);
        auto x = windowsize.x / 2000;

        sprite->setOrigin({ sprite->getGlobalBounds().getCenter() });
        sprite->setScale({ x, x });
        sprite->setPosition({ startpos.x,((startpos.y / 8) + (startpos.y / 16)) });
    }
};


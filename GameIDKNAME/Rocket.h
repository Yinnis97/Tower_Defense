#pragma once
#include "Tower.h"

class Rocket :
	public Tower
{
private:
public:
    Rocket(Vector2f pos, Vector2f size, float speed, char type = 'R', float firerate = 2, int32_t dmg = 8, float rds = 9, uint32_t upPrice = 20)
        : Tower(pos, size, speed, type, firerate, dmg, rds, upPrice)
    {
        Tower_Init(pos,size);
    }

    void Tower_Init(Vector2f pos, Vector2f size) override
    {
        if (!texture.loadFromFile("Textures/Rocket.png"))
        {
            std::cout << "Error Loading Texture" << std::endl;
        }

        Tower_Init_Variables(pos,size);
    }
};


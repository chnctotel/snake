//
//  entities.cpp
//  snake
//
//  Created by chnctotel on 01.04.2026.
//
#include "entities.h"
#include "utils.h"

Entities::Entities(char sSmall, char sNormal)
:
symbolSmall(sSmall), symbolNormal(sNormal)
{
    normal = {-1, -1};
    for (size_t i = 0; i < count; i++)
        small[i] = {-1, -1};
}

void Entities::spawn(Field& f, byte status)
{
    if (status & FLAG_SPLIT)
    {
        normal = {-1, -1};
        
        for (size_t i = 0; i < count; i++)
        {
            int rx, ry;
            do {
                rx = utils::GetRandomInt(1, f.getWidth() - 2);
                ry = utils::GetRandomInt(1, f.getHeight() - 2);
            } while (!f.emptyPos(rx, ry));
            
            small[i] = {rx, ry};
            
            f.setChar(rx, ry, '$');
        }
        
    }
    else
    {
        for (size_t i = 0; i < count; i++)
            small[i] = {-1, -1};
        
        int rx, ry;
        do {
            rx = utils::GetRandomInt(1, f.getWidth() - 2);
            ry = utils::GetRandomInt(1, f.getHeight() - 2);
        } while (!f.emptyPos(rx, ry));
        
        normal = {rx, ry};
    }
}

void Entities::draw(Field& f, byte status)
{
    if (status & FLAG_SPLIT) {
        for (size_t i = 0; i < count; i++)
            if (small[i].x != -1)
                f.setChar(small[i].x, small[i].y, symbolSmall);
    }
    else
        f.setChar(normal.x, normal.y, symbolNormal);
}

int Entities::collision(Field& f, byte status, vector head)
{
    if (status & FLAG_SPLIT) {
        for (size_t i = 0; i < count; i++)
            if (small[i].x != -1 && head.x == small[i].x && head.y == small[i].y)
            {
                small[i] = {-1, -1};
                return 1;
            }
    }
    else
        if (head.x == normal.x && head.y == normal.y)
        {
            normal = {-1, -1};
            spawn(f, status);
            return 1;
        }
    return 0;
}


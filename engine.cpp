//
//  engine.cpp
//  snake
//
//  Created by chnctotel on 01.04.2026.
//
#include "engine.h"

void engine::setup()
{
    map.init(30, 20);
    map.clear();
   
    player.init(map.getWidth() / 2, map.getHeight() / 2, DIRECTION::RIGHT);
    
    target.init();
    trap.init();
    
    target.spawn(map, status);
    trap.spawn(map, status);
}

void engine::render()
{
    map.clear();
    
    target.draw(map, status);
    trap.draw(map, status);
    player.draw(map);
    
    map.print(status, player.getScore(), T_cooldown, T_duration, T_mine);
}

void engine::input()
{
    if (utils::kbhit())
    {
        char key = getchar();
        player.input(key);
    }
}

void engine::timer()
{
    if (T_cooldown >= 300 && !(status & FLAG_SPLIT))
    {
        status |= FLAG_SPLIT;
        T_cooldown = 0;
        T_duration = 0;
        
        target.spawn(map, status);
        trap.spawn(map, status);
    }
    
    
    if (status & FLAG_SPLIT)
    {
        T_duration++;
        if (T_duration >= 50)
        {
            status &= ~FLAG_SPLIT;
            T_duration = 0;
                
            target.spawn(map, status);
            trap.spawn(map, status);
                
        }
    } else
            T_cooldown++;
}
void engine::collision()
{
    if (status & FLAG_SPLIT)
    {
        for (int i = 0; i < target.getCount(); i++)
        {
            vector pos = target.getSmallPos(i);
            if (player.getHead().x == pos.x && player.getHead().y == pos.y)
            {
                player.grow();
                target.setSmallPos(i, {-1, -1});
            }
        }
        
        for (int i = 0; i < trap.getCount(); i++)
        {
            vector pos = trap.getSmallPos(i);
            if (player.getHead().x == pos.x && player.getHead().y == pos.y)
            {
                player.shrink();
                trap.setSmallPos(i, {-1, -1});
            }
        }
    } else
    {
        if (player.getHead().x == target.getPos().x && player.getHead().y == target.getPos().y)
        {
            player.grow();
            target.spawn(map, status);
        }
        
        bool is_mineActive = (player.getHead().x == trap.getPos().x && player.getHead().y == trap.getPos().y);
        
        if (T_mine >= 50 || is_mineActive)
        {
            if (is_mineActive)
                player.shrink();
            
            trap.spawn(map, status);
            T_mine = 0;
        }
    }
    
}
void engine::death()
{
    if (player.getHead().x == map.getWidth() - 1 || player.getHead().x <= 0 ||
        player.getHead().y == map.getHeight() - 1 || player.getHead().y <= 0)
        status |= FLAG_LOSE;
    
    if (player.collision())
        status |= FLAG_LOSE;
}

void engine::update()
{
    player.updatePosition();
    T_mine++;
    
    timer();
    collision();
    death();

}

void engine::run()
{
        setup();
        
        while (!(status & FLAG_LOSE))
        {
            input();
            update();
            render();
            usleep(150000);
        }
    
    if (status & FLAG_LOSE)
    {
        system("clear");
        std::cout << '\n' << "                             <<< GAME OVER !!! \n";
        std::cout << '\n' << "                             <<< YOUR SCORE: " << player.getScore() <<"\n\n\n";
        
    }
}



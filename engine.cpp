//
//  engine.cpp
//  snake
//
//  Created by chnctotel on 01.04.2026.
//
#include "engine.h"

Engine::Engine() :
map(30, 20),
player(map.getWidth() / 2, map.getHeight() / 2, DIRECTION::RIGHT)
{
    map.clear();
    
    target.spawn(map, status);
    trap.spawn(map, status);
}

void Engine::render()
{
    map.clear();
    
    target.draw(map, status);
    trap.draw(map, status);
    player.draw(map);
    
    map.print(status, player.score, T_cooldown, T_duration, T_mine);
}

void Engine::input()
{
    if (utils::kbhit())
    {
        char key = getchar();
        player.input(key);
    }
}

void Engine::timer()
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
void Engine::collision()
{
    if (status & FLAG_SPLIT)
    {
        for (int i = 0; i < target.count; i++)
        {
            vector pos = target.small[i];
            if (player.snakeHead.x == pos.x && player.snakeHead.y == pos.y)
            {
                player.grow();
                target.setSmallPos(i, {-1, -1});
            }
        }
        
        for (int i = 0; i < trap.count; i++)
        {
            vector pos = trap.small[i];
            if (player.snakeHead.x == pos.x && player.snakeHead.y == pos.y)
            {
                player.shrink();
                trap.setSmallPos(i, {-1, -1});
            }
        }
    } else
    {
        if (player.snakeHead.x == target.normal.x && player.snakeHead.y == target.normal.y)
        {
            player.grow();
            target.spawn(map, status);
        }
        
        bool is_mineActive = (player.snakeHead.x == trap.normal.x && player.snakeHead.y == trap.normal.y);
        
        if (T_mine >= 50 || is_mineActive)
        {
            if (is_mineActive)
                player.shrink();
            
            trap.spawn(map, status);
            T_mine = 0;
        }
    }
    
}
void Engine::death()
{
    if (player.snakeHead.x == map.getWidth() - 1 || player.snakeHead.x <= 0 ||
        player.snakeHead.y == map.getHeight() - 1 || player.snakeHead.y <= 0)
        status |= FLAG_LOSE;
    
    if (player.collision())
        status |= FLAG_LOSE;
}

void Engine::update()
{
    player.updatePosition();
    T_mine++;
    
    timer();
    collision();
    death();

}

void Engine::reset()
{
    status &= ~FLAG_LOSE;
    
    player.reset(map.getWidth() / 2, map.getHeight() / 2, DIRECTION::RIGHT);
    
    map.clear();
    
    T_mine = 0;
    T_cooldown = 0;
    T_duration = 0;
    
    target.spawn(map, status);
    trap.spawn(map, status);
}

void Engine::run()
{
    reset();
    
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
        std::cout << '\n' << "                             <<< YOUR SCORE: " << player.score <<"\n\n\n";
        
        getchar();
    }
}



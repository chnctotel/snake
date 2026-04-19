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
    
    T_targetLT = utils::GetRandomInt(400, 600);
    target.spawn(map, status);
    trap.spawn(map, status);
}

void Engine::render()
{
    map.clear();
    
    target.draw(map, status);
    trap.draw(map, status);
    drugs.draw(map, 0);
    player.draw(map);
    
    if (status & FLAG_TRIP)
        for (size_t i = 0; i < 15; i++)
        {
            int gx = utils::GetRandomInt(1, map.getWidth() - 2);
            int gy = utils::GetRandomInt(1, map.getHeight() - 2);
            char symbols[] = {'?', 's', ';', '!', 'v', '6', '%', '0'};
            map.setChar(gx, gy, symbols[utils::GetRandomInt(0, 7)]);
        }
    
    map.print(status, player.score, T_cooldown, T_targetLT, T_mine);
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
    if (T_lifetime == 0)
    {
        T_cooldown++;
        if (T_cooldown == T_targetLT)
        {
            drugs.spawn(map, 0);
            T_lifetime = 1;
            T_cooldown = 0;
            T_targetLT = utils::GetRandomInt(200, 500);
        }
    }
    else if (T_lifetime > 0)
    {
        T_lifetime++;
        if (T_lifetime >= 50)
        {
            drugs.normal = {-1, -1};
            T_lifetime = 0;
        }
    }
    
    if (status & (FLAG_TRIP | FLAG_RUSH | FLAG_SPLIT))
    {
        T_duration++;
        
        if (T_duration >= T_targetD)
        {
            status &= ~(FLAG_TRIP | FLAG_RUSH | FLAG_SPLIT);
            T_duration = 0;
            trap.spawn(map, status);
            target.spawn(map, status);
        }
    }
    
    
    
    
    
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
    
    
    if (player.snakeHead.x == drugs.normal.x && player.snakeHead.y == drugs.normal.y)
    {
        player.score += 5;
        for (size_t i = 0; i < 5; i++)
            player.grow();
        
        drugs.normal = { -1, -1 };
        status &= ~(FLAG_TRIP | FLAG_RUSH | FLAG_SPLIT);
        int drugs_effect = utils::GetRandomInt(0, 2);
        
        if (drugs_effect == 0)
            status |= FLAG_TRIP;
        else if (drugs_effect == 1)
            status |= FLAG_RUSH;
        else
        {
            status |= FLAG_SPLIT;
            trap.spawn(map, status);
            target.spawn(map, status);
        }
        
        T_duration = 1;
        T_targetD = utils::GetRandomInt(50, 150);
        T_lifetime = 0;
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
    status &= ~(FLAG_TRIP | FLAG_RUSH | FLAG_SPLIT);
    
    player.reset(map.getWidth() / 2, map.getHeight() / 2, DIRECTION::RIGHT);
    
    map.clear();
    
    T_mine = 0;
    T_lifetime = 0;
    T_cooldown = 0;
    T_duration = 0;
    
    drugs.normal = {-1, -1};
    
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
            
            int delay = 150000;
            
            if (status & FLAG_TRIP)
                delay = 200000;
            else if (status & FLAG_RUSH)
                delay = 50000;
            
            usleep(delay);
        }
    
    if (status & FLAG_LOSE)
    {
        system("clear");
        std::cout << '\n' << "                             <<< GAME OVER !!! \n";
        std::cout << '\n' << "                             <<< YOUR SCORE: " << player.score <<"\n\n\n";
        
        getchar();
    }
}



#pragma once
//  engine.h
//  snake



#include <iostream>
#include "game_data.h"
#include "utils.h"

#include "snake.h"
#include "field.h"
#include "entities.h"


class Engine
{
private:
    
    byte status = 0;
    
    int T_cooldown = 0;
    int T_duration = 0;
    int T_mine = 0;
    
    Field map;
    Snake player;
    Food  target;
    Mine  trap;
   
    
    
public:
    
    Engine();
    
    
    byte getStatus() const { return status; }
    
    void render();
    
    void input();
    
    void death();
    void timer();
    void collision();
    
    void update();
    
    void run();
    
};

#pragma once
//  engine.h
//  snake



#include <iostream>
#include "game_data.h"
#include "utils.h"

#include "snake.h"
#include "field.h"
#include "entities.h"


class engine
{
private:
    
    byte status = 0;
    
    int T_cooldown = 0;
    int T_duration = 0;
    int T_mine = 0;
    
    field map;
    snake player;
    food  target;
    mine  trap;
   
    
    
public:
    
    byte getStatus() { return status; }
    
    
    void setup();

    void render();
    
    void input();
    
    void death();
    void timer();
    void collision();
    
    void update();
    
    void run();
    
};

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
    
    int T_mine = 0;
    int T_cooldown = 0;
    int T_lifetime = 0;
    int T_duration = 0;
    
    int T_targetCD = 0;
    int T_targetD  = 0;
    
    Field map;
    Snake player;
    Entities target {'$', '@'};
    Entities trap {'x', 'X'};
    Entities drugs {'.', 'p'};
   
    
    
public:
    
    Engine();
    
    
    byte getStatus() const { return status; }
    int getScore() const { return player.score; }
    
    void render();
    
    void input();
    
    void death();
    void timer();
    void collision();
    
    void update();
    
    void reset();
    
    void run();
    
};

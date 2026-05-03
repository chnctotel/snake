#pragma once
//  snake.h
//  snake

#include <memory>
#include "game_data.h"
#include "field.h"


class Snake
{
private:
    
    int score;
    
    vector snakeHead;
    std::unique_ptr<vector[]> body;
    vector direction;
    DIRECTION move;
    
    void setDirection();
    
public:
    
    Snake(int x, int y, DIRECTION startMove);
   
    void updatePosition();
    void input(char key);
    
    void grow();
    void shrink();
    
    bool collision();
    
    void draw(Field& f);
    
    void reset(int x, int y, DIRECTION dir);
    
    friend class Engine;
};

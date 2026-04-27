#pragma once
//  snake.h
//  snake

#include "game_data.h"
#include "field.h"


class Snake
{
private:
    
    int score;
    
    vector snakeHead;
    vector* body;
    vector direction;
    DIRECTION move;
    
    void setDirection();
    
public:
    
    Snake(int x, int y, DIRECTION startMove);
    Snake(const Snake& other);
    Snake(Snake&& other);
    ~Snake() { delete[] body; }
    
    void updatePosition();
    void input(char key);
    
    void grow();
    void shrink();
    
    bool collision();
    
    void draw(Field& f);
    
    void reset(int x, int y, DIRECTION dir);
    
    friend class Engine;
};

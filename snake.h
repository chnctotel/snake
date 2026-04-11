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
    ~Snake() { delete[] body; }
    
    vector add(const vector& v1, const vector& v2) { return {v1.x + v2.x, v1.y + v2.y};}
    vector getHead() const { return snakeHead; }
    int getScore() const { return score; }
    
    void updatePosition();
    void input(char key);
    
    void grow();
    void shrink();
    
    bool collision();
    
    void draw(Field& f);
};

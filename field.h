#pragma once
//  field.h
//  snake
#include "game_data.h"


class field
{
private:
    
    char** data;
    
    int width;
    int height;
    
public:
    
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    
    void init(int width, int height);
    
    void clear();
    void setChar(int x, int y, char symbol);
    void print(byte status, int score, int T_cooldown, int T_duration, int T_mine);
    
    bool emptyPos(int x, int y);
    
    void destroy();
};


#pragma once
//  field.h
//  snake
#include "game_data.h"


class Field
{
private:
    
    char** data;
    
    int width;
    int height;
    
public:
    
    Field(int width, int height);
    ~Field();
    
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    
    void clear();
    void setChar(int x, int y, char symbol);
    void print(byte status, int score, int T_cooldown, int T_targetCD, int T_mine);
    
    bool emptyPos(int x, int y);
};


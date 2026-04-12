#pragma once
//  entities.h
//  snake
#include "game_data.h"
#include "field.h"

class Entities
{
private:

    static const int count = 25;
    
    vector small[count];
    vector normal;
    
    char symbolSmall;
    char symbolNormal;
    
public:
    
    Entities(char sSmall, char sNormal);
    
    void setSmallPos(int i, vector newPos) { small[i] = newPos; }
    
    void spawn(Field& f, byte status);
    
    void draw(Field& f, byte status);
    
    int collision(Field& f, byte status, vector head);
    
    friend class Engine;
};

#pragma once
//  entities.h
//  snake
#include "game_data.h"
#include "field.h"

class food
{
private:
    
    static const int count = 25;
    
    vector normal;
    vector small[count];
    
public:
    
    vector getSmallPos(int i) { return small[i]; }
    vector getPos() { return normal; }
    int getCount() { return count; }

    void setSmallPos(int i, vector newPos) { small[i] = newPos; }
    
    void init();
    
    void spawn(field& f, byte status);
    
    void draw(field& f, byte status);
    
    int collision(field& f, byte status, vector head);
    
    
};

///

class mine
{
private:
    
    static const int count = 25;
    
    vector normal;
    vector small[count];
    
public:
    
    vector getSmallPos(int i) { return small[i]; }
    vector getPos() { return normal; }
    int getCount() { return count; }
    
    void setSmallPos(int i, vector newPos) { small[i] = newPos; }
    
    void init();
    
    void spawn(field& f, byte status);
    
    void draw(field& f, byte status);
    
    int collision(field& f, byte status, vector head);
    
};

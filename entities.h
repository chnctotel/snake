#pragma once
//  entities.h
//  snake
#include "game_data.h"
#include "field.h"

class Food
{
private:
    
    static const int count = 25;
    
    vector normal;
    vector small[count];
    
public:
    
    Food();
    
    vector getSmallPos(int i) const { return small[i]; }
    vector getPos() const { return normal; }
    int getCount() const { return count; }

    void setSmallPos(int i, vector newPos) { small[i] = newPos; }
    
    void spawn(Field& f, byte status);
    
    void draw(Field& f, byte status);
    
    int collision(Field& f, byte status, vector head);
    
    
};

///

class Mine
{
private:
    
    static const int count = 25;
    
    vector normal;
    vector small[count];
    
public:
    
    Mine();
    
    vector getSmallPos(int i) const { return small[i]; }
    vector getPos() const { return normal; }
    int getCount() const { return count; }
    
    void setSmallPos(int i, vector newPos) { small[i] = newPos; }
    
    void init();
    
    void spawn(Field& f, byte status);
    
    void draw(Field& f, byte status);
    
    int collision(Field& f, byte status, vector head);
    
};

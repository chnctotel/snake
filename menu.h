#pragma once
//  menu.h
//  snake
#include "game_data.h"

class Menu
{
private:
    
    bool isSelected;
    int selectedItem = 0;
    static const size_t count = 5;
    
    const char* item[count] = { "Start Game", "Settings", "Login", "Stats", "Exit" };
    
public:
    
    void input(char key);
    
    void draw();
    
    OPTION run();
};


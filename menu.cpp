//
//  menu.cpp
//  snake
//
//  Created by chnctotel on 13.04.2026.
//
#include <iostream>
#include "menu.h"
#include "utils.h"

void Menu::input(char key)
{
    if (key == 'w' || key == 'W')
        selectedItem--;
    if (key == 's' || key == 'S')
        selectedItem++;
    if (key == static_cast<char>(10) || key == static_cast<char>(13))
        isSelected = true;
    
    if (selectedItem < 0)
        selectedItem = count - 1;
    if (selectedItem >= count)
        selectedItem = 0;
}

void Menu::draw()
{
    std::system("clear");
    std::cout << std::endl;
    for (size_t i = 0; i < count; i++)
        if (i == selectedItem)
            std::cout << "                                 > " << item[i] << '\n';
        else
            std::cout << "                                   " << item[i] << '\n';
}

OPTION Menu::run()
{
    isSelected = false;
    
    draw();
    
    while (!isSelected)
    {
        if (utils::kbhit())
        {
            char key = getchar();
            input(key);
            draw();
        }
    }
    return static_cast<OPTION>(selectedItem);
}

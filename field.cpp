//
//  field.cpp
//  snake
//
//  Created by chnctotel on 30.03.2026.
//

#include <iostream>
#include "field.h"

void field::init(int width, int height)
{
    this->width = width;
    this->height = height;
    
    data = new char*[height];
    for (size_t i = 0; i < height; i++)
        data[i] = new char[width];
}

void field::clear()
{
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
        {
            if (y == 0 || y == height - 1 || x == 0 || x == width - 1)
                data[y][x] = '#';
            else
                data[y][x] = ' ';
        }
}

void field::setChar(int x, int y, char symbol)
{
    if (y >= 0 && y < height && x >= 0 && x < width)
        data[y][x] = symbol;
}

void field::print(byte status, int score, int T_cooldown, int T_duration, int T_mine)
{
    std::system("clear");
    
    for (size_t y = 0; y < height; y++)
    {
        for (size_t x = 0; x < width; x++)
        {
            char s = data[y][x];
            
            if (s == '0')
                std::cout << DARK_GREEN;
            else if (s == 'o')
                std::cout << LIGHT_GREEN;
            else if (s == '@' || s == '$')
                std::cout << YELLOW;
            else if (s == 'X' || s == 'x')
                std::cout << RED;
            
            std::cout << s << ' ';
            std::cout << RESET;
            
            if (x == width - 1)
            {
                if (y == 2)
                    std::cout << " <--- SCORE: " << score;
                if (y == 4)
                    std::cout << " <--- MODE: " << ((status & FLAG_SPLIT) ? "SPLIT" : "NORMAL");
                if (y == 6 && !(status & FLAG_SPLIT) && T_cooldown < 250)
                    std::cout << " <--- mine timer: " << (50 - T_mine);
                if (y == 6 && (status & FLAG_SPLIT))
                    std::cout << " <--- duration: " << (50 - T_duration);
                if (y == 6 && T_cooldown > 250)
                    std::cout << " STORM IS COMING..";
            }
        }
        std::cout << '\n';
    }
}

bool field::emptyPos(int x, int y)
{
    if (y < 0 || y >= height || x < 0 || x >= width)
        return false;
    return data[y][x] == ' ';
}

void field::destroy()
{
    for (size_t i = 0; i < height; i++)
        delete[] data[i];
    delete[] data;
}

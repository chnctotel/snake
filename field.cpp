//
//  field.cpp
//  snake
//
//  Created by chnctotel on 30.03.2026.
//

#include <iostream>
#include "field.h"
#include "utils.h"

Field::Field(int width, int height)
{
    this->width = width;
    this->height = height;
    
    data = std::unique_ptr<std::unique_ptr<char[]>[]>(new std::unique_ptr<char[]>[height]);
    
    for (size_t i = 0; i < height; i++)
        data[i] = std::unique_ptr<char[]>(new char[width]);
}

void Field::clear()
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

void Field::setChar(int x, int y, char symbol)
{
    if (y >= 0 && y < height && x >= 0 && x < width)
        data[y][x] = symbol;
}

void Field::print(byte status, int score, int T_cooldown, int T_targetCD, int T_mine)
{
    std::system("clear");
    
    for (size_t y = 0; y < height; y++)
    {
        for (size_t x = 0; x < width; x++)
        {
            char s = data[y][x];
            int color = utils::GetRandomInt(31, 36);
            
            if (status & FLAG_RUSH && s != ' ')
                    std::cout << "\033[1;3" << utils::GetRandomInt(1, 6) << "m" << s << " " << RESET;
               else if (s == 'p')
                    std::cout << "💊";
                else if (s == ' ')
                    std::cout << "  ";
                else
                {
                    if (s == '0')
                        std::cout << DARK_GREEN;
                    else if (s == 'o')
                        std::cout << LIGHT_GREEN;
                    else if (s == '@' || s == '$')
                        std::cout << YELLOW;
                    else if (s == 'X' || s == 'x')
                        std::cout << RED;
                    else if (s == '?')
                        std::cout << "\033[" << color << "m";
                    else if (s == 's')
                        std::cout << "\033[" << color << "m";
                    else if (s == ';')
                        std::cout << "\033[" << color << "m";
                    else if (s == '!')
                        std::cout << "\033[" << color << "m";
                    else if (s == 'v')
                        std::cout << "\033[" << color << "m";
                    else if (s == '6')
                        std::cout << "\033[" << color << "m";
                    else if (s == '%')
                        std::cout << "\033[" << color << "m";
                    
                    std::cout << s << ' ';
                    std::cout << RESET;
                }
            
                if (x == width - 1)
                {
                    if (y == 2)
                        std::cout << " <--- SCORE: " << score;
                    if (y == 4 && !(status & FLAG_SPLIT && T_cooldown < T_targetCD))
                        std::cout << " <--- mine timer: " << (50 - T_mine);
                }
            }
            std::cout << '\n';
        }
}

bool Field::emptyPos(int x, int y)
{
    if (y < 0 || y >= height || x < 0 || x >= width)
        return false;
    return data[y][x] == ' ';
}


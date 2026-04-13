//
//  game_data.h
//  snake
//
//  Created by chnctotel on 27.03.2026.
//

#pragma once

#define RESET           "\033[0m"
#define RED             "\033[31m"
#define DARK_GREEN      "\033[1;32m"
#define LIGHT_GREEN     "\033[92m"
#define YELLOW          "\033[38;5;190m"

using byte = unsigned char;

static constexpr byte FLAG_LOSE  = 1 << 0;
static constexpr byte FLAG_SPLIT = 1 << 1;

enum class OPTION
{
    START = 0, SETTINGS, LOGIN, STATS, EXIT
};

enum class DIRECTION
{
    UP, DOWN, LEFT, RIGHT
};

struct vector
{
    int x;
    int y;
};


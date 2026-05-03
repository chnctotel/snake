//
//  snake.cpp
//  snake
//
//  Created by chnctotel on 30.03.2026.
//
#include "snake.h"
#include "utils.h"


void Snake::setDirection()
{
    switch (move)
    {
        case DIRECTION::UP:
            direction = {0, -1};
            break;
        case DIRECTION::DOWN:
            direction = {0, 1};
            break;
        case DIRECTION::LEFT:
            direction = {-1, 0};
            break;
        case DIRECTION::RIGHT:
            direction = {1, 0};
            break;
    }
}

Snake::Snake(int x, int y, DIRECTION startMove)
{
    score = 0;
    
    body = std::unique_ptr<vector[]>(new vector[1]);
    snakeHead = {x, y};
    
    body[0] = snakeHead;
    move = startMove;
    
    setDirection();
}

void Snake::updatePosition()
{
    setDirection();
    
    for (int i = score; i > 0; i--)
        body[i] = body[i - 1];
    
    snakeHead += direction;
    body[0] = snakeHead;
}

void Snake::input(char key)
{
    if ((key == 'w' || key == 'W') && move != DIRECTION::DOWN)
        move = DIRECTION::UP;
    else if ((key == 's' || key == 'S') && move != DIRECTION::UP)
        move = DIRECTION::DOWN;
    else if ((key == 'a' || key == 'A') && move != DIRECTION::RIGHT)
        move = DIRECTION::LEFT;
    else if ((key == 'd' || key == 'D') && move != DIRECTION::LEFT)
        move = DIRECTION::RIGHT;
}

void Snake::grow()
{
    vector* temp = utils::AddElement(body.get(), body.get() + score + 1, {0, 0});
    
    body.reset(temp);
    score++;
}

void Snake::shrink()
{
    if (score <= 0)
        return;
        

    vector* temp = utils::RemoveElement(body.get(), body.get() + score + 1, body.get() + score);
    
    body.reset(temp);
    score--;
}

void Snake::draw(Field& f)
{
    f.setChar(snakeHead.x, snakeHead.y, '0');
    
    for (size_t i = 1; i <= score; i++)
        f.setChar(body[i].x, body[i].y, 'o');
}

bool Snake::collision()
{
    for (int i = 1; i <= score; i++)
        if (snakeHead == body[i])
            return true;
    return false;
}

void Snake::reset(int x, int y, DIRECTION startMove)
{
    score = 0;
    snakeHead = { x, y };
  
    body = std::unique_ptr<vector[]>(new vector[1]);
    body[0] = snakeHead;
    move = startMove;
    
    setDirection();
}



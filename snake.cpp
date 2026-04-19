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
    
    body = new vector[1];
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
    
    snakeHead = add(snakeHead, direction);
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
    vector* temp = utils::AddElement(body, body + score + 1, {0, 0});
    
    delete[] body;
    body = temp;
    score++;
}

void Snake::shrink()
{
    if (score <= 0)
        return;
        

    vector* temp = utils::RemoveElement(body, body + score + 1, body + score);
    
    delete[] body;
    body = temp;
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
        if (snakeHead.x == body[i].x && snakeHead.y == body[i].y)
            return true;
    return false;
}

void Snake::reset(int x, int y, DIRECTION startMove)
{
    if (body != nullptr)
    {
        delete[] body;
        body = nullptr;
    }
    
    score = 0;
    snakeHead = { x, y };
  
    body = new vector[1];
    body[0] = snakeHead;
    move = startMove;
    
    setDirection();
}



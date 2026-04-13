#pragma once
//  application.h
//  snake
#include "engine.h"
#include "menu.h"

class Application
{
private:
    
    bool isRunning;
    
    Menu menu;
    Engine game;
    
public:
    
    Application() { isRunning = true; }
    
    void run();
    
};


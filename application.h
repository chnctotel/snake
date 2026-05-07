#pragma once
//  application.h
//  snake
#include <string>
#include "engine.h"
#include "menu.h"
#include "database.h"

class Application
{
private:
    
    bool isRunning;
    
    std::string playerNickname = "Player1";
    Database db;
    
    Menu menu;
    Engine game;
    
public:
    
    Application() { isRunning = true; }
    
    void run();
    
};


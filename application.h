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
    bool isLogged;
    
    std::string playerNickname;
    Database db;
    
    Menu menu;
    Engine game;
    
public:
    
    Application() { isRunning = true; isLogged = false; }
    
    void run();
    
};


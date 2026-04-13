//
//  application.cpp
//  snake
//
//  Created by chnctotel on 13.04.2026.
//
#include "application.h"

void Application::run()
{
    while (isRunning)
    {
        OPTION choice = menu.run();
        
        switch (choice)
        {
            case OPTION::START:
                game.run();
                
                break;
            case OPTION::SETTINGS:
                std::system("clear");
                std::cout << "Under construction..." << '\n' << "Press any key to return to menu.";
                getchar();
                
                break;
            case OPTION::LOGIN:
                std::system("clear");
                std::cout << "Under construction..." << '\n' << "Press any key to return to menu.";
                getchar();
                
                break;
            case OPTION::STATS:
                std::system("clear");
                std::cout << "Under construction..." << '\n' << "Press any key to return to menu.";
                getchar();
                
                break;
            case OPTION::EXIT:
                std::system("clear");
                isRunning = false;
                
                break;
        }
        
        
        
        
        
        
        
        
        
        
    }
}

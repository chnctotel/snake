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
                
                db.saveScore(playerNickname, game.getScore());
                break;
            case OPTION::SETTINGS:
                std::system("clear");
                std::cout << "Under construction..." << '\n' << "Press any key to return to menu.";
                getchar();
                
                break;
            case OPTION::LOGIN:
                std::system("clear");
                std::cout << "Enter your name: ";
                std::cin >> playerNickname;
                std::cout << "Welcome, " << playerNickname << "!\nPress Enter...";
                getchar(); getchar();

                break;
            case OPTION::STATS:
            {
                std::system("clear");
            
                ScoreRecord topTen[10];
                int found = db.getTopScores(topTen, 10);
                
                std::cout << "--- TOP PLAYERS --- \n";
                for (int i = 0; i < found; i++)
                    std::cout << i + 1 << ". " << topTen[i].nickname << ": " << topTen[i].score << '\n';
                
                if (found == 0)
                    std::cout << "No records yet.\n";
                
                std::cout << "\nPress Enter...";
                getchar(); getchar();
                
                break;
            }
            case OPTION::EXIT:
                std::system("clear");
                isRunning = false;
                
                break;
        }
        
        
        
        
        
        
        
        
        
        
    }
}

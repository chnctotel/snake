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
                if (!isLogged)
                {
                    std::system("clear");
                                 
                    std::cout << '\n' <<"                     << You must Login before playing!\n";
                    std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nPress Enter to return to menu...";
                    getchar(); getchar();
                }
                else
                {
                    game.run();
                    db.saveScore(playerNickname, game.getScore());
                }
                break;
            case OPTION::SETTINGS:
                std::system("clear");
                std::cout << "Under construction..." << '\n' << "Press any key to return to menu.";
                getchar();
                
                break;
            case OPTION::LOGIN:
                std::system("clear");
                std::cout << "\n                             <<< Enter your name: \n";
                std::cout << "\n                               > ";
                std::cin >> playerNickname;
                
                isLogged = true;
            
                std::cout << "\n\n\n\n                             << Welcome, " << playerNickname << "!\n\n\n\n\n\n\n\n\n\n\n\n\n\nPress Enter...";
                getchar(); getchar();

                break;
            case OPTION::STATS:
            {
                std::system("clear");
            
                ScoreRecord topTen[10];
                int found = db.getTopScores(topTen, 10);
                             
                std::cout << '\n' <<"                             <<< TOP PLAYERS: \n";
                for (int i = 0; i < found; i++)
                    std::cout << i + 1 << ". " << topTen[i].nickname << ": " << topTen[i].score << '\n';
                
                if (found == 0)
                {
                    std::cout << "\n\n\n                             No records yet...";
                    
                    std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nPress Enter...";
                    getchar(); getchar();
                }
                else
                {
                    int maxLines = 23;
                    int busyLines = found + 3;
                    int needLines = maxLines - busyLines;
                    
                    for (int i = 0; i < needLines; i++)
                        std::cout << '\n';
                    
                    std::cout << "Press Enter...";
                    getchar(); getchar();
                }
                break;
            }
            case OPTION::EXIT:
                std::system("clear");
                isRunning = false;
                
                break;
        }
        
        
        
        
        
        
        
        
        
        
    }
}

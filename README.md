# Terminal Snake (C++ OOP)

A terminal-based Snake game developed to practice Object-Oriented Programming (OOP) principles in C++.

## Project Overview
I started learning C++ on January 9, 2026. This project represents my first major practical milestone, where I applied theoretical knowledge in a real-world scenario:

- Transition from procedural (struct-based) programming to an OOP architecture.
- Manual memory management and dynamic array handling.
- Modular code structure (Engine, Entities, Field, and Snake classes).

## Key Features
- Classic Snake gameplay with collision detection.
- **SPLIT Mode**: a custom mechanic where game entities (food, mines) can duplicate.
- Timer system for managing power-ups and hazards.
- Non-blocking input handling (game logic runs independently of user input).

## Build and Run
To compile the project on Unix-based systems (macOS/Linux), run the following command in the source directory:

g++ main.cpp engine.cpp entities.cpp field.cpp snake.cpp -o snake

To start the game:
./snake

## Controls
- W / ↑ — move up  
- S / ↓ — move down  
- A / ← — move left  
- D / → — move right 

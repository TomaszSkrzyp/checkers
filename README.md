# checkers
# Project: Checkers Game (Console-based)

Overview

This is a console-based Checkers game implemented in C++. The game supports two-player mode and a single-player mode with an AI opponent. The AI is built using the Minimax algorithm with Alpha-Beta pruning to optimize decision-making.

**Features**

Console-based UI: Play Checkers in the terminal.

Two-player mode: Play against another human.

AI opponent: Play against a computer-controlled opponent.

Minimax Algorithm with Alpha-Beta Pruning: The AI makes intelligent moves by evaluating board states efficiently.

**Installation**

Prerequisites

A C++ compiler (e.g., g++, clang, or MSVC)

A terminal or command prompt

**Compilation and running**

 IF NOT USING VISUAL STUDIO:
To compile the game, use the following command in the terminal:

 g++ -o checkers main.cpp checkers.cpp ai.cpp -std=c++11
After compiling, run the executable with:

 ./checkers

 IF USING VISUAL STUDIO:
Open the .sln File
Double-click on the Checkers.sln file.
Set the Entry Point
Make sure main.cpp is set as the Startup File (Right-click → Set as Startup Item).
Click on the "Build Solution" (Shortcut: Ctrl + Shift + B).

**Game Setup**

To choose which player is a computer and eventual level of computer, change values in game object constuctor in checkers.cpp inside main()
EXAMPLE:

  game(false,0,true,5);
  
This would make a game between a real player number 1 - white (false means not a computer) 
and a computer player number 2 - black (true means a computer). The number that goes after boolean means eventual depth of a computer player
In other words, how much turns(white and black) would the computer count ahead to choose wheter a checked move is good or bad. 
Computer depth 0 is a player that makes random legal moves.

**How to Play**

The game follows standard Checkers rules.
Players take turns moving pieces. Example format of a squaee you have to type in: "A6"  
When typing longer moves you will be instructed to type in moves that will be "walked" through

Regular pieces move diagonally forward; kings move diagonally in both directions.

Capturing is mandatory when possible.

The game ends when a player has no moves left.

**AI Implementation**

The AI player is implemented using the Minimax algorithm with Alpha-Beta Pruning to enhance efficiency. The AI evaluates board states using:

Piece count: Counts the number of remaining pieces.

Position: Pieces in a farther position are more valuable. Same with pieces postion at the wall

King advantage: Gives higher value to kings.

**Future Enhancements**

Graphical User Interface (GUI)

Multiplayer over network

**License**

This project is open-source under the MIT License.

**Contributions**

Feel free to contribute by submitting pull requests or reporting issues.

**Author**

Tomasz Skrzyp

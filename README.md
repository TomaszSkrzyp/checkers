# checkers
# Project: Checkers Game (Console-based)

Overview

This is a console-based Checkers game implemented in C++. The game supports two-player mode and a single-player mode with an AI opponent. The AI is built using the Minimax algorithm with Alpha-Beta pruning to optimize decision-making.

Features

Console-based UI: Play Checkers in the terminal.

Two-player mode: Play against another human.

AI opponent: Play against a computer-controlled opponent.

Minimax Algorithm with Alpha-Beta Pruning: The AI makes intelligent moves by evaluating board states efficiently.

Installation

Prerequisites

A C++ compiler (e.g., g++, clang, or MSVC)

A terminal or command prompt

Compilation

To compile the game, use the following command in the terminal:

 g++ -o checkers main.cpp checkers.cpp ai.cpp -std=c++11

Running the Game

After compiling, run the executable with:

./checkers

How to Play

The game follows standard Checkers rules.

Players take turns moving pieces.

Regular pieces move diagonally forward; kings move diagonally in both directions.

Capturing is mandatory when possible.

The game ends when a player has no moves left.

AI Implementation

The AI player is implemented using the Minimax algorithm with Alpha-Beta Pruning to enhance efficiency. The AI evaluates board states using:

Piece count: Counts the number of remaining pieces.

Mobility: Evaluates the number of available moves.

King advantage: Gives higher value to kings.

Future Enhancements

Graphical User Interface (GUI)

Difficulty levels for AI

Multiplayer over network

License

This project is open-source under the MIT License.

Contributions

Feel free to contribute by submitting pull requests or reporting issues.

Author

[Your Name]

#pragma once
#include <vector>
#include<iostream>
#include <String>
#include<cmath>
#include<list>
#include"board_record.h"/// <summary>
/// Abstract base class 'general'. The 'board_jumps' and 'board_moves' classes inherit from it. These functions are used to search for moves on the board.
/// </summary>
class general {
protected:
    /// <summary>
    /// A char object defining the current turn (its order). 'w' means white's turn, 'b' means black's turn.
    /// </summary>
    char turn;

    /// <summary>
    /// Function to determine the Y coordinate of the jumped square. Due to board compression, this is not a trivial task like the X coordinate.
    /// </summary>
    /// <param name="yj"> Y coordinate of the jumped square </param>
    /// <param name="xs"> X coordinate of the starting square </param>
    /// <param name="ys"> Y coordinate of the starting square </param>
    /// <param name="yf"> Y coordinate of the ending square </param>
    const void find_y_jumped(int& yj, int xs, int ys, int yf);

    /// <summary>
    /// Function that establishes the key value for a jump. This value contains information about the starting, jumped, and ending points.
    /// </summary>
    /// <param name="xs"> X coordinate of the starting square </param>
    /// <param name="ys"> Y coordinate of the starting square </param>
    /// <param name="xj"> X coordinate of the jumped square </param>
    /// <param name="yj"> Y coordinate of the jumped square </param>
    /// <param name="xf"> X coordinate of the ending square </param>
    /// <param name="yf"> Y coordinate of the ending square </param>
    /// <returns> Key value </returns>
    const int hashed_jump(int xs, int ys, int xj, int yj, int xf, int yf);

    /// <summary>
    /// Function to rotate the key value.
    /// </summary>
    /// <param name="i"> Key value </param>
    /// <returns> Rotated key value </returns>
    const int rev_hash(int i);

    /// <summary>
    /// Array of char objects. It represents the squares on the board. The value of the char defines the piece located on that square: 'b' - black piece, 'w' - white piece, 'e' - empty square. Additionally, 'B' and 'W' represent the kings of respective colors.
    /// </summary>
    char arr[8][4];

public:
    /// <summary>
    /// A pure virtual class used to load the list of moves found by the algorithm into the provided move list.
    /// </summary>
    /// <param name="list"> A list of move pointers, to which we want to transfer the found moves </param>
    virtual void update_moves(std::list<move*>& list) = 0;

    /// <summary>
    /// Constructor for the general class. It reads the values of the squares from the board object to fill the char array representing the board. The current turn is set using an initializer list.
    /// </summary>
    /// <param name="b"> A board object whose values we want to transfer to the object </param>
    general(const board& b) : turn(b.get_turn()) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 4; j++) {
                arr[i][j] = b.get_piece(i, j);
            }
        }
    }

    /// <summary>
    /// Destructor for the general class. It cleans up the m_list.
    /// </summary>
    ~general();

    std::list<move*> m_list = {};

    /// <summary>
    /// Function allowing to change the content of the char array 'arr' of an existing object. It works the same way as the constructor.
    /// </summary>
    /// <param name="b"> The new board state </param>
    void replace_board(const board& b);

    /// <summary>
    /// Function returning the turn.
    /// </summary>
    /// <returns> A char indicating which color's pieces should move now </returns>
    int get_turn() const {
        return turn;
    }
};

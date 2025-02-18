#pragma once
#include "board_jumps.h"

/// <summary>
/// Class responsible for finding possible moves for a piece on the board. Inherits from the 'general' class.
/// </summary>
class board_moves : public general {
private:
    /// <summary>
    /// Function checks the possibility of moving up the board for the given coordinates and piece.
    /// </summary>
    /// <param name="piece"> Color of the moving piece (char) </param>
    /// <param name="xs"> X coordinate of the starting square </param>
    /// <param name="ys"> Y coordinate of the starting square </param>
    /// <param name="dir"> Direction of the possible move ('l' - diagonal move left, 'r' - diagonal move right) </param>
    void move_legal_up(char piece, int xs, int ys, char dir);

    /// <summary>
    /// Function checks the possibility of moving down the board for the given coordinates and piece.
    /// </summary>
    /// <param name="piece"> Color of the moving piece (char) </param>
    /// <param name="xs"> X coordinate of the starting square </param>
    /// <param name="ys"> Y coordinate of the starting square </param>
    /// <param name="dir"> Direction of the possible move ('l' - diagonal move left, 'r' - diagonal move right) </param>
    void move_legal_down(char piece, int xs, int ys, char dir);

    /// <summary>
    /// List of pointers to moves generated for an object of this class. It overloads the list with the same name declared in the base class.
    /// </summary>
    std::list<move*> m_list;

public:
    /// <summary>
    /// Constructor of the board_moves class, using the constructor of the base class 'general'.
    /// </summary>
    /// <param name="b"> Reference to the board object passed </param>
    board_moves(const board& b) : general(b) {
        /*std::cout << "board moves finder created" << std::endl;*/
    }

    /// <summary>
    /// Destructor of the board_moves object.
    /// </summary>
    ~board_moves() {
        /*std::cout << "board moves finder destroyed" << std::endl;*/
    }

    /// <summary>
    /// This function is used to load the list of moves found by the object into the selected list of moves.
    /// </summary>
    /// <param name="list"> List of pointers to moves (not necessarily empty) </param>
    void update_moves(std::list<move*>& list);

    /// <summary>
    /// This function dynamically allocates a move object and adds it to the m_list.
    /// </summary>
    /// <param name="piece"> Color of the moving piece (char) </param>
    /// <param name="xs"> X coordinate of the starting square </param>
    /// <param name="ys"> Y coordinate of the starting square </param>
    /// <param name="xf"> X coordinate of the ending square </param>
    /// <param name="yf"> Y coordinate of the ending square </param>
    void add_move(char piece, int xs, int ys, int xf, int yf);

    /// <summary>
    /// This function iterates over the board and searches for moves upwards (by calling the move_legal_up function) or downwards (by calling the move_legal_down function) 
    /// for each position where a piece of the correct color is located.
    /// </summary>
    /// <returns> Returns true if no moves were found </returns>
    bool avalilable_moves();
};

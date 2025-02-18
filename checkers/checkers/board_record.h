#pragma once
#include <iostream>
#include <list>
#include <vector>
#include "moves_jumps.h"

/// <summary>
/// Class storing information about the current state of the board.
/// </summary>
class board {
private:
    char arr[8][4]; // Char array containing information about pieces on the board, optimized to 8x4 for better performance
    char turn; // Current turn - 'w' means white's turn, 'b' means black's turn
    bool is_computer[2]; // Two-element array indicating whether either player is a computer (true for computer)
    std::list<move*> previous_moves; // List of pointers to all executed moves

    /// <summary>
    /// Function checking if the given coordinates should trigger "crowning".
    /// </summary>
    /// <param name="x">The x-coordinate of the field being checked</param>
    /// <param name="y">The y-coordinate of the field being checked</param>
    void check_crown(const int& x, const int& y);

    /// <summary>
    /// Function that sets the pieces to their initial positions and clears the previous moves list.
    /// </summary>
    void reset();

public:
    /// <summary>
    /// Constructor that initializes the array to the starting positions.
    /// </summary>
    /// <param name="w_is_computer">Indicates if the white player is a computer</param>
    /// <param name="b_is_computer">Indicates if the black player is a computer</param>
    board(char w_is_computer, char b_is_computer);

    /// <summary>
    /// Destructor of the board object.
    /// </summary>
    ~board();

    /// <summary>
    /// Copy constructor for the board object.
    /// </summary>
    board(const board& board);

    /// <summary>
    /// Method returning the color of the piece at the given coordinates.
    /// </summary>
    /// <param name="x">The x-coordinate of the field being checked</param>
    /// <param name="y">The y-coordinate of the field being checked</param>
    /// <returns>Char representing the color of the piece</returns>
    char get_piece(int x, int y) const;

    /// <summary>
    /// Method returning a pointer to the previous move.
    /// </summary>
    /// <returns>A pointer to the previous move</returns>
    move* get_previous_move() const;

    /// <summary>
    /// Method that makes the given move on the board.
    /// </summary>
    /// <param name="chosen_move">Pointer to the move that should be made</param>
    void make_move(move* chosen_move);

    /// <summary>
    /// Method undoing the last move made on the board.
    /// </summary>
    void undo_move();

    /// <summary>
    /// Method changing the current turn (player's color).
    /// </summary>
    void change_turn();

    /// <summary>
    /// Method returning the current player's color.
    /// </summary>
    /// <returns>Char representing the current player's color</returns>
    char get_turn() const;

    /// <summary>
    /// Method checking if the player with the given index is a computer.
    /// </summary>
    /// <param name="ind">Player index (0 or 1)</param>
    /// <returns>true if the player is a computer; false if the player is human</returns>
    bool is_player_computer(int ind) const;
};

/// <summary>
/// Container class storing game results.
/// </summary>
template <typename T>
class game_results_container {
private:
    std::vector<T> game_data; // Vector storing game data

public:
    /// <summary>
    /// Method adding game data to the container.
    /// </summary>
    /// <param name="data">Game data to be added</param>
    void add(const T& data) {
        game_data.push_back(data);
    }

    /// <summary>
    /// Method returning the game data from a given index.
    /// </summary>
    /// <param name="index">Index of the data to retrieve</param>
    /// <returns>Reference to the game data from the given index</returns>
    const T& get_data(size_t index) {
        return game_data[index];
    }

    /// <summary>
    /// Method returning the number of elements stored in the container.
    /// </summary>
    /// <returns>Number of elements in the container</returns>
    const size_t size() {
        return game_data.size();
    }
};

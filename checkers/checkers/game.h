#pragma once
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "board_moves.h"
#include "player.h"
#include <memory>
#include "alpha_beta.h"
#include <thread>
#include <chrono>

/// <summary>
/// Class representing the checkers game.
/// </summary>
class game {
    float score = 0; ///< Current game score
    bool types[2]; ///< Player types (true for computer, false for human)
    int level[2]; ///< Difficulty levels of the players
    player players[2]; ///< Array of players
    // Nested templated container class for game results
    game_results_container<std::string> winners; ///< Container for game results (winners)
    game_results_container<int> game_lengths; ///< Container for game lengths

    /// <summary>
    /// Function that evaluates the current board state.
    /// </summary>
    /// <param name="b">Board object</param>
    /// <returns>The board evaluation score</returns>
    int evaluate_score(const board& b);

    /// <summary>
    /// Function that checks if a given piece is on the edge of the board.
    /// </summary>
    /// <param name="i">Row index</param>
    /// <param name="j">Column index</param>
    /// <returns>True if the piece is on the edge, otherwise false</returns>
    bool on_wall(int i, int j);

    /// <summary>
    /// The main game loop.
    /// </summary>
    /// <param name="iscomp1">Is the first player a computer?</param>
    /// <param name="iscomp2">Is the second player a computer?</param>
    /// <param name="max_turn">Maximum number of turns</param>
    void main_loop(bool iscomp1, bool iscomp2, int max_turn);

    /// <summary>
    /// Function that fills a list of move pointers with available jump moves for a position.
    /// </summary>
    /// <param name="moves">List of move pointers to fill</param>
    /// <param name="jump_finder">Object used to find jumps</param>
    /// <param name="new_board">Board object containing the current board state</param>
    /// <returns>True if a jump is found, false if not</returns>
    bool load_jump_moves(std::list<move*>& moves, board_jumps jump_finder, const board& new_board);

    /// <summary>
    /// Function that fills a list of move pointers with available moves for a position.
    /// </summary>
    /// <param name="moves">List of move pointers to fill</param>
    /// <param name="move_finder">Object used to find moves</param>
    /// <param name="new_board">Board object containing the current board state</param>
    /// <returns>True if a move is found, false if not</returns>
    bool load_moves(std::list<move*>& moves, board_moves move_finder, const board& new_board);

public:
    /// <summary>
    /// Constructor initializing a new game.
    /// </summary>
    /// <param name="is_comp_1">Is the first player a computer?</param>
    /// <param name="level1">Difficulty level of the first player. 0 means a human player</param>
    /// <param name="is_comp_2">Is the second player a computer?</param>
    /// <param name="level2">Difficulty level of the second player. 0 means a human player</param>
    game(bool is_comp_1, int level1, bool is_comp_2, int level2);

    /// <summary>
    /// Function that starts the game.
    /// </summary>
    /// <param name="max_turn">Number of turns after which the game will end in a draw</param>
    void start(int max_turn);

    /// <summary>
    /// Function that checks if the game is over.
    /// </summary>
    /// <param name="player_index">Player index</param>
    /// <param name="list_size">Size of the move list</param>
    /// <returns>True if the game is over, false otherwise</returns>
    bool game_over(int player_index, int list_size);
};

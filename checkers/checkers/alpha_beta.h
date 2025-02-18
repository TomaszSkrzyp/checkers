#pragma once
#include <memory>
#include "board_jumps.h"
#include "board_moves.h"

/// <summary>
/// Class implementing the algorithm for finding the best move. It uses the alpha-beta pruning algorithm.
/// </summary>
class alpha_beta {
private:
    int MaxIterDepth; // Maximum iteration depth of the algorithm

    std::unique_ptr<board> current_b; // Current board state

    move* bestM; // Best move obtained by the algorithm
    move* temp_bestM; // Temporary best move

    int max_depth; // Maximum search depth
    int cur_depth; // Current search depth
    bool reached_end; // Flag indicating whether the search has reached its end

    board_jumps jump_finder; // Object for finding jumps
    board_moves move_finder; // Object for finding regular moves

    /// <summary>
    /// Method for printing the move.
    /// </summary>
    /// <param name="v">Pointer to the move we want to print</param>
    void print_move(move* v);

    /// <summary>
    /// Method to check if the given coordinates are on the edge of the board.
    /// </summary>
    /// <param name="x">X coordinate</param>
    /// <param name="y">Y coordinate</param>
    /// <returns>true if the coordinates are on the edge of the board; false otherwise</returns>
    bool on_wall(int x, int y);

    /// <summary>
    /// Method to evaluate the score for a given board.
    /// </summary>
    /// <param name="b">Reference to the board object for which the score is being calculated</param>
    /// <returns>Score of the given board</returns>
    int evaluate_score(const board& b);

    /// <summary>
    /// Method for filling the list of move pointers with available moves in the current position.
    /// </summary>
    /// <param name="moves">List of move pointers to be filled</param>
    /// <param name="jump_finder">Object for finding jumps</param>
    /// <param name="new_board">Board object containing the current state of the board</param>
    /// <returns>true if a move is found; false if not</returns>
    bool load_jump_moves(std::list<move*>& moves, board_jumps& jump_finder, const board& new_board);

    /// <summary>
    /// Method for filling the list of move pointers with available regular moves in the current position.
    /// </summary>
    /// <param name="moves">List of move pointers to be filled</param>
    /// <param name="move_finder">Object for finding moves</param>
    /// <param name="new_board">Board object containing the current state of the board</param>
    /// <returns>true if a move is found; false if not</returns>
    bool load_moves(std::list<move*>& moves, board_moves& move_finder, const board& new_board);

public:
    /// <summary>
    /// Constructor for the alpha_beta class. Initializes the alpha_beta object based on the provided parameters.
    /// </summary>
    /// <param name="board_ptr">Unique pointer to the board object on which moves will be checked</param>
    /// <param name="jump_finding_tool">Object for finding jumps</param>
    /// <param name="move_finding_tool">Object for finding moves</param>
    /// <param name="max">Maximum depth of the algorithm iterations</param>
    alpha_beta(std::unique_ptr<board>& board_ptr, board_jumps& jump_finding_tool, board_moves& move_finding_tool, int max)
        : current_b(std::move(board_ptr)), bestM(nullptr), temp_bestM(nullptr), max_depth(0), cur_depth(0), reached_end(false),
        jump_finder(jump_finding_tool), move_finder(move_finding_tool), MaxIterDepth(max) {}

    /// <summary>
    /// Method implementing the "alpha-beta pruning" algorithm. It checks all move combinations up to a given depth unless a situation is encountered where further searching is pointless.
    /// It returns the result that can be achieved within this combination.
    /// </summary>
    /// <param name="b">Unique pointer to the board object on which moves will be checked. These objects will be created recursively during the algorithm execution</param>
    /// <param name="depth">Depth at which the algorithm is currently operating</param>
    /// <param name="alpha">Alpha value used in the algorithm, can be defined as the best result found so far by white</param>
    /// <param name="beta">Beta value used in the algorithm, can be defined as the best result found so far by black</param>
    /// <returns>The best result achieved at the current search level</returns>
    int algorythm(std::unique_ptr<board>& b, int depth, int alpha, int beta);

    /// <summary>
    /// Method that returns the best move found by the algorithm.
    /// </summary>
    /// <param name="print">Flag determining whether to print the move</param>
    /// <returns>The best move</returns>
    move* get_best_move(bool print);

    /// <summary>
    /// Method for searching through the move list and updating the best move.
    /// </summary>
    /// <param name="m_list">List of moves to search through</param>
    void search(std::list<move*> m_list);
};

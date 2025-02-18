#pragma once

#include "board_record.h"
#include "board_record.h"

#include <vector>
#include <thread>
#include <chrono> 


/// Object responsible for handling input and output.

class command_control {
	std::list<move*> list; /// List of possible moves.
	std::string players[2]; /// "Names" of the players participating in the game, stored in an array of strings.
	char turn; /// Information about the current turn, 'w' means white's turn, 'b' means black's turn

	/// <summary>
	/// Function that checks whether a given move is legal. It also checks "jumps" of length one that are part of longer jump sequences.
	/// </summary>
	/// <param name="keys"> List of keys containing information about the jump. The function updates this list in case of longer jump sequences. </param>
	/// <param name="xs"> x-coordinate of the starting square </param>
	/// <param name="ys"> y-coordinate of the starting square </param>
	/// <param name="xj"> x-coordinate of the jumped square </param>
	/// <param name="yj"> y-coordinate of the jumped square </param>
	/// <param name="xf"> x-coordinate of the ending square </param>
	/// <param name="yf"> y-coordinate of the ending square </param>
	/// <param name="answer"> A pointer to the correct move, passed by reference to "return" the correct move. </param>
	/// <param name="reset"> Information about the need to reset the move request process from the user. </param>
	/// <returns> True or false depending on whether a valid move is found. </returns>
	bool one_move_request(std::list<int>& keys, int& xs, int& ys, int& xj, int& yj, int& xf, int& yf, move*& answer, bool& reset);

	/// <summary>
	/// Function that retrieves a square from the user in the form of a position on the board and converts it to an int value being the index.
	/// </summary>
	/// <param name="x"> x-coordinate of the square, passed by reference in order to update the converted value. </param>
	/// <param name="y"> y-coordinate of the square, passed by reference in order to update the converted value. </param>
	void get_pos_from_command(int& x, int& y);

	/// <summary>
	/// Function that displays the move in a format consistent with board positions.
	/// </summary>
	/// <param name="v"> A pointer to the move we want to display. </param>
	void print_single_move(move* v) const;

	/// <summary>
	/// Function that "erases" n lines from the terminal.
	/// </summary>
	/// <param name="n_lines"> The number of lines to "erase". </param>
	void clear_lines(int n_lines) const;

	/// <summary>
	/// Function that determines the y-coordinate of the jumped square. Due to board compression, this is not a trivial task. The x-coordinate is always the arithmetic mean of xs and xf.
	/// </summary>
	/// <param name="yj"> The y-coordinate of the jumped square, passed by reference. </param>
	/// <param name="xs"> x-coordinate of the starting square </param>
	/// <param name="ys"> y-coordinate of the starting square </param>
	/// <param name="yf"> y-coordinate of the ending square </param>
	void find_y_jumped(int& yj, int xs, int ys, int yf);

	/// <summary>
	/// Function that determines the key value for the jump. This value contains information about the starting point, jumped point, and ending point.
	/// </summary>
	/// <param name="xs"> x-coordinate of the starting square </param>
	/// <param name="ys"> y-coordinate of the starting square </param>
	/// <param name="xj"> x-coordinate of the jumped square </param>
	/// <param name="yj"> y-coordinate of the jumped square </param>
	/// <param name="xf"> x-coordinate of the ending square </param>
	/// <param name="yf"> y-coordinate of the ending square </param>
	/// <returns></returns>
	const int hashed_jump(int xs, int ys, int xj, int yj, int xf, int yf);

	/// <summary>
	/// Function that rotates the key value.
	/// </summary>
	/// <param name="i"> The key value </param>
	/// <returns> The rotated key value </returns>
	const int rev_hash(int i);

public:
	/// <summary>
	/// Constructor for the command_control object.
	/// </summary>
	/// <param name="t"> Current turn </param>
	/// <param name="p1"> "Name" of the first player </param>
	/// <param name="p2"> "Name" of the second player </param>
	command_control(char t, const std::string& p1, const std::string& p2) : turn(t) {
		players[0] = p1; players[1] = p2;
	}

	/// <summary>
	/// Destructor that destroys the command_control object. There is no need to deallocate the pointers in the list, as that is handled by another function.
	/// </summary>
	~command_control() {
		while (!list.empty()) {
			list.pop_front();
		}
	}

	/// <summary>
	/// Function that calculates the value of a move.
	/// </summary>
	/// <param name="cur_score"> The score before the move </param>
	/// <param name="score_after"> The score after the move </param>
	void move_strength(int cur_score, int score_after) const;

	/// <summary>
	/// Function that retrieves a move from the user. Works in conjunction with the one_move_request function.
	/// </summary>
	/// <returns> The valid move </returns>
	move* move_request();

	/// <summary>
	/// Function that informs about the assignment of colors to players.
	/// </summary>
	void start_game() const;

	/// <summary>
	/// Function that informs about the current turn and score.
	/// </summary>
	/// <param name="score"> The current score </param>
	/// <param name="turn"> The current turn </param>
	/// <param name="num"> The move number </param>
	void start_round(int score, char turn, int num) const;

	/// <summary>
	/// Function that informs about the move just made.
	/// </summary>
	/// <param name="m"> A pointer to the move </param>
	/// <param name="turn"> The current turn </param>
	void mid_round(move* m, char turn) const;

	/// <summary>
	/// Function that informs about the end of the game, the potential winner, and asks about the desire for another match.
	/// </summary>
	/// <param name="is_draw"> Informs about a possible draw </param>
	/// <param name="index"> Informs about the index of the winner </param>
	/// <returns> Returns true if the player wishes to play another match </returns>
	bool end_game(bool is_draw, int index) const;

	/// <summary>
	/// Function that displays the move in a format consistent with board positions, excluding any jumped squares.
	/// </summary>
	/// <param name="v"> A pointer to the move we want to display </param>
	void this_move_command(move* m) const;

	/// <summary>
	/// Function that displays the current board.
	/// </summary>
	/// <param name="b"> A pointer to the board object containing the board we want to display </param>
	void print_table(const board* b) const;

	/// <summary>
	/// Updates the list of moves held by the command_control object and changes the turn.
	/// </summary>
	/// <param name="new_list"> A reference to the list of move pointers we want to load into the command_control object </param>
	/// <param name="t"> The current turn </param>
	void replace_moves(const std::list<move*>& new_list, char t);

	/// <summary>
	/// Displays the list of available moves.
	/// </summary>
	void print_move() const;

	/// <summary>
	/// Function that changes the value of the current turn.
	/// </summary>
	/// <param name="t"> The new value of the turn </param>
	void replace_turn(char t) {
		turn = t;
	}

	/// <summary>
	/// Function that returns the value of the turn.
	/// </summary>
	/// <returns> The value of the turn </returns>
	char get_turn() const {
		return turn;
	}

	/// <summary>
	/// Function that retrieves input data and converts it to a string type.
	/// </summary>
	/// <returns> The input data in the form of a string </returns>
	std::string get_string() const;

	/// <summary>
	/// Function that prints the results of all previous games.
	/// </summary>
	void print_previous_results(game_results_container<std::string>& winners, game_results_container<int>& game_lengths) const;

};
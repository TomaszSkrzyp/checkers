#pragma once
#include "moves_jumps.h"
#include "command.h"
#include <random>
/// <summary>
/// Abstract class representing a player in the game.
/// </summary>
class player_type {
public:
	/// <summary>
	/// A pure virtual method that must be implemented in derived classes.
	/// Used to choose a move from the available moves.
	/// </summary>
	/// <param name="moves">List of available moves.</param>
	/// <param name="console">Reference to the object controlling the commands.</param>
	/// <returns>A pointer to the selected move.</returns>
	virtual move* choose_move(std::list<move*> moves, command_control& console) = 0;

	/// <summary>
	/// Virtual destructor of the base class ensuring correct destruction of derived class objects.
	/// </summary>
	virtual ~player_type() {}
};

/// <summary>
/// Class representing a computer player who chooses a move randomly.
/// Inherits from the abstract player_type class.
/// </summary>
class random_comp : public player_type {
	/// <summary>
	/// Object used to generate random numbers.
	/// </summary>
	std::random_device move_choser;

public:
	/// <summary>
	/// Method that selects a random move from the available moves for the computer player.
	/// </summary>
	/// <param name="moves">List of available moves.</param>
	/// <param name="console">Reference to the object controlling the commands.</param>
	/// <returns>A pointer to the randomly selected move.</returns>
	move* choose_move(std::list<move*> moves, command_control& console) override;

};

/// <summary>
/// Class representing an intelligent computer player who makes more advanced decisions when choosing a move.
/// Inherits from the abstract player_type class.
/// </summary>
class smart_computer : public player_type {

public:
	/// <summary>
	/// Method that selects a move from the available moves for the intelligent computer player.
	/// The implementation of this method should take into account the strategy of decision-making by the computer.
	/// </summary>
	/// <param name="moves">List of available moves.</param>
	/// <param name="console">Reference to the object controlling the commands.</param>
	/// <returns>A pointer to the selected move.</returns>
	move* choose_move(std::list<move*> moves, command_control& console) override;
};

/// <summary>
/// Class representing a human player who makes decisions based on user input.
/// Inherits from the abstract player_type class.
/// </summary>
class human_player : public player_type {

public:
	/// <summary>
	/// Method defining how data is collected from the user.
	/// </summary>
	/// <param name="moves">List of available moves.</param>
	/// <param name="console">Reference to the object controlling the commands.</param>
	/// <returns>A pointer to the selected move.</returns>
	move* choose_move(std::list<move*> moves, command_control& console) override;
};

/// <summary>
/// Class representing a player in the game.
/// </summary>
class player {
	char color; ///< Player's color.
	std::string name; ///< Player's name.

	std::shared_ptr<player_type> p_type; ///< Pointer to the player's type.

public:
	/// <summary>
	/// Default constructor.
	/// </summary>
	player() = default;

	/// <summary>
	/// Constructor initializing the player with a given color and name.
	/// </summary>
	/// <param name="c">Player's color.</param>
	/// <param name="player_name">Player's name.</param>
	player(char c, const std::string& player_name) : color(c), name(player_name) {
	}

	/// <summary>
	/// Sets the player's type to the given type.
	/// </summary>
	/// <param name="p_type">Pointer to the player's type object.</param>
	void set_type(std::shared_ptr<player_type> p_type) {
		this->p_type = p_type;
	}

	/// <summary>
	/// Chooses a move from the list of available moves using the defined player type.
	/// </summary>
	/// <param name="list">List of available moves.</param>
	/// <param name="console">Reference to the object controlling the commands.</param>
	/// <returns>A pointer to the selected move.</returns>
	move* choose_move(std::list<move*> list, command_control& console) {
		// Replaces moves in the console for this player
		console.replace_moves(list, color);
		// Chooses a move using the defined player type
		return p_type->choose_move(list, console);
	}

	/// <summary>
	/// Returns the player's name.
	/// </summary>
	/// <returns>The player's name.</returns>
	std::string get_name() {
		return name;
	}

	/// <summary>
	/// Sets a new name for the player.
	/// </summary>
	/// <param name="new_name">New player's name.</param>
	void set_name(std::string new_name) {
		name = new_name;
	}
};

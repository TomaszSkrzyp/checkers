#pragma once
#include <list>
#include <iostream>

/// <summary>
/// Class representing a single jump of a piece on the board.
/// </summary>
class jump {
	char j_piece; ///< Color of the piece making the jump
	jump* prev; ///< Pointer to the previous jump
	bool next; ///< Flag indicating whether there is another jump
	int key = 0; ///< Unique identifier for the jump
	/*jumped pieces*/
	char jumped; ///< Color of the piece that was jumped over
	int xj; ///< x-coordinate of the jumped piece
	int yj; ///< y-coordinate of the jumped piece
	/*start and finish*/
	int xs; ///< x-coordinate of the starting field of the jump
	int ys; ///< y-coordinate of the starting field of the jump

	int xf; ///< x-coordinate of the destination field of the jump
	int yf; ///< y-coordinate of the destination field of the jump

public:
	int n_jump; ///< Counter for references to the jump object

	/// <summary>
	/// Constructor creating a jump object.
	/// </summary>
	/// <param name="j_p">Color of the piece making the jump</param>
	/// <param name="j">Color of the piece that was jumped over</param>
	/// <param name="x_j">x-coordinate of the jumped piece</param>
	/// <param name="y_j">y-coordinate of the jumped piece</param>
	/// <param name="x_s">x-coordinate of the starting field of the jump</param>
	/// <param name="y_s">y-coordinate of the starting field of the jump</param>
	/// <param name="x_f">x-coordinate of the destination field of the jump</param>
	/// <param name="y_f">y-coordinate of the destination field of the jump</param>
	/// <param name="p">Pointer to the previous jump</param>
	/// <param name="k">Unique identifier for the jump</param>
	jump(char j_p, char j, int x_j, int y_j, int x_s, int y_s, int x_f, int y_f, jump* p, int k)
		: prev(p), j_piece(j_p), jumped(j), xj(x_j), yj(y_j), n_jump(0), next(false), xs(x_s), ys(y_s), xf(x_f), yf(yf), key(k) {
	}

	/// <summary>
	/// Method returning the unique identifier of the jump.
	/// </summary>
	/// <returns>Unique identifier of the jump</returns>
	int get_key() const { return key; }

	/// <summary>
	/// Method returning the pointer to the previous jump.
	/// </summary>
	/// <returns>Pointer to the previous jump</returns>
	jump* get_prev() { return prev; }

	/// <summary>
	/// Method setting the flag indicating whether there is another jump.
	/// </summary>
	/// <param name="new_next">New value for the next flag</param>
	void set_next(bool new_next) { next = new_next; }

	/// <summary>
	/// Method returning the value of the next flag, indicating whether there is another jump.
	/// </summary>
	/// <returns>Value of the next flag</returns>
	bool get_next() const { return next; }

	/// <summary>
	/// Method returning the color of the piece making the jump.
	/// </summary>
	/// <returns>Color of the piece making the jump</returns>
	char get_piece() const { return j_piece; }

	/// <summary>
	/// Method returning the color of the piece that was jumped over.
	/// </summary>
	/// <returns>Color of the piece that was jumped over</returns>
	char get_jumped_piece() const { return jumped; }

	/// <summary>
	/// Method returning the x-coordinate of the starting field of the jump.
	/// </summary>
	/// <returns>x-coordinate of the starting field of the jump</returns>
	int get_xs() const { return xs; }

	/// <summary>
	/// Method returning the y-coordinate of the starting field of the jump.
	/// </summary>
	/// <returns>y-coordinate of the starting field of the jump</returns>
	int get_ys() const { return ys; }

	/// <summary>
	/// Method returning the x-coordinate of the destination field of the jump.
	/// </summary>
	/// <returns>x-coordinate of the destination field of the jump</returns>
	int get_xf() const { return xf; }

	/// <summary>
	/// Method returning the y-coordinate of the destination field of the jump.
	/// </summary>
	/// <returns>y-coordinate of the destination field of the jump</returns>
	int get_yf() const { return yf; }

	/// <summary>
	/// Method returning the x-coordinate of the jumped piece.
	/// </summary>
	/// <returns>x-coordinate of the jumped piece</returns>
	int get_xj() const { return xj; }

	/// <summary>
	/// Method returning the y-coordinate of the jumped piece.
	/// </summary>
	/// <returns>y-coordinate of the jumped piece</returns>
	int get_yj() const { return yj; }
};

/// <summary>
/// Class representing a single move of a piece on the board.
/// </summary>
class move {
	char piece; ///< Color of the piece making the move
	/*start*/
	int xs; ///< x-coordinate of the starting field of the move
	int ys; ///< y-coordinate of the starting field of the move
	/*finish*/
	int xf; ///< x-coordinate of the destination field of the move
	int yf; ///< y-coordinate of the destination field of the move

public:
	/// <summary>
	/// Constructor initializing a new move.
	/// </summary>
	/// <param name="p">Color of the piece making the move</param>
	/// <param name="x_s">x-coordinate of the starting field of the move</param>
	/// <param name="y_s">y-coordinate of the starting field of the move</param>
	/// <param name="x_f">x-coordinate of the destination field of the move</param>
	/// <param name="y_f">y-coordinate of the destination field of the move</param>
	move(char p, int x_s, int y_s, int x_f, int y_f)
		: piece(p), xs(x_s), ys(y_s), xf(x_f), yf(y_f) {
	}

	std::list<jump*> jumps; ///< List of jumps made as part of the move

	/// <summary>
	/// Copy constructor, creating a new move based on an existing one.
	/// </summary>
	/// <param name="copied">Reference to the move to be copied</param>
	move(move& copied)
		: piece(copied.get_piece()), xs(copied.get_xs()), ys(copied.get_ys()), xf(copied.get_xf()), yf(copied.get_yf()) {
		for (std::list<jump*>::iterator it = copied.jumps.begin(); it != copied.jumps.end(); ++it) {
			jump* copied_jump = new jump(*(*it));
			jumps.push_back(copied_jump);
		}
	}

	/// <summary>
	/// Destructor removing all jumps from the list of jumps.
	/// </summary>
	~move() {
		for (std::list<jump*>::iterator it = jumps.begin(); it != jumps.end(); ++it) {
			--(*it)->n_jump;
			if ((*it)->n_jump == 0) {
				delete (*it);
			}
		}
	}

	/// <summary>
	/// Method checking whether a "kinging" has occurred as a result of the move.
	/// </summary>
	/// <param name="piece_after">Color of the piece after the move</param>
	/// <returns>true if "kinging" occurred; false otherwise</returns>
	bool has_kinging_occured(char piece_after);

	/*getters*/

	/// <summary>
	/// Method returning the x-coordinate of the starting field of the move.
	/// </summary>
	/// <returns>x-coordinate of the starting field of the move</returns>
	int get_xs() const { return xs; }

	/// <summary>
	/// Method returning the y-coordinate of the starting field of the move.
	/// </summary>
	/// <returns>y-coordinate of the starting field of the move</returns>
	int get_ys() const { return ys; }

	/// <summary>
	/// Method returning the x-coordinate of the destination field of the move.
	/// </summary>
	/// <returns>x-coordinate of the destination field of the move</returns>
	int get_xf() const { return xf; }

	/// <summary>
	/// Method returning the y-coordinate of the destination field of the move.
	/// </summary>
	/// <returns>y-coordinate of the destination field of the move</returns>
	int get_yf() const { return yf; }

	/// <summary>
	/// Method returning the color of the piece making the move.
	/// </summary>
	/// <returns>Color of the piece making the move</returns>
	char get_piece() const { return piece; }

	/// <summary>
	/// Method setting the coordinates of the starting field of the move.
	/// </summary>
	/// <param name="x">New x-coordinate of the starting field of the move</param>
	/// <param name="y">New y-coordinate of the starting field of the move</param>
	void set_start(int x, int y) {
		xs = x;
		ys = y;
	}

	/// <summary>
	/// Method setting the coordinates of the destination field of the move.
	/// </summary>
	/// <param name="x">New x-coordinate of the destination field of the move</param>
	/// <param name="y">New y-coordinate of the destination field of the move</param>
	void set_finish(int x, int y) {
		xf = x;
		yf = y;
	}

	/// <summary>
	/// Method displaying information about the performed jumps.
	/// </summary>
	const void print_jumps();
	/// <summary>
	/// Operator overload for adding a jump to the list of jumps for the move.
	/// </summary>
	const move& operator+(jump* other);
};

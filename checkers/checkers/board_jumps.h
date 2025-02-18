#pragma once
#include"general.h"

/// <summary>
/// Class representing an object that finds all available jumps in a position. Inherits from the 'general' class.
/// </summary>
class board_jumps : public general {
private:
    /// <summary>
    /// Function adding jumps to an existing list of jumps. It checks if the same or reverse jump already exists in the list by comparing the jump keys we want to add with those already present in the list. 
    /// If this condition is not met, the function dynamically allocates a new jump object, adds it to the list, and checks if further jumps are possible from the square where the piece lands.
/// </summary>
    /// <param name="j_list"> List of pointers to jump objects </param>
    /// <param name="p"> char object indicating the color of the piece making the jump </param>
    /// <param name="xs"> 
    ///  X coordinate of the starting square </param>
    /// <param name="ys"> Y coordinate of the starting square </param>
    /// <param name="xj"> X coordinate of the jumped square </param>
    /// <param name="yj"> Y coordinate of the jumped square </param>
    /// <param name="xf"> X coordinate of the landing square </param>
    /// <param name="yf"> Y coordinate of the landing square </param>
    /// <param name="prev_jump"> Pointer to the jump that is the predecessor of the jump we want to add to the list </param>
    /// <returns> Returns true if the jump can be added to the jump list </returns>
    bool create_jump(std::list<jump*> j_list, char p, int xs, int ys, int xj, int yj, int xf, int yf, jump* prev_jump);

    /// <summary>
    /// This function dynamically allocates a new move object based on the list of jump pointers and adds this move to the list of possible moves. It also fills in the jumps with a pointer to the previous jump by iterating through the list of jump pointers.
/// </summary>
    /// <param name="j_list"> List of jump pointers based on which we want to create a move object and add it to the list </param>
    void create_jump_move(std::list<jump*> j_list);

    /// <summary>
    /// This function checks whether a jump can be made in the specified direction from the given square. If the jump is possible and the current list of jumps can be legally transformed into a move, 
    /// the function that creates a move for the current list of jump pointers is called. If the jump is possible, meaning all conditions are met, a function adding the jump to the current jump list is called.
/// </summary>
    /// <param name="jumping_piece"> char object indicating the piece color </param>
    /// <param name="xs"> X coordinate of the starting square </param>
    /// <param name="ys"> Y coordinate of the starting square </param>
    /// <param name="direction_y"> Direction in the horizontal orientation of the checked jump </param>
    /// <param name="direction_x"> Direction in the vertical orientation of the checked jump </param>
    /// <param name="prev"> Pointer to the jump preceding the checked jump </param>
    /// <param name="j_list"> List of pointers to all previous jumps </param>
    void check_jump(char jumping_piece, int xs, int ys, char direction_y, char direction_x, jump* prev, std::list<jump*> j_list);

public:
    /// <summary>
    /// Constructor for the board_jumps class using the constructor of the base class 'general'.
    /// </summary>
    /// <param name="b"> Reference to the board object passed </param>
    board_jumps(const board& b) : general(b) {
        /*std::cout << "board jumps finder created" << std::endl;*/
    }

    /// <summary>
    /// Destructor for the board_jumps class using the destructor of the base class 'general'.
    /// </summary>
    ~board_jumps() {
        /*std::cout << "board jumps finder destructed" << std::endl;*/
    }

    /// <summary>
    /// This function is used to load the list of moves found by the object into the selected list of moves. In my program, it concerns the list of available moves in the current turn created in the method 
    /// game::main_loop, which is the main function of the program. The function also deallocates the contents of the previous turn's available moves list.
    /// </summary>
    /// <param name="list"> Not necessarily an empty list of pointers to moves </param>
    void update_moves(std::list<move*>& list);

    /// <summary>
    /// Function that searches for possible jumps at the specified position on the board. It calls the check_jump function for possible directions at the specified position.
    /// </summary>
    /// <param name="xs"> X coordinate of the starting square </param>
    /// <param name="ys"> Y coordinate of the starting square </param>
    /// <param name="prev"> Pointer to the previous jump </param>
    /// <param name="j_list"> List of pointers to previous jumps </param>
    void avalilable_jump(int xs, int ys, jump* prev, std::list<jump*>& j_list);

    /// <summary>
    /// Function that iterates over the board and searches for jumps (by calling the available_jump function) for each position where a piece of the correct color is located.
    /// </summary>
    /// <returns> Returns true if no jumps are found </returns>
    bool avalilable_jumps();

    /// <summary>
    /// Function returning the current value of the 'turn' attribute indicating the current turn in the game.
    /// </summary>
    /// <returns> The current turn </returns>
    char get_turn() const {
        return turn;
    }
};

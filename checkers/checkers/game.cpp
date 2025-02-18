
#include "game.h"


void game::main_loop(bool iscomp1,bool iscomp2,int max_turn) {
	board new_board(iscomp1, iscomp2);
	board_jumps jump_finder(new_board);board_moves move_finder(new_board);
	command_control console('w',players[0].get_name(),players[1].get_name());
	std::list<move*> list;
	
	int cur_player_index = 0;
	console.start_game();
	
	for (int i = 0; i <max_turn; i++) {
			if (!load_jump_moves(list,jump_finder,new_board)) {
				load_moves(list, move_finder, new_board);
			}
			if (game_over(cur_player_index,int(list.size()))){
				if (console.end_game(0, cur_player_index + 1)) {
					game_lengths.add(i + 1);
					winners.add(players[(cur_player_index + 1) % 2].get_name());
					main_loop( iscomp1, iscomp2,max_turn);
				}
				return;
			}

			int cur_score = evaluate_score(new_board);
			console.start_round(cur_score, new_board.get_turn(),i+1);
			console.print_table(&new_board);
			if(list.size()!=1){
				std::unique_ptr<board> ptr = std::make_unique<board>(new_board);
				alpha_beta algo(ptr, jump_finder, move_finder, level[cur_player_index]);
				algo.search(list);
				if (level[cur_player_index] != 0 and types[cur_player_index]) {
					list.push_front(algo.get_best_move(true));
					
				}
			}
			new_board.make_move((players[cur_player_index]).choose_move(list , console));
			console.mid_round(new_board.get_previous_move(), new_board.get_turn());
			console.print_table(&new_board);
			console.move_strength(cur_score, evaluate_score(new_board));
			
			cur_player_index = (cur_player_index + 1) % 2;
			while (!list.empty()) {
				delete list.front();
				list.pop_front();
			}

	}

	winners.add("-");
	game_lengths.add(max_turn);

	if (console.end_game(1, 1)) {

		main_loop(iscomp1, iscomp2, max_turn);
	}
	else {

		console.print_previous_results(winners, game_lengths);
		

	}

	return;

	
}
game::game(bool is_comp_1, int level1, bool is_comp_2, int level2) {
	player player1('w', "blank"); player player2('b', "blank");
	command_control console('w',"blank","blank");
	std::cout << "Type in first player's name\n";
	player1.set_name(console.get_string());
	winners = {};
	game_lengths = {};
	std::cout << "Type in first player's name\n";
	player2.set_name(console.get_string());

	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	system("cls");
	level[0] = level1; level[1] = level2;
	if (is_comp_1) {
		if (level1 > 0) {
			player1.set_type(std::make_shared<smart_computer>());
		}
		else {
			player1.set_type(std::make_shared<random_comp>());
		}
		
	}
	else {
		level[0] = 0;
		player1.set_type(std::make_shared<human_player>());
	}
	if (is_comp_2) {
		if (level2 > 0) {
			player2.set_type(std::make_shared<smart_computer>());
		}
		else {

			player2.set_type(std::make_shared<random_comp>());
		}
	}
	else {

		level[0] = 0;
		player2.set_type(std::make_shared<human_player>());
	}
	types[0] = is_comp_1; types[1] = is_comp_2;
	players[0] = player1;
	players[1] = player2;
	score = 0;
};
	

bool game::load_moves(std::list<move*> &moves, board_moves move_finder,const board& new_board ) {
	move_finder.replace_board(new_board);
	move_finder.avalilable_moves();
	move_finder.update_moves(moves);
	if (!moves.empty()) {
		
		return true;
	}
	return false;
}
bool game::load_jump_moves(std::list<move*>& moves,  board_jumps jump_finder, const board& new_board) {
	jump_finder.replace_board(new_board);
	jump_finder.avalilable_jumps();
	jump_finder.update_moves(moves);
	if (!moves.empty()) {
		/*do wyrzycenia*/
		
		return true;
	}
	return false;
}
int game::evaluate_score(const board& b) {
	int white_score = 0;
	int black_score = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 4; j++) {
			if (tolower(b.get_piece(i, j)) == 'w') {
				if (b.get_piece(i, j) == 'W') {
					white_score += 3 * (100 + 10 * (i));
				}
				white_score += 100;
				if (on_wall(i, j)) {
					white_score += 3 * (7 - i);
				}

			}
			else if (tolower(b.get_piece(i, j)) == 'b') {
				if (b.get_piece(i, j) == 'B') {
					black_score -= 3 * (100 + 10 * (7 - i));
				}
				black_score -= 100;
				if (on_wall(i, j)) {
					black_score -= 5 * i;
				}
			}
		}
	}
	if (black_score == 0) {
		return 100000;
	}
	else if (white_score == 0) {
		return -100000;
	}
	return white_score + black_score;
}

void game::start(int max_turn) {
	main_loop(types[0], types[1], max_turn);
}
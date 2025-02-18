
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
/// Klasa reprezentujaca gre w warcaby.
/// /// </summary>
class game {
            float score = 0; ///< Aktualny wynik gry
            bool types[2]; ///< Typy graczy (prawda dla komputera, falsz dla czlowieka)
            int level[2]; ///< Poziomy trudnosci graczy
            player players[2]; ///< Tablica graczy
            // Nested templated container class for game results
            game_results_container<std::string> winners; ///< Kontener na wyniki gry (zwyciezcy)
            game_results_container<int> game_lengths; ///< Kontener na dlugosci gier

            /// <summary>
            /// Funkcja oceniajaca aktualny stan planszy.
            /// </summary>
            /// <param name="b">Obiekt planszy</param>
            /// <returns>Wartosc oceny planszy</returns>
            int evaluate_score(const board& b);

            /// <summary>
            /// Funkcja sprawdzajaca, czy dany pionek znajduje sie przy krawedzi planszy.
            /// </summary>
            /// <param name="i">Indeks wiersza</param>
            /// <param name="j">Indeks kolumny</param>
            /// <returns>Prawda, jesli pionek znajduje sie przy krawedzi, w przeciwnym razie falsz</returns>
            bool on_wall(int i, int j);

            /// <summary>
            /// Glowna petla gry.
            /// </summary>
            /// <param name="iscomp1">Czy pierwszy gracz jest komputerem</param>
            /// <param name="iscomp2">Czy drugi gracz jest komputerem</param>
            /// <param name="max_turn">Maksymalna liczba tur</param>
            void main_loop(bool iscomp1, bool iscomp2, int max_turn);

            /// <summary>
            /// Funkcja wypelniajaca liste wskaznikow do ruchu skokami dostepnymi w pozycji.
            /// </summary>
            /// <param name="moves">Lista wskaznikow do ruchu, ktora chcemy wypelnic</param>
            /// <param name="jump_finder">Obiekt sluzacy do znalezienia skokow</param>
            /// <param name="new_board">Obiekt typu board zawierajacy informacje o stanie na planszy</param>
            /// <returns>Prawda, gdy zostanie znaleziony skok, falsz, gdy nie</returns>
            bool load_jump_moves(std::list<move*>& moves, board_jumps jump_finder, const board& new_board);

            /// <summary>
            /// Funkcja wypelniajaca liste wskaznikow do ruchu ruchami dostepnymi w pozycji.
            /// </summary>
            /// <param name="moves">Lista wskaznikow do ruchu, ktora chcemy wypelnic</param>
            /// <param name="move_finder">Obiekt sluzacy do znalezienia ruchow</param>
            /// <param name="new_board">Obiekt typu board zawierajacy informacje o stanie na planszy</param>
            /// <returns>Prawda, gdy zostanie znaleziony ruch, falsz, gdy nie</returns>
            bool load_moves(std::list<move*>& moves, board_moves move_finder, const board& new_board);

        public:
            /// <summary>
            /// Konstruktor inicjujacy nowa gre.
            /// </summary>
            /// <param name="is_comp_1">Czy pierwszy gracz jest komputerem</param>
            /// <param name="level1">Poziom trudnosci pierwszego gracza. 0 oznacza gracza fizycznego</param>
            /// <param name="is_comp_2">Czy drugi gracz jest komputerem.</param>
            /// <param name="level2">Poziom trudnosci drugiego gracza. 0 oznacza gracza fizycznego</param>
            game(bool is_comp_1, int level1, bool is_comp_2, int level2);

            /// <summary>
            /// Funkcja rozpoczynajaca gre.
            /// </summary>
            void start(); 

            /// <summary>
            /// Funkcja sprawdzajaca, czy gra sie zakonczyla.
            /// </summary>
            /// <param name="player_index">Indeks gracza</param>
            /// <param name="list_size">Rozmiar listy ruchow</param>
            /// <returns>Prawda, jesli gra sie zakonczyla, w przeciwnym razie falsz</returns>
            bool game_over(int player_index, int list_size);
        };

	



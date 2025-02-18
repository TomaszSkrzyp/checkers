#pragma once
#include <memory>
#include "board_jumps.h"
#include "board_moves.h"

/// <summary>
/// Klasa realizujaca algorytm znajdywania najlepszego ruchu. Wykorzystuje algorytm alpha-beta pruning.
/// </summary>
class alpha_beta {
private:
    int MaxIterDepth; // Maksymalna glebokosc iteracji algorytmu

    std::unique_ptr<board> current_b; // Aktualny stan planszy

    move* bestM; // Najlepszy ruch uzyskany przez algorytm
    move* temp_bestM; // Tymczasowy najlepszy ruch

    int max_depth; // Maksymalna glebokosc przeszukiwania
    int cur_depth; // Obecna glebokosc przeszukiwania
    bool reached_end; // Flaga informujaca, czy osiagnieto koniec przeszukiwania

    board_jumps jump_finder; // Obiekt do znajdowania skokow
    board_moves move_finder; // Obiekt do znajdowania zwyklych ruchow

    /// <summary>
    /// Metoda sluzaca do wydrukowania ruchu.
    /// </summary>
    /// <param name="v">Wskaznik na ruch, ktory chcemy wydrukowac</param>
    void print_move(move* v);

    /// <summary>
    /// Metoda sprawdzajaca, czy podane wspolrzedne znajduja sie na krawedzi planszy.
    /// </summary>
    /// <param name="x">Wspolrzedna X</param>
    /// <param name="y">Wspolrzedna Y</param>
    /// <returns>true, jesli wspolrzedne sa na krawedzi planszy; w przeciwnym razie false</returns>
    bool on_wall(int x, int y);

    /// <summary>
    /// Metoda oceniajaca wynik dla danej planszy.
    /// </summary>
    /// <param name="b">Referencja do obiektu planszy, dla ktorego obliczany jest wynik</param>
    /// <returns>Ocena wyniku dla danej planszy</returns>
    int evaluate_score(const board& b);

    /// <summary>
    /// Metoda wypelniajaca liste wskaznikow do ruchu ruchami dostepnymi w danej pozycji.
    /// </summary>
    /// <param name="moves">Lista wskaznikow do ruchu, ktora chcemy wypelnic</param>
    /// <param name="jump_finder">Obiekt sluzacy do znajdowania skokow</param>
    /// <param name="new_board">Obiekt typu board zawierajacy informacje o stanie na planszy</param>
    /// <returns>true, gdy zostanie znaleziony ruch; false, gdy nie</returns>
    bool load_jump_moves(std::list<move*>& moves, board_jumps& jump_finder, const board& new_board);

    /// <summary>
    /// Metoda wypelniajaca liste wskaznikow do ruchu ruchami dostepnymi w danej pozycji.
    /// </summary>
    /// <param name="moves">Lista wskaznikow do ruchu, ktora chcemy wypelnic</param>
    /// <param name="move_finder">Obiekt sluzacy do znajdowania ruchow</param>
    /// <param name="new_board">Obiekt typu board zawierajacy informacje o stanie na planszy</param>
    /// <returns>true, gdy zostanie znaleziony ruch; false, gdy nie</returns>
    bool load_moves(std::list<move*>& moves, board_moves& move_finder, const board& new_board);

public:
    /// <summary>
    /// Konstruktor klasy alpha_beta. Inicjalizuje obiekt klasy alpha_beta na podstawie przekazanych parametrow.
    /// </summary>
    /// <param name="board_ptr">Unique pointer do obiektu board, na ktorym beda sprawdzane ruchy</param>
    /// <param name="jump_finding_tool">Obiekt do znajdowania skokow</param>
    /// <param name="move_finding_tool">Obiekt do znajdowania ruchow</param>
    /// <param name="max">Maksymalna glebokosc iteracji algorytmu</param>
    alpha_beta(std::unique_ptr<board>& board_ptr, board_jumps& jump_finding_tool, board_moves& move_finding_tool, int max)
        : current_b(std::move(board_ptr)), bestM(nullptr), temp_bestM(nullptr), max_depth(0), cur_depth(0), reached_end(false),
        jump_finder(jump_finding_tool), move_finder(move_finding_tool), MaxIterDepth(max) {}

    /// <summary>
    /// Metoda realizujaca algorytm "alpha-beta pruning". Sprawdza ona kazda kombinacje ruchow do podanej glebokosci, chyba ze napotka sytuacje, w ktorej dalsze poszukiwanie jest bezcelowe.
    /// Zwraca wynik, jaki uda sie osiagnac w tej kombinacji.
    /// </summary>
    /// <param name="b">Unique pointer do obiektu board, na ktorym beda sprawdzane ruchy. Obiekty te beda tworzone rekurencyjnie w czasie trwania algorytmu</param>
    /// <param name="depth">Glebokosc na ktorej znajduje sie algorytm</param>
    /// <param name="alpha">Wartosc alpha uzywana w algorytmie, mozna ja zdefiniowac jako najlepsza dotychczas znaleziona przez kolor bialy wartosc wyniku</param>
    /// <param name="beta">Wartosc beta uzywana w algorytmie, mozna ja zdefiniowac jako najlepsza dotychczas znaleziona przez kolor czarny wartosc wyniku</param>
    /// <returns>Najlepszy wynik osiagniety w danym poziomie przeszukiwania</returns>
    int algorythm(std::unique_ptr<board>& b, int depth, int alpha, int beta);

    /// <summary>
    /// Metoda zwracajaca najlepszy ruch znaleziony przez algorytm.
    /// </summary>
    /// <param name="print">Flaga okreslajaca, czy wydrukowac ruch</param>
    /// <returns>Najlepszy ruch</returns>
    move* get_best_move(bool print);

    /// <summary>
    /// Metoda przeszukujaca liste ruchow i aktualizujaca najlepszy ruch.
    /// </summary>
    /// <param name="m_list">Lista ruchow do przeszukania</param>
    void search(std::list<move*> m_list);
};

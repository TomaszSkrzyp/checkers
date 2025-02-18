#pragma once
#include <iostream>
#include <list>
#include <vector>
#include "moves_jumps.h"

/// <summary>
/// Klasa przechowujaca informacje na temat obecnej zawartosci planszy.
/// </summary>
class board {
private:
    char arr[8][4]; // Tablica charow zawierajaca informacje o bierkach na planszy, zoptymalizowana do 8x4 dla przyspieszenia dzialania
    char turn; // Obecna tura - 'w' oznacza kolejke bialych, 'b' czarnych
    bool is_computer[2]; // Dwuelementowa tablica informujaca, czy ktorys z graczy jest komputerem (true dla komputera)
    std::list<move*> previous_moves; // Lista wskaznikow do wszystkich wykonanych ruchow

    /// <summary>
    /// Funkcja sprawdzajaca, czy na podanych wspolrzednych nalezy dokonac "koronowania".
    /// </summary>
    /// <param name="x">Wspolrzedna x sprawdzanego pola</param>
    /// <param name="y">Wspolrzedna y sprawdzanego pola</param>
    void check_crown(const int& x, const int& y);

    /// <summary>
    /// Funkcja ustawiajaca bierki na poczatkowych pozycjach i czysciaca zawartosc listy poprzednich ruchow.
    /// </summary>
    void reset();

public:
    /// <summary>
    /// Konstruktor uzupelniajacy tablice na pozycje poczatkowe.
    /// </summary>
    /// <param name="w_is_computer">Informacja, czy gracz o kolorze bialym jest komputerem</param>
    /// <param name="b_is_computer">Informacja, czy gracz o kolorze czarnym jest komputerem</param>
    board(char w_is_computer, char b_is_computer);

    /// <summary>
    /// Destruktor obiektu board.
    /// </summary>
    ~board();

    /// <summary>
    /// Konstruktor kopiujacy obiektu board.
    /// </summary>
    board(const board& board);

    /// <summary>
    /// Metoda zwracajaca kolor bierki na podanych wspolrzednych.
    /// </summary>
    /// <param name="x">Wspolrzedna x sprawdzanego pola</param>
    /// <param name="y">Wspolrzedna y sprawdzanego pola</param>
    /// <returns>Char oznaczajacy kolor bierki</returns>
    char get_piece(int x, int y) const;

    /// <summary>
    /// Metoda zwracajaca wskaznik do poprzedniego ruchu.
    /// </summary>
    /// <returns>Wskaznik do poprzedniego ruchu</returns>
    move* get_previous_move() const;

    /// <summary>
    /// Metoda wykonujaca podany ruch na planszy.
    /// </summary>
    /// <param name="chosen_move">Wskaznik do ruchu, ktory ma byc wykonany</param>
    void make_move(move* chosen_move);

    /// <summary>
    /// Metoda cofajaca ostatni wykonany ruch na planszy.
    /// </summary>
    void undo_move();

    /// <summary>
    /// Metoda zmieniajaca ture gry (kolor gracza).
    /// </summary>
    void change_turn();

    /// <summary>
    /// Metoda zwracajaca obecny kolor gracza, ktory ma wykonac ruch.
    /// </summary>
    /// <returns>Char reprezentujacy obecny kolor gracza</returns>
    char get_turn() const;

    /// <summary>
    /// Metoda sprawdzajaca, czy gracz o podanym indeksie jest komputerem.
    /// </summary>
    /// <param name="ind">Indeks gracza (0 lub 1)</param>
    /// <returns>true, jesli gracz jest komputerem; false, jesli jest czlowiekiem</returns>
    bool is_player_computer(int ind) const;
};

/// <summary>
/// Klasa kontenera przechowujacego wyniki gry.
/// </summary>
template <typename T>
class game_results_container {
private:
    std::vector<T> game_data; // Wektor przechowujacy dane o grze

public:
    /// <summary>
    /// Metoda dodajaca dane o grze do kontenera.
    /// </summary>
    /// <param name="data">Dane o grze do dodania</param>
    void add(const T& data) {
        game_data.push_back(data);
    }

    /// <summary>
    /// Metoda zwracajaca dane o grze z danego indeksu.
    /// </summary>
    /// <param name="index">Indeks danych do pobrania</param>
    /// <returns>Referencja do danych o grze z podanego indeksu</returns>
    const T& get_data(size_t index) {
        return game_data[index];
    }

    /// <summary>
    /// Metoda zwracajaca liczbe elementow przechowywanych w kontenerze.
    /// </summary>
    /// <returns>Liczba elementow w kontenerze</returns>
    const size_t size() {
        return game_data.size();
    }
};

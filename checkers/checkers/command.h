#pragma once

/// <param name="xs"> wpolrzedna x pola startowego </param>
/// <param name="ys"> wpolrzedna y pola startowego </param>
/// <param name="xj"> wpolrzedna x przeskakiwanego pola </param>
/// <param name="yj"> wpolrzedna y przeskakiwanego pola </param>
/// <param name="xf"> wpolrzedna x pola koncowego </param>
/// <param name="yf"> wpolrzedna y pola koncowego </param>
#include "board_record.h"

#include <vector>
#include <thread>
#include <chrono> 


/// Obiekt sluzacy do obslugi wejscia i wyjscia.

class command_control {
	std::list<move*> list; /// Lista mozliwych ruchow.
	std::string players[2]; /// "Imiona" zawodnikow bioracych udzial w grze, przechowywane w tablicy stringow.
	char turn; /// Informacja o obecnej turze, 'w' oznacza ture bialych, 'b' oznacza ture czarnych

	/// <summary>
	/// Funkcja sprawdzajaca, czy podany ruch jest legalny. Sprawdza rowniez "skoki" o dlugosci jeden bedace czescia dluzszej sekwencji skokow.
	/// </summary>
	/// <param name="keys"> Lista kluczy zawierajacych informacje o skoku. Funkcja aktualizuje te liste w przypadku dluzszej sekwencji skokow. </param>
	/// <param name="xs"> Wspolrzedna X pola startowego </param>
	/// <param name="ys"> Wspolrzedna Y pola startowego </param>
	/// <param name="xj"> Wspolrzedna X przeskakiwanego pola </param>
	/// <param name="yj"> Wspolrzedna Y przeskakiwanego pola </param>
	/// <param name="xf"> Wspolrzedna X pola koncowego </param>
	/// <param name="yf"> Wspolrzedna Y pola koncowego </param>
	/// <param name="answer"> Wskaznik do poprawnego ruchu, przekazywany przez referencje, co pozwala "zwrocic" poprawny ruch. </param>
	/// <param name="reset"> Informacja o koniecznosci zresetowania funkcji pobierania ruchu od uzytkownika. </param>
	/// <returns> True lub false w zaleznosci od tego, czy znaleziono poprawny ruch. </returns>
	bool one_move_request(std::list<int>& keys, int& xs, int& ys, int& xj, int& yj, int& xf, int& yf, move*& answer, bool& reset);

	/// <summary>
	/// Funkcja pobierajaca pole od uzytkownika w postaci pozycji na planszy i konwertujaca do wartosci int bedacej indeksem.
	/// </summary>
	/// <param name="x"> Wspolrzedna X pola, pobierana jako referencja z uwagi na potrzebe zaktualizowania wartosci przekonwertowanej. </param>
	/// <param name="y"> Wspolrzedna Y pola, pobierana jako referencja z uwagi na potrzebe zaktualizowania wartosci przekonwertowanej. </param>
	void get_pos_from_command(int& x, int& y);

	/// <summary>
	/// Funkcja wyswietlajaca ruch w postaci zgodnej z pozycjami na planszy. 
	/// </summary>
	/// <param name="v"> Wskaznik do ruchu, ktory chcemy wyswietlic. </param>
	void print_single_move(move* v) const;

	/// <summary>
	/// Funkcja "zmazujaca" n linii z terminalu.
	/// </summary>
	/// <param name="n_lines"> Ilosc linii do "zmazania". </param>
	void clear_lines(int n_lines) const;

	/// <summary>
	/// Funkcja ustalajaca wspolrzedna Y przeskakiwanego pola. Przez kompresje planszy nie jest to trywialne zadanie. Wspolrzedna X jest zawsze srednia arytmetyczna xs i xf.
	/// </summary>
	/// <param name="yj"> Wspolrzedna Y przeskakiwanego pola, pobierana przez referencje. </param>
	/// <param name="xs"> Wspolrzedna X pola startowego </param>
	/// <param name="ys"> Wspolrzedna Y pola startowego </param>
	/// <param name="yf"> Wspolrzedna Y pola koncowego </param>
	void find_y_jumped(int& yj, int xs, int ys, int yf);

	/// <summary>
	/// Funkcja ustalajaca wartosc klucza dla skoku. Wartosc ta zawiera informacje o punkcie startowym, przeskakiwanym i koncowym.
	/// </summary>
	/// <param name="xs"> Wspolrzedna X pola startowego </param>
	/// <param name="ys"> Wspolrzedna Y pola startowego </param>
	/// <param name="xj"> Wspolrzedna X przeskakiwanego pola </param>
	/// <param name="yj"> Wspolrzedna Y przeskakiwanego pola </param>
	/// <param name="xf"> Wspolrzedna X pola koncowego </param>
	/// <param name="yf"> Wspolrzedna Y pola koncowego </param>
	/// <returns></returns>
	const int hashed_jump(int xs, int ys, int xj, int yj, int xf, int yf);

	/// <summary>
	/// Funkcja obracajaca wartosc klucza.
	/// </summary>
	/// <param name="i"> Wartosc klucza </param>
	/// <returns> Obrocona wartosc klucza </returns>
	const int rev_hash(int i);

public:
	/// <summary>
	/// Konstruktor obiektu command_control.
	/// </summary>
	/// <param name="t"> Obecna tura </param>
	/// <param name="p1"> "Imie" pierwszego zawodnika </param>
	/// <param name="p2"> "Imie" drugiego zawodnika </param>
	command_control(char t, const std::string& p1, const std::string& p2) : turn(t) {
		players[0] = p1; players[1] = p2;
	} 

	/// <summary>
	/// Destruktor niszczacy obiekt command control. Nie ma potrzeby dealokowania wskaznikow znajdujacych sie w liscie, poniewaz zajmuje sie tym inna funkcja.
	/// </summary>
	~command_control() {
		while (!list.empty()) {
			list.pop_front();
		}
	}

	/// <summary>
	/// Funkcja obliczajaca wartosc wykonanego ruchu.
	/// </summary>
	/// <param name="cur_score"> Wynik przed ruchem </param>
	/// <param name="score_after"> Wynik po ruchu </param>
	void move_strength(int cur_score, int score_after) const;

	/// <summary>
	/// Funkcja pobierajaca od uzytkownika ruch. Dziala wspolnie z funkcja one_move_request.
	/// </summary>
	/// <returns> Zwraca poprawny ruch </returns>
	move* move_request();

	/// <summary>
	/// Funkcja informujaca o przydziale graczom koloru.
	/// </summary>
	void start_game() const;

	/// <summary>
	/// Funkcja informujaca o obecnej kolejce oraz wyniku.
	/// </summary>
	/// <param name="score"> Obecny wynik </param>
	/// <param name="turn"> Obecna kolej </param>
	/// <param name="num"> Numer ruchu </param>
	void start_round(int score, char turn, int num) const;

	/// <summary>
	/// Funkcja informujaca o wlasnie wykonanym ruchu.
	/// </summary>
	/// <param name="m"> Wskaznik do ruchu </param>
	/// <param name="turn"> Obecna kolej </param>
	void mid_round(move* m, char turn) const;

	/// <summary>
	/// Funkcja informujaca o koncu gry, ewentualnym zwyciezcy oraz wysylajaca zapytanie o kolejna partie.
	/// </summary>
	/// <param name="is_draw"> Informuje o ewentualnym remisie </param>
	/// <param name="index"> Informuje o indeksie zwyciezcy </param>
	/// <returns> Zwraca true, gdy gracz wykazuje chec zagrania kolejnej partii </returns>
	bool end_game(bool is_draw, int index) const;

	/// <summary>
	/// Funkcja wyswietlajaca ruch w postaci zgodnej z pozycjami na planszy, pomijajac ewentualne przeskoczone pola.
	/// </summary>
	/// <param name="v"> Wskaznik do ruchu, ktory chcemy wyswietlic </param>
	void this_move_command(move* m) const;

	/// <summary>
	/// Funkcja wyswietlajaca obecna tablice.
	/// </summary>
	/// <param name="b"> Wskaznik do obiektu klasy board zawierajacej plansze, ktora chcemy wyswietlic </param>
	void print_table(const board* b) const;

	/// <summary>
	/// Aktualizuje liste ruchow posiadanych przez obiekt command control oraz zmienia ture.
	/// </summary>
	/// <param name="new_list"> Referencja do listy wskaznikow do ruchow, ktora chcemy wgrac do obiektu command control </param>
	/// <param name="t"> Obecna tura </param>
	void replace_moves(const std::list<move*>& new_list, char t);

	/// <summary>
	/// Wyswietla liste dostepnych ruchow.
	/// </summary>
	void print_move() const;

	/// <summary>
	/// Funkcja zmieniajaca atrybut obecnej tury.
	/// </summary>
	/// <param name="t"> Nowa wartosc tury </param>
	void replace_turn(char t) {
		turn = t;
	}

	/// <summary>
	/// Funkcja zwracajaca wartosc tury.
	/// </summary>
	/// <returns> Wartosc tury </returns>
	char get_turn() const {
		return turn;
	}

	/// <summary>
	/// Funkcja pobierajaca dane wejsciowe i konwertujaca je do typu string.
	/// </summary>
	/// <returns> Dane wejsciowe w formie stringa </returns>
	std::string get_string() const;

	/// <summary>
	/// Funkcja drukujaca wartosci wszystkich poprzednich gier.
	/// </summary>
	void print_previous_results(game_results_container<std::string>& winners, game_results_container<int>& game_lengths) const;
	
};
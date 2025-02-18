#pragma once
#include "moves_jumps.h"
#include "command.h"
#include <random>
/// <summary>
/// Abstrakcyjna klasa zawodnika, reprezentujaca gracza w grze.
/// </summary>
class player_type {
public:
	/// <summary>
	/// Wirtualna metoda czysto wirtualna, ktora musi byc zaimplementowana w klasach pochodnych.
	/// Sluzy do wyboru ruchu z dostepnych ruchow.
	/// </summary>
	/// <param name="moves">Lista dostepnych ruchow.</param>
	/// <param name="console">Referencja do obiektu kontrolujacego komendy.</param>
	/// <returns>Wskaznik na wybrany ruch.</returns>
	virtual move* choose_move( std::list<move*> moves, command_control& console) = 0;

	/// <summary>
	/// Wirtualny destruktor klasy bazowej, zapewniajacy poprawne niszczenie obiektow klas pochodnych.
	/// </summary>
	virtual ~player_type() {}
};

/// <summary>
/// Klasa reprezentujaca gracza komputerowego, ktory wybiera ruch losowo.
/// Dziedziczy po abstrakcyjnej klasie player_type.
/// </summary>
class random_comp : public player_type {
	/// <summary>
	/// Obiekt sluzacy do generowania losowych liczb.
	/// </summary>
	std::random_device move_choser;

public:
	/// <summary>
	/// Metoda wybiera losowy ruch z dostepnych ruchow dla gracza komputerowego.
	/// </summary>
	/// <param name="moves">Lista dostepnych ruchow.</param>
	/// <param name="console">Referencja do obiektu kontrolujacego komendy.</param>
	/// <returns>Wskaznik na wybrany losowy ruch.</returns>
	move* choose_move( std::list<move*> moves, command_control& console) override;

};
/// <summary>
/// Klasa reprezentujaca inteligentnego gracza komputerowego, ktory podejmuje bardziej zaawansowane decyzje w wyborze ruchu. Dziedziczy po abstrakcyjnej klasie player_type.
/// </summary>
class smart_computer : public player_type {

public:
	/// <summary>
	/// Metoda wybiera ruch z dostepnych ruchow dla inteligentnego gracza komputerowego.
	/// Implementacja tej metody powinna uwzgledniac strategie podejmowania decyzji przez komputer.
	/// </summary>
	/// <param name="moves">Lista dostepnych ruchow.</param>
	/// <param name="console">Referencja do obiektu kontrolujacego komendy.</param>
	/// <returns>Wskaznik na wybrany ruch.</returns>
	move* choose_move( std::list<move*> moves, command_control& console) override;
};
/// <summary>
/// Klasa reprezentujaca inteligentnego gracza komputerowego, ktory podejmuje decyzje na podstawie wejscia uzytkownika. Dziedziczy po abstrakcyjnej klasie player_type.
/// </summary>
class human_player : public player_type {

public:
	/// <summary>
	/// Metoda definiuje w jaki sposob pobierane sa dane od uzytkownika.
	/// </summary>
	/// <param name="moves">Lista dostepnych ruchow.</param>
	/// <param name="console">Referencja do obiektu kontrolujacego komendy.</param>
	/// <returns>Wskaznik na wybrany ruch.</returns>
	move* choose_move(std::list<move*> moves, command_control& console) override;
};


/// <summary>
/// Klasa reprezentujaca gracza w grze.
/// </summary>
class player {
	char color; ///< Kolor gracza.
	std::string name; ///< Nazwa gracza.

	std::shared_ptr<player_type> p_type; ///< Wskaznik inteligentnego typu gracza.

public:
	/// <summary>
	/// Konstruktor domyslny.
	/// </summary>
	player() = default;

	/// <summary>
	/// Konstruktor inicjalizujacy gracza z podanym kolorem i nazwa.
	/// </summary>
	/// <param name="c">Kolor gracza.</param>
	/// <param name="player_name">Nazwa gracza.</param>
	player(char c, const std::string& player_name) : color(c), name(player_name) {
	}

	/// <summary>
	/// Ustawia typ gracza na podany typ.
	/// </summary>
	/// <param name="p_type">Wskaznik na obiekt typu gracza.</param>
	void set_type(std::shared_ptr<player_type> p_type) {
		this->p_type = p_type;
	}

	/// <summary>
	/// Wybiera ruch z listy dostepnych ruchow przy uzyciu zdefiniowanego typu gracza.
	/// </summary>
	/// <param name="list">Lista dostepnych ruchow.</param>
	/// <param name="console">Referencja do obiektu kontrolujacego komendy.</param>
	/// <returns>Wskaznik na wybrany ruch.</returns>
	move* choose_move(std::list<move*> list, command_control& console) {
		// Zastepuje ruchy w konsoli dla tego gracza
		console.replace_moves(list, color);
		// Wybiera ruch przy uzyciu zdefiniowanego typu gracza
		return p_type->choose_move(list, console);
	}

	/// <summary>
	/// Zwraca nazwe gracza.
	/// </summary>
	/// <returns>Nazwa gracza.</returns>
	std::string get_name() {
		return name;
	}

	/// <summary>
	/// Ustawia nowa nazwe gracza.
	/// </summary>
	/// <param name="new_name">Nowa nazwa gracza.</param>
	void set_name(std::string new_name) {
		name = new_name;
	}
};
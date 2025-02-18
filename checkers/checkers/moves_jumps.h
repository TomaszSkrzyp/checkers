#pragma once
#include <list>
#include <iostream>

/// <summary>
/// Klasa reprezentujaca pojedynczy skok pionka na planszy.
/// </summary>
class jump {
	char j_piece; ///< Kolor pionka wykonujacego skok
	jump* prev; ///< Wskaznik do poprzedniego skoku
	bool next; ///< Flaga okreslajaca, czy istnieje kolejny skok
	int key = 0; ///< Klucz identyfikacyjny skoku
	/*przeskoczone piony*/
	char jumped; ///< Kolor pionka, ktory zostal przeskoczony
	int xj; ///< Wspolrzedna x przeskoczonego pionka
	int yj; ///< Wspolrzedna y przeskoczonego pionka
	/*start i finish*/
	int xs; ///< Wspolrzedna x pola startowego skoku
	int ys; ///< Wspolrzedna y pola startowego skoku

	int xf; ///< Wspolrzedna x pola docelowego skoku
	int yf; ///< Wspolrzedna y pola docelowego skoku

public:
	int n_jump; ///< Licznik referencji do obiektu skoku

	/// <summary>
	/// Konstruktor tworzacy obiekt skoku.
	/// </summary>
	/// <param name="j_p">Kolor pionka wykonujacego skok</param>
	/// <param name="j">Kolor pionka, ktory zostal przeskoczony</param>
	/// <param name="x_j">Wspolrzedna x przeskoczonego pionka</param>
	/// <param name="y_j">Wspolrzedna y przeskoczonego pionka</param>
	/// <param name="x_s">Wspolrzedna x pola startowego skoku</param>
	/// <param name="y_s">Wspolrzedna y pola startowego skoku</param>
	/// <param name="x_f">Wspolrzedna x pola docelowego skoku</param>
	/// <param name="y_f">Wspolrzedna y pola docelowego skoku</param>
	/// <param name="p">Wskaznik do poprzedniego skoku</param>
	/// <param name="k">Klucz identyfikacyjny skoku</param>
	jump(char j_p, char j, int x_j, int y_j, int x_s, int y_s, int x_f, int y_f, jump* p, int k)
		: prev(p), j_piece(j_p), jumped(j), xj(x_j), yj(y_j), n_jump(0), next(false), xs(x_s), ys(y_s), xf(x_f), yf(y_f), key(k) {
	}

	/// <summary>
	/// Metoda zwracajaca klucz identyfikacyjny skoku.
	/// </summary>
	/// <returns>Klucz identyfikacyjny skoku</returns>
	int get_key() const { return key; }

	/// <summary>
	/// Metoda zwracajaca wskaznik do poprzedniego skoku.
	/// </summary>
	/// <returns>Wskaznik do poprzedniego skoku</returns>
	jump* get_prev() { return prev; }

	/// <summary>
	/// Metoda ustawiajaca flage okreslajaca, czy istnieje kolejny skok.
	/// </summary>
	/// <param name="new_next">Nowa wartosc flagi next</param>
	void set_next(bool new_next) { next = new_next; }

	/// <summary>
	/// Metoda zwracajaca wartosc flagi next, okreslajacej, czy istnieje kolejny skok.
	/// </summary>
	/// <returns>Wartosc flagi next</returns>
	bool get_next() const { return next; }

	/// <summary>
	/// Metoda zwracajaca kolor pionka wykonujacego skok.
	/// </summary>
	/// <returns>Kolor pionka wykonujacego skok</returns>
	char get_piece() const { return j_piece; }

	/// <summary>
	/// Metoda zwracajaca kolor pionka, ktory zostal przeskoczony.
	/// </summary>
	/// <returns>Kolor pionka, ktory zostal przeskoczony</returns>
	char get_jumped_piece() const { return jumped; }

	/// <summary>
	/// Metoda zwracajaca wspolrzedna x pola startowego skoku.
	/// </summary>
	/// <returns>Wspolrzedna x pola startowego skoku</returns>
	int get_xs() const { return xs; }

	/// <summary>
	/// Metoda zwracajaca wspolrzedna y pola startowego skoku.
	/// </summary>
	/// <returns>Wspolrzedna y pola startowego skoku</returns>
	int get_ys() const { return ys; }

	/// <summary>
	/// Metoda zwracajaca wspolrzedna x pola docelowego skoku.
	/// </summary>
	/// <returns>Wspolrzedna x pola docelowego skoku</returns>
	int get_xf() const { return xf; }

	/// <summary>
	/// Metoda zwracajaca wspolrzedna y pola docelowego skoku.
	/// </summary>
	/// <returns>Wspolrzedna y pola docelowego skoku</returns>
	int get_yf() const { return yf; }

	/// <summary>
	/// Metoda zwracajaca wspolrzedna x przeskoczonego pionka.
	/// </summary>
	/// <returns>Wspolrzedna x przeskoczonego pionka</returns>
	int get_xj() const { return xj; }

	/// <summary>
	/// Metoda zwracajaca wspolrzedna y przeskoczonego pionka.
	/// </summary>
	/// <returns>Wspolrzedna y przeskoczonego pionka</returns>
	int get_yj() const { return yj; }
};
#pragma once
#include <list>
#include <iostream>

/// <summary>
/// Klasa reprezentujaca pojedynczy ruch pionka na planszy.
/// </summary>
class move {
	char piece; ///< Kolor pionka wykonujacego ruch
	/*start*/
	int xs; ///< Wspolrzedna x pola startowego ruchu
	int ys; ///< Wspolrzedna y pola startowego ruchu
	/*finisz*/
	int xf; ///< Wspolrzedna x pola docelowego ruchu
	int yf; ///< Wspolrzedna y pola docelowego ruchu

public:
	/// <summary>
	/// Konstruktor inicjujacy nowy ruch.
	/// </summary>
	/// <param name="p">Kolor pionka wykonujacego ruch</param>
	/// <param name="x_s">Wspolrzedna x pola startowego ruchu</param>
	/// <param name="y_s">Wspolrzedna y pola startowego ruchu</param>
	/// <param name="x_f">Wspolrzedna x pola docelowego ruchu</param>
	/// <param name="y_f">Wspolrzedna y pola docelowego ruchu</param>
	move(char p, int x_s, int y_s, int x_f, int y_f)
		: piece(p), xs(x_s), ys(y_s), xf(x_f), yf(y_f) {
	}

	std::list<jump*> jumps; ///< Lista skokow wykonanych w ramach ruchu

	/// <summary>
	/// Konstruktor kopiujacy, tworzacy nowy ruch na podstawie istniejacego.
	/// </summary>
	/// <param name="copied">Referencja do kopii ruchu, ktora nalezy skopiowac</param>
	move(move& copied)
		: piece(copied.get_piece()), xs(copied.get_xs()), ys(copied.get_ys()), xf(copied.get_xf()), yf(copied.get_yf()) {
		for (std::list<jump*>::iterator it = copied.jumps.begin(); it != copied.jumps.end(); ++it) {
			jump* copied_jump = new jump(*(*it));
			jumps.push_back(copied_jump);
		}
	}

	/// <summary>
	/// Destruktor usuwajacy wszystkie skoki z listy skokow.
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
	/// Metoda sprawdzajaca, czy w wyniku ruchu nastepuje "ukoronowanie" piona.
	/// </summary>
	/// <param name="piece_after">Kolor pionka po wykonaniu ruchu</param>
	/// <returns>true, jesli nastepuje "ukoronowanie"; false w przeciwnym razie</returns>
	bool has_kinging_occured(char piece_after);

	/*getters*/

	/// <summary>
	/// Metoda zwracajaca wspolrzedna x pola startowego ruchu.
	/// </summary>
	/// <returns>Wspolrzedna x pola startowego ruchu</returns>
	int get_xs() const { return xs; }

	/// <summary>
	/// Metoda zwracajaca wspolrzedna y pola startowego ruchu.
	/// </summary>
	/// <returns>Wspolrzedna y pola startowego ruchu</returns>
	int get_ys() const { return ys; }

	/// <summary>
	/// Metoda zwracajaca wspolrzedna x pola docelowego ruchu.
	/// </summary>
	/// <returns>Wspolrzedna x pola docelowego ruchu</returns>
	int get_xf() const { return xf; }

	/// <summary>
	/// Metoda zwracajaca wspolrzedna y pola docelowego ruchu.
	/// </summary>
	/// <returns>Wspolrzedna y pola docelowego ruchu</returns>
	int get_yf() const { return yf; }

	/// <summary>
	/// Metoda zwracajaca kolor pionka wykonujacego ruch.
	/// </summary>
	/// <returns>Kolor pionka wykonujacego ruch</returns>
	char get_piece() const { return piece; }

	/// <summary>
	/// Metoda ustawiajaca wspolrzedne pola startowego ruchu.
	/// </summary>
	/// <param name="x">Nowa Wspolrzedna x pola startowego ruchu</param>
	/// <param name="y">Nowa Wspolrzedna y pola startowego ruchu</param>
	void set_start(int x, int y) {
		xs = x;
		ys = y;
	}

	/// <summary>
	/// Metoda ustawiajaca wspolrzedne pola docelowego ruchu.
	/// </summary>
	/// <param name="x">Nowa Wspolrzedna x pola docelowego ruchu</param>
	/// <param name="y">Nowa Wspolrzedna y pola docelowego ruchu</param>
	void set_finish(int x, int y) {
		xf = x;
		yf = y;
	}

	/// <summary>
	/// Metoda wyswietlajaca informacje o wykonanych skokach.
	/// </summary>
	const void print_jumps();
	/// <summary>
	/// Przeciazenie operatora dodawania pozwalajace dodac skok do listy skokow danego ruchu.
	/// </summary>
	const move& operator+(jump* other);
};

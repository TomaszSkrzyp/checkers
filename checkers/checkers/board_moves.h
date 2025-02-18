#pragma once
#include "board_jumps.h"

/// <summary>
/// Klasa odpowiedzialna za znajdowanie mozliwych ruchow dla bierki na planszy. Dziedziczy po klasie general.
/// </summary>
class board_moves : public general {
private:
    /// <summary>
    /// Funkcja sprawdza mozliwosc poruszenia sie w gore planszy dla podanych wspolrzednych i bierki.
    /// </summary>
    /// <param name="piece"> Kolor poruszanej bierki (char) </param>
    /// <param name="xs"> Wspolrzedna X pola startowego </param>
    /// <param name="ys"> Wspolrzedna Y pola startowego </param>
    /// <param name="dir"> Kierunek ewentualnego ruchu ('l' - ruch na ukos w lewo, 'r' - ruch na ukos w prawo) </param>
    void move_legal_up(char piece, int xs, int ys, char dir);

    /// <summary>
    /// Funkcja sprawdza mozliwosc poruszenia sie w dol planszy dla podanych wspolrzednych i bierki.
    /// </summary>
    /// <param name="piece"> Kolor poruszanej bierki (char) </param>
    /// <param name="xs"> Wspolrzedna X pola startowego </param>
    /// <param name="ys"> Wspolrzedna Y pola startowego </param>
    /// <param name="dir"> Kierunek ewentualnego ruchu ('l' - ruch na ukos w lewo, 'r' - ruch na ukos w prawo) </param>
    void move_legal_down(char piece, int xs, int ys, char dir);

    /// <summary>
    /// Lista wskaznikow do ruchu generowana dla obiektu tej klasy. Przeciaza zadeklarowana w klasie bazowej liste o tej samej nazwie.
    /// </summary>
    std::list<move*> m_list;

public:
    /// <summary>
    /// Konstruktor klasy board_moves, uzywajacy konstruktora klasy bazowej general.
    /// </summary>
    /// <param name="b"> Obiekt klasy board przekazywany przez referencje </param>
    board_moves(const board& b) : general(b) {
        /*std::cout << "board moves finder created" << std::endl;*/
    }

    /// <summary>
    /// Destruktor obiektu typu board_moves.
    /// </summary>
    ~board_moves() {
        /*std::cout << "board moves finder destroyed" << std::endl;*/
    }

    /// <summary>
    /// Funkcja sluzaca do wgrania listy ruchow znalezionych przez obiekt do wybranej listy ruchow.
    /// </summary>
    /// <param name="list"> Lista wskaznikow do ruchu (niekoniecznie pusta) </param>
    void update_moves(std::list<move*>& list);

    /// <summary>
    /// Funkcja dynamicznie alokuje obiekt typu move i dodaje go do listy m_list.
    /// </summary>
    /// <param name="piece"> Kolor poruszanej bierki (char) </param>
    /// <param name="xs"> Wspolrzedna X pola startowego </param>
    /// <param name="ys"> Wspolrzedna Y pola startowego </param>
    /// <param name="xf"> Wspolrzedna X pola koncowego </param>
    /// <param name="yf"> Wspolrzedna Y pola koncowego </param>
    void add_move(char piece, int xs, int ys, int xf, int yf);

    /// <summary>
    /// Funkcja iterujaca przez plansze i szukajaca ruchow w gore (poprzez wywolanie funkcji move_legal_up) lub w dol (poprzez wywolanie funkcji move_legal_down)
    /// dla kazdej pozycji, na ktorej znajduje sie bierka wlasciwego koloru.
    /// </summary>
    /// <returns> Zwraca true, gdy nie udalo sie znalezc zadnego ruchu </returns>
    bool avalilable_moves();
};


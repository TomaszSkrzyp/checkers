#pragma once
#include <vector>
#include<iostream>
#include <String>
#include<cmath>
#include<list>
#include"board_record.h"/// <summary>
/// Klasa bazowa abstrakcyjna general. Dziedzicza po niej klasy board_jumps i board_moves. Funkcje te sa wykorzystywane w poszukiwaniu ruchow na planszy.
/// </summary>
class general {
protected:
    /// <summary>
    /// Obiekt typu char definiujacy obecna ture (jej kolejnosc). 'w' oznacza kolej bialych, 'b' kolej czarnych.
    /// </summary>
    char turn;

    /// <summary>
    /// Funkcja pozwala wyznaczyc wspolrzedna Y przeskakiwanego pola. Przez kompresje planszy nie jest to zadanie trywialne tak jak w przypadku wspolrzednej X.
    /// </summary>
    /// <param name="yj"> Wspolrzedna Y przeskakiwanego pola </param>
    /// <param name="xs"> Wspolrzedna X pola startowego </param>
    /// <param name="ys"> Wspolrzedna Y pola startowego </param>
    /// <param name="yf"> Wspolrzedna Y pola koncowego </param>
    const void find_y_jumped(int& yj, int xs, int ys, int yf);

    /// <summary>
    /// Funkcja ustalajaca wartosc klucza dla skoku. Wartosc ta zawiera informacje o punkcie startowym, przeskakiwanym i koncowym.
    /// </summary>
    /// <param name="xs"> Wspolrzedna X pola startowego </param>
    /// <param name="ys"> Wspolrzedna Y pola startowego </param>
    /// <param name="xj"> Wspolrzedna X przeskakiwanego pola </param>
    /// <param name="yj"> Wspolrzedna Y przeskakiwanego pola </param>
    /// <param name="xf"> Wspolrzedna X pola koncowego </param>
    /// <param name="yf"> Wspolrzedna Y pola koncowego </param>
    /// <returns> Wartosc klucza </returns>
    const int hashed_jump(int xs, int ys, int xj, int yj, int xf, int yf);

    /// <summary>
    /// Funkcja obracajaca wartosc klucza.
    /// </summary>
    /// <param name="i"> Wartosc klucza </param>
    /// <returns> Obrocona wartosc klucza </returns>
    const int rev_hash(int i);

    /// <summary>
    /// Tablica obiektow typu char. Reprezentuje ona pola na planszy. Wartosc chara definiuje bierke znajdujaca sie na tym polu: 'b' - bierka czarna, 'w' - bierka biala, 'e' - puste pole. Dodatkowo 'B' oraz 'W' oznaczaja damki poszczegolnych kolorow.
    /// </summary>
    char arr[8][4];

public:
    /// <summary>
    /// Klasa czysto wirtualna uzywana do wgrywania listy ruchow znalezionych przez algorytm poszukiwania do listy ruchow podanej w argumencie.
    /// </summary>
    /// <param name="list"> Lista wskaznikow do ruchu, do ktorej chcemy przeniesc znalezione ruchy </param>
    virtual void update_moves(std::list<move*>& list) = 0;

    /// <summary>
    /// Konstruktor klasy general. Do uzupelnienia tablicy charow reprezentujacej plansze zczytuje wartosci pol z obiektu klasy board. Obecna ture ustala przy uzyciu listy inicjalizujacej.
    /// </summary>
    /// <param name="b"> Obiekt typu board, ktorego wartosci chcemy przeniesc do obiektu </param>
    general(const board& b) : turn(b.get_turn()) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 4; j++) {
                arr[i][j] = b.get_piece(i, j);
            }
        }
    }

    /// <summary>
    /// Destruktor klasy general. Oczyszcza liste m_list.
    /// </summary>
    ~general();

    std::list<move*> m_list = {};

    /// <summary>
    /// Funkcja pozwalajaca zmieniac zawartosc tablicy charow arr istniejacego juz obiektu. Wykorzystuje te sama zasade dzialania co konstruktor.
    /// </summary>
    /// <param name="b"> Nowy stan planszy </param>
    void replace_board(const board& b);

    /// <summary>
    /// Funkcja zwracajaca kolej ruchu.
    /// </summary>
    /// <returns> Char informujacy o kolorze bierek, ktory ma sie teraz poruszyc </returns>
    int get_turn() const {
        return turn;
    }
};
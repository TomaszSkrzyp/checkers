#pragma once
#include"general.h"

/// <summary>
/// Klasa reprezentujaca obiekt znajdujacy wszystkie dostepne skoki w pozycji. Dziedziczy po klasie general.
/// </summary>
class board_jumps : public general {
private:
    /// <summary>
    /// Funkcja dodajaca skoki do istniejacej juz listy skokow. Sprawdza, czy w liscie tej wystapil juz skok ten sam lub skok odwrotny przez porownanie kluczy skoku, ktory chcemy dodac, oraz wszystkich
    /// wystepujacych w liscie. Jesli warunek ten nie zostanie spelniony, funkcja dynamicznie alokuje nowy obiekt typu skok, dodaje go do listy i sprawdza, czy z pola, na ktorym bierka wyladuje, sa dostepne nastepne skoki.
    /// </summary>
    /// <param name="j_list"> Lista wskaznikow do obiektow typu skok </param>
    /// <param name="p"> Obiekt typu char informujacy o kolorze bierki wykonujacej skok </param>
    /// <param name="xs"> 
    ///  X pola startowego </param>
    /// <param name="ys"> Wspolrzedna Y pola startowego </param>
    /// <param name="xj"> Wspolrzedna X przeskakiwanego pola </param>
    /// <param name="yj"> Wspolrzedna Y przeskakiwanego pola </param>
    /// <param name="xf"> Wspolrzedna X pola koncowego </param>
    /// <param name="yf"> Wspolrzedna Y pola koncowego </param>
    /// <param name="prev_jump"> Wskaznik na skok bedacy poprzednikiem skoku, ktory chcemy dodac do listy skokow </param>
    /// <returns> Zwraca true, gdy mozliwe jest dodanie skoku do listy skokow </returns>
    bool create_jump(std::list<jump*> j_list, char p, int xs, int ys, int xj, int yj, int xf, int yf, jump* prev_jump);

    /// <summary>
    /// Funkcja dynamicznie alokuje nowy obiekt typu ruch na podstawie listy wskaznikow do skokow oraz dodaje ten ruch do listy mozliwych ruchow. Funkcja uzupelnia skoki o wskaznik do skoku poprzedniego, 
    /// przechodzac iteracyjnie przez liste wskaznikow do skokow.
    /// </summary>
    /// <param name="j_list"> Lista wskaznikow do skokow na podstawie, ktorej chcemy stworzyc obiekt typu ruch i dodac ten ruch do listy </param>
    void create_jump_move(std::list<jump*> j_list);

    /// <summary>
    /// Funkcja sprawdza, czy w podanym kierunku z podanego pola mozna wykonac skok. Jesli skok ten jest mozliwy i obecna lista skokow moze legalnie byc przeksztalcona w ruch, wywolywana jest 
    /// funkcja tworzaca ruch dla obecnej listy wskaznikow do skokow. Jesli skok jest mozliwy, to znaczy wszystkie warunki sa spelnione, wywolywana jest funkcja dodajaca skok do obecnej listy skokow.
    /// </summary>
    /// <param name="jumping_piece"> Obiekt typu char oznaczajacy kolor bierki </param>
    /// <param name="xs"> Wspolrzedna X pola startowego </param>
    /// <param name="ys"> Wspolrzedna Y pola startowego </param>
    /// <param name="direction_y"> Kierunek w orientacji poziomej sprawdzanego skoku </param>
    /// <param name="direction_x"> Kierunek w orientacji pionowej sprawdzanego skoku </param>
    /// <param name="prev"> Wskaznik do skoku poprzedzajacego sprawdzany skok </param>
    /// <param name="j_list"> Lista wskaznikow do wszystkich poprzednich skokow </param>
    void check_jump(char jumping_piece, int xs, int ys, char direction_y, char direction_x, jump* prev, std::list<jump*> j_list);

public:
    /// <summary>
    /// Konstruktor klasy board_jumps uzywajacy konstruktora klasy bazowej general.
    /// </summary>
    /// <param name="b"> Obiekt klasy board podawany przez referencje </param>
    board_jumps(const board& b) : general(b) {
        /*std::cout << "board jumps finder created" << std::endl;*/
    }

    /// <summary>
    /// Destruktor klasy board_jumps uzywajacy konstruktora klasy bazowej general.
    /// </summary>
    ~board_jumps() {
        /*std::cout << "board jumps finder destructed" << std::endl;*/
    }

    /// <summary>
    /// Funkcja sluzaca do wgrania listy ruchow znalezionych przez obiekt do wybranej listy ruchow. W przypadku mojego programu dotyczy ona listy dostepnych ruchow w obecnej turze tworzonej w metodzie 
    /// game::main_loop bedacej glowna funkcja programu. Funkcja dealokuje rowniez zawartosc listy dostepnych ruchow poprzedniej tury.
    /// </summary>
    /// <param name="list"> Niekoniecznie pusta lista wskaznikow do ruchu </param>
    void update_moves(std::list<move*>& list);

    /// <summary>
    /// Funkcja poszukujaca mozliwych skokow w podanej pozycji na planszy. Wywoluje ona funkcje check_jump dla mozliwych kierunkow w podanej pozycji.
    /// </summary>
    /// <param name="xs"> Wspolrzedna X pola startowego </param>
    /// <param name="ys"> Wspolrzedna Y pola startowego </param>
    /// <param name="prev"> Wskaznik na poprzedni skok </param>
    /// <param name="j_list"> Lista wskaznikow na poprzednie skoki </param>
    void avalilable_jump(int xs, int ys, jump* prev, std::list<jump*>& j_list);

    /// <summary>
    /// Funkcja iterujaca przez plansze i poszukujaca skokow (poprzez wywolanie funkcji available_jump) dla kazdej pozycji na ktorej znajduje sie bierka wlasciwego koloru.
    /// </summary>
    /// <returns> Zwraca true, gdy nie uda sie znalezc zadnego skoku </returns>
    bool avalilable_jumps();

    /// <summary>
    /// Funkcja zwraca obecna wartosc atrybutu turn informujacego o obecnej turze w partii.
    /// </summary>
    /// <returns> Obecna tura </returns>
    char get_turn() const {
        return turn;
    }
};
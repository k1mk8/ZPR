#ifndef Game_H
#define Game_H

#include<iostream>
#include<ctime>
#include<vector>
#include<sstream>
#include<fstream>

#include "Bot.h"
#include "BasicWindow.h"

using namespace sf;
using namespace std;

class Game
{
private:
    VideoMode videoMode; // okno gry wyświetlane do użytkownika
    RenderWindow* window; // okno gry
    bool endGame; // czy koniec gry
    Event sfmlEvent; // event gry
    vector<Player> players; // wektor graczy
    vector<Bot> bots; // wektor botów
    vector<StaticPoints> staticPoints; // punkty statyczne na mapie
    Font font; // czcionka
    Text guiText; // tekst GUI
    Text table; //tekst wyników
    int maxStaticPoints; // maksymalna ilość obiektó statycznych
    int totalPoints; // sumaryczna ilośc punktów
    int maxPoints = 10; // maksymalna ilość punktów w grze
    int maxBots = 10; // maksymalna ilość graczy w grze
    void variables(const int& speed); // inicjowanie zmiennych
    void initWindow(); // inicjowanie okna
    void initFonts(); // inicjowanie czcionki
    void initText(); // inicjowanie tekstu
    void initBots(const float& speed); // inicjowanie botów
    void zoomOut(); // oddalanie obrazu
public:
    Game(const int& speed); // konstruktor domyślny
    ~Game(); // destruktor domyślny
    const bool& getEndGame() const; // zwraca informację o końcu gry
    bool running(); // czy okno otwarte
    void pollEvents(); // eventy na mapie
    const int& getTotalPoints() const; // zwraca sumaryczną ilośc punktów
    void calculateTotalPoints(); // obliczanie sumy punktów
    void spawnStaticPoints(); // tworzenie obiektów statycznych
    int randPointType(); // losowanie obiektów do stworzenia
    void updatePlayer(); // uaktualnianie graczy
    template<typename T>
    void updateCollision(vector<T>& participants, bool isBot); // sprawdzanie kolizji
    void updateGui(); // uaktualnianie GUI
    void updateMaxPoints(); // uaktualnianie maksymalnej liczby punktów w grze
    void updateBot(); // wykonanie aktualizacji ruchow
    void update(); // uaktualnianie wydarzeń na mapie
    void calculateStaticPoints();
    void renderGui(RenderTarget* target); // wyświetlanie GUI
    void render(); // renderowanie i wyświetlanie mapy oraz obiektów
};
#endif
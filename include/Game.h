#include<iostream>
#include<ctime>
#include<vector>
#include<sstream>
#include<fstream>

#include "Bot.h"

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
    Font font; // czcionka
    Text guiText; // tekst GUI
    Text table; //tekst wyników
    vector<StaticPoints> staticPoints; // punkty statyczne na mapie
    int maxStaticPoints; // maksymalna ilość obiektó statycznych
    int totalPoints; // sumaryczna ilośc punktów
    int maxPoints = 10; // maksymalna ilość punktów w grze
    int maxBots = 5; // maksymalna ilość graczy w grze
    void variables(const int speed); // inicjowanie zmiennych
    void initWindow(); // inicjowanie okna
    void initFonts(); // inicjowanie czcionki
    void initText(); // inicjowanie tekstu
    void initBots(); // inicjowanie botów
    void zoomOut(); // oddalanie obrazu
public:
    Game(const int speed); // konstruktor domyślny
    ~Game(); // destruktor domyślny
    const bool& getEndGame() const; // zwraca informację o końcu gry
    bool running(); // czy okno otwarte
    void pollEvents(); // eventy na mapie
    const int& getTotalPoints() const; // zwraca sumaryczną ilośc punktów
    void calculateTotalPoints(); // obliczanie sumy punktów
    void spawnStaticPoints(); // tworzenie obiektów statycznych
    int randPointType(); // losowanie obiektów do stworzenia
    void updatePlayer(); // uaktualnianie graczy
    void updateCollision(); // sprawdzanie kolizji
    void updateGui(); // uaktualnianie GUI
    void updateMaxPoints(); // uaktualnianie maksymalnej liczby punktów w grze
    void updateBot(); // wykonanie aktualizacji ruchow
    void update(); // uaktualnianie wydarzeń na mapie
    void renderGui(RenderTarget* target); // wyświetlanie GUI
    void render(); // renderowanie i wyświetlanie mapy oraz obiektów
};
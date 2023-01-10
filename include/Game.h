#include<iostream>
#include<ctime>
#include<vector>
#include<sstream>
#include<fstream>

#include "StaticPoints.h"

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
    Font font; // czcionka
    Text guiText; // tekst GUI
    vector<StaticPoints> staticPoints; // punkty statyczne na mapie
    int maxStaticPoints; // maksymalna ilość obiektó statycznych
    int totalPoints; // sumaryczna ilośc punktów
    int maxPoints = 10; // maksymalna ilość punktów w grze
    void variables(); // inicjowanie zmiennych
    void initWindow(); // inicjowanie okna
    void initFonts(); // inicjowanie czcionki
    void initText(); // inicjowanie tekstu
    void zoomOut(); // oddalanie obrazu
public:
    Game(); // konstruktor domyślny
    ~Game(); // destruktor domyślny
    const bool& getEndGame() const; // zwraca informację o końcu gry
    bool running(); // czy okno otwarte
    void pollEvents(); // eventy na mapie
    void calculateTotalPoints(); // obliczanie sumy punktów
    void spawnStaticPoints(); // tworzenie obiektów statycznych
    int randPointType(); // losowanie obiektów do stworzenia
    void updatePlayer(); // uaktualnianie graczy
    void updateCollision(); // sprawdzanie kolizji
    void updateGui(); // uaktualnianie GUI
    void updateMaxPoints(); // uaktualnianie maksymalnej liczby punktów w grze
    void update(); // uaktualnianie wydarzeń na mapie
    void renderGui(RenderTarget* target); // wyświetlanie GUI
    void render(); // renderowanie i wyświetlanie mapy oraz obiektów
};
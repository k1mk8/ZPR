#include <vector>
#include <cmath>
#include <iostream>
#include <time.h>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

using namespace sf;
using namespace std;
class Player
{
private:
    clock_t splitTime; // czas podziału gracza
    CircleShape shape; // kształt gracza
    float speed; // prędkość gracza
    float startingSpeed; // początkowa prędkość gracza
    int mass; // masa gracza
    void Variables(const int mass); // inicjowanie zmiennych
    void makeShape(); // tworzenie kształtu
    void calculateSpeed(); // obliczanie prędkości
    void connect(std::vector<Player>& players); // łącznie graczy
public:
    Player(float x = 0, float y = 0, const int mass = 512); // konstruktor graczy
    ~Player(); // destruktor klasy
    const CircleShape& getShape() const; // getter kształtu
    const int& getMass() const; // getter masy
    float getRadius(); // getter promienia
    const float& getSpeed() const; // getter prędkości
    const Vector2f& getPlayerPostion() const; // getter pozycji gracza
    const clock_t& getSplitTime() const; // getter czasu podziału
    void setSplitTime(clock_t splittime); // setter czasu podziału
    void setMass(const int weight); // setter masy
    void grow(const int food); // jedzenie masy
    void split(std::vector <Player>& players); // dzielenie gracza
    void splitBySpike(std::vector <Player>& players); // dzielenie przez spike'a
    void move(); // ruch gracza
    void checkMapCollision(); // sprawdzanie ograniczeń mapy
    void loseMass(); // tracenie masy
    void splitMass(); // dzielenie masy
    void shootingMass(); // strzelanie masą
    void setPosition(std::vector <Player>& players); // ustawianie pozycji
    void render(RenderTarget& target); // enderowanie gracza
};
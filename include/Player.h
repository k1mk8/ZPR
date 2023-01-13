#include <vector>
#include <cmath>
#include <iostream>
#include <time.h>
#include <math.h>     

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
class Player
{
private:
    clock_t splitTime; // czas podziału gracza
    clock_t freshSpawnedTime; // czas podziału gracza
    sf::CircleShape shape; // kształt gracza
    float speed; // prędkość gracza
    float startingSpeed; // początkowa prędkość gracza
    int mass; // masa gracza
    int type; // rodzaj obiektu
    std::string name; // nazwa gracza
    void Variables(const int mass, const int speed); // inicjowanie zmiennych
    void makeShape(); // tworzenie kształtu
    void connect(std::vector<Player>& players); // łącznie graczy
public:
    Player(float x = 0, float y = 0, const int mass = 10, const int speed = 10); // konstruktor graczy
    ~Player(); // destruktor klasy
    sf::CircleShape& getShape(); // getter kształtu
    const int& getMass() const; // getter masy
    float getStartingSpeed(); // getter masy
    float getRadius(); // getter promienia
    int getType(); // getter Typu obiektu
    const float& getSpeed() const; // getter prędkości
    const sf::Vector2f& getPlayerPostion() const; // getter pozycji gracza
    const clock_t& getSplitTime() const; // getter czasu podziału
    void setSplitTime(clock_t splittime); // setter czasu podziału
    void setType(int type); // setter Typu obiektu
    const clock_t& getFreshSpawnedTime() const; // getter czasu podziału
    void setFreshSpawnedTime(clock_t freshSpawnedTime); // setter czasu podziału
    void calculateSpeed(); // obliczanie prędkości
    void calculateFreshSpawnedSpeed(); // obliczanie prędkości po utworzeniu nowego bytu
    void setMass(const int weight); // setter masy
    void grow(const int food); // jedzenie masy
    void split(sf::RenderWindow& window, std::vector <Player>& players); // dzielenie gracza
    void splitBySpike(std::vector<Player>& players); // dzielenie przez spike'a
    std::pair<float, float> getRelativeMousePositon(sf::RenderWindow& window, std::vector <Player>& players);
    void move(sf::RenderWindow& window, std::vector <Player>& players); // ruch gracza
    void checkMapCollision(); // sprawdzanie ograniczeń mapy
    void loseMass(); // tracenie masy
    void splitMass(); // dzielenie masy
    void setPosition(std::vector <Player>& players, sf::RenderWindow& window); // ustawianie pozycji
    void render(sf::RenderTarget& target); // enderowanie gracza
};
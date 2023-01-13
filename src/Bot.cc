/*
    @file Bot.cc
    @author Karol Kasperek, Szymon Dyszewski
    @brief plik zawierający implementację klasy Bot
*/

#include "Bot.h"

using namespace std;
using namespace sf;

Bot::Bot(float x, float y, const int mass, const int speed)
    : Player(x, y, mass, speed)
{
    /// @brief Konstruktor bota
    /// @param x pozycja pozioma
    /// @param y pozycja pionowa
    /// @param mass masa gracza
    /// @param speed predkosc gracza

    this->makeShape();
    this->setType(4);
}

Bot::~Bot()
{
}

float Bot::getDirection(float x, float y)
{
    /// @brief funkcja zwracająca kierunek poruszania się
    /// @param x współrzędna x
    /// @param y współrzędna y
    /// @return wartość atan2
    float xdiff = x - this->getPlayerPostion().x;
    float ydiff = y - this->getPlayerPostion().y;
    return atan2(-ydiff, xdiff);
}

void Bot::makeShape()
{
    /// @brief tworzy obiekt
    this->getShape().setFillColor(Color::Black);
    this->getShape().setRadius(this->getRadius());
}

template<typename T>
bool Bot::searchNearby(const vector<T>& participants, int range)
{
    /// @brief funkcja szukającego najbliższego obiektu w danym obszarze
    /// @tparam T template dla ujednolicenia funkcji
    /// @param participants obiekt
    /// @param range zasięg
    /// @return wydarzenie jaki ma zostać wywołane
    float direction = 0;
    float closest = 1e12;
    float speed = this->getSpeed();
    for(auto& it: participants) // iteracja po wszystkich obiektach
    {
        float this_x = this->getPlayerPostion().x; // pobranie swojej pozycji
        float this_y = this->getPlayerPostion().y;
        float it_x = it.getPlayerPostion().x; // pobranie pozycji obiektu
        float it_y = it.getPlayerPostion().y;
        if(it_x == this_x && it_y == this_y) // sprawdzenie czy nie jesteśmy sobą
            continue;
        float diff_x = abs(it_x - this_x);
        float diff_y = abs(it_y - this_y);
        if(diff_x < range && diff_y < range) // sprawdzenie czy obiekt jest w zasięgu
        {
            int this_mass = this->getMass();
            int it_mass = it.getMass();
            if(this_mass >= 1.2 * it_mass) // porównanie mas 
            {
                if(diff_x + diff_y < closest)
                {
                    direction = this->getDirection(it_x, it_y); // ustalenie kierunku do najbliższego
                    closest = diff_x + diff_y;
                }
            }
            else if(0.95 * this_mass < it_mass && it_mass != 30)
            {
                direction = this->getDirection(it_x, it_y);
                this->getShape().move(-cos(direction) * speed, sin(direction) * speed);
                return 0;
            }
        }
    }
    if(direction == 0)
        return 1;
    this->getShape().move(cos(direction) * speed, -sin(direction) * speed);
    return 0;
}

void Bot::moveBot(const vector<Bot>& bots, const vector<Player>& players, const vector<StaticPoints>& static_points)
{
    /// @brief funkcja obsługująca poruszanie się botów
    /// @param bots wektory botów na planszy
    /// @param players wektor graczy na planszy
    /// @param static_points wektor punktów statycznych na planszy
    this->calculateSpeed();
    if(searchNearby(players, this->getMass() / 5 + 300))
        if(searchNearby(bots, this->getMass() / 5 + 300))
            searchNearby(static_points, 4000);
    this->checkMapCollision();
}

void Bot::splitBySpike(vector <Bot>& participants)
{
    /// @brief funkcja generująca rozbijanie się na spikea'ch
    /// @param participants boty do rozbicia
    (void)participants;
}
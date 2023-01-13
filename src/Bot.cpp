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
        float thisX = this->getPlayerPostion().x; // pobranie swojej pozycji
        float thisY = this->getPlayerPostion().y;
        float itX = it.getPlayerPostion().x; // pobranie pozycji obiektu
        float itY = it.getPlayerPostion().y;
        if(itX == thisX && itY == thisY) // sprawdzenie czy nie jesteśmy sobą
            continue;
        float diffX = abs(itX - thisX);
        float diffY = abs(itY - thisY);
        if(diffX < range && diffY < range) // sprawdzenie czy obiekt jest w zasięgu
        {
            int thisMass = this->getMass();
            int itMass = it.getMass();
            if(thisMass >= 1.2 * itMass) // porównanie mas 
            {
                if(diffX + diffY < closest)
                {
                    direction = this->getDirection(itX, itY); // ustalenie kierunku do najbliższego
                    closest = diffX + diffY;
                }
            }
            else if(0.95 * thisMass < itMass && itMass != 30)
            {
                direction = this->getDirection(itX, itY);
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

void Bot::moveBot(const vector<Bot>& bots, const vector<Player>& players, const vector<StaticPoints>& staticPoints)
{
    /// @brief funkcja obsługująca poruszanie się botów
    /// @param bots wektory botów na planszy
    /// @param players wektor graczy na planszy
    /// @param staticPoints wektor punktów statycznych na planszy
    this->calculateSpeed();
    if(searchNearby(players, this->getMass() / 5 + 300))
        if(searchNearby(bots, this->getMass() / 5 + 300))
            searchNearby(staticPoints, 4000);
    this->checkMapCollision();
}

void Bot::splitBySpike(vector <Bot>& participants)
{
    /// @brief funkcja generująca rozbijanie się na spikea'ch
    /// @param participants boty do rozbicia
    (void)participants;
}
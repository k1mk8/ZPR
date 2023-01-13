#ifndef Bot_H
#define Bot_H

#include "StaticPoints.h"

class Bot : public Player
{
/// @brief klasa odpowiedzialna za tworzenie i obsługę botów
public:
    float getDirection(float x, float y); // zwraca kierunek ruchu
    void makeShape(); // tworzenie kształtu
    Bot(float x = 50, float y = 50, const int mass = 10, const int speed = 10); // konstruktor 
    ~Bot(); // destruktor
    void moveBot(const std::vector<Bot>& bots, const std::vector<Player>& players, const std::vector<StaticPoints>& static_points); // poruszanie się bota
    template<typename T>
    bool searchNearby(const std::vector<T>& participants, int range); // szukanie najbliższego obiektu
    void splitBySpike(std::vector<Bot>& participants); // dzielenie przez spike'a
};
#endif
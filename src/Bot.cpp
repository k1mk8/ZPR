#include "Bot.h"

using namespace std;

/// @brief Konstruktor bota
///
/// @param x pozycja pozioma
/// @param y pozycja pionowa
/// @param mass masa gracza
/// @param speed predkosc gracza
/// @param name nazwa gracza
///

Bot::Bot(float x, float y, const int mass, const int speed)
    : Player(x, y, mass, speed)
{
    this->makeShape();
}

/// @brief Try moving in given direction, as long as there are no spikes in the way that can explode the bot's first cell.
/// When no spikes are in the way, updates bot's velocity and returns true, otherwise doesn't change velocity and returns false.
///
/// @param dir Direction of movement
/// @param spikes Vector of spikes
///

float Bot::getDirection(float x, float y)
{
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

void Bot::moveBot(const vector<Bot>& bots, const vector<Player>& players, const vector<StaticPoints>& staticPoints)
{
    this->calculateSpeed();
    bool flag = 0;
    for(auto& it: players)
    {
        if(abs(it.getPlayerPostion().x - this->getPlayerPostion().x) < 200 &&
            abs(it.getPlayerPostion().y - this->getPlayerPostion().y) < 200)
        {
            float direction = this->getDirection(it.getPlayerPostion().x, it.getPlayerPostion().y);
            if(this->getMass() >= 1.2 * it.getMass())
            {
                this->getShape().move(cos(direction) * this->getSpeed(), -sin(direction) * this->getSpeed());
                break;
            }
            else if(0.95 * this->getMass() < it.getMass())
            {
                this->getShape().move(-cos(direction) * this->getSpeed(), sin(direction) * this->getSpeed());
                break;
            }
            else
            {
                flag = 1;
            }
        }
        else
            flag = 1;
    }
    if(flag)
    {    
        float closestPoint = 10000;
        float closestx, closesty;
        for(auto& it: staticPoints)
        {
            float positonDifference = abs(it.getShape().getPosition().x - this->getPlayerPostion().x) +
                abs(it.getShape().getPosition().y - this->getPlayerPostion().y);
            if(positonDifference <= closestPoint && it.getType() != SPIKES )
            {
                closestPoint = positonDifference;
                closestx = it.getShape().getPosition().x;
                closesty = it.getShape().getPosition().y;
            }
        }
        float direction = this->getDirection(closestx, closesty);
        this->getShape().move(cos(direction) * this->getSpeed(), -sin(direction) * this->getSpeed());
    }
}
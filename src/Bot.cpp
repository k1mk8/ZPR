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

Bot::~Bot()
{
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

template<typename T>
bool Bot::searchNearby(const vector<T>& participants, int range)
{
    float direction = 0;
    float closest = 1e12;
    float speed = this->getSpeed();
    for(auto& it: participants)
    {
        float thisX = this->getPlayerPostion().x;
        float thisY = this->getPlayerPostion().y;
        float itX = it.getPlayerPostion().x;
        float itY = it.getPlayerPostion().y;
        if(itX == thisX && itY == thisY)
            continue;
        float diffX = abs(itX - thisX);
        float diffY = abs(itY - thisY);
        if(diffX < range && diffY < range)
        {
            int thisMass = this->getMass();
            int itMass = it.getMass();
            if(thisMass >= 1.2 * itMass)
            {
                if(diffX + diffY < closest)
                {
                    direction = this->getDirection(itX, itY);
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
    this->calculateSpeed();
    if(searchNearby(players, this->getMass() / 5 + 300))
        if(searchNearby(bots, this->getMass() / 5 + 300))
            searchNearby(staticPoints, 4000);
    this->checkMapCollision();
}

void Bot::splitBySpike(vector <Bot>& participants)
{
    (void)participants;
}
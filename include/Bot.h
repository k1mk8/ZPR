#include "StaticPoints.h"

class Bot : public Player
{
private:
    float getDirection(float x, float y);
    void makeShape();
public:
    Bot(float x = 50, float y = 50, const int mass = 10, const int speed = 10);
    ~Bot();
    void moveBot(const std::vector<Bot>& bots, const std::vector<Player>& players, const std::vector<StaticPoints>& staticPoints);
    template<typename T>
    bool searchNearby(const std::vector<T>& participants, int range);
    void splitBySpike(std::vector<Bot>& participants);
};

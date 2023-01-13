#include "StaticPoints.h"

using namespace std;
using namespace sf;

class Bot : public Player
{
private:
    float getDirection(float x, float y);
    void makeShape();
public:
    Bot(float x = 50, float y = 50, const int mass = 10, const int speed = 10);
    ~Bot();
    void moveBot(const vector<Bot>& bots, const vector<Player>& players, const vector<StaticPoints>& staticPoints);
    template<typename T>
    bool searchNearby(const vector<T>& participants, int range);
    void splitBySpike(vector<Bot>& participants);
};

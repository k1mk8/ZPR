#include "StaticPoints.h"

using namespace std;
using namespace sf;

class Bot : public Player
{
public:
    Bot(float x = 50, float y = 50, const int mass = 10, const int speed = 10);
    void moveBot(const vector<Bot>& bots, const vector<Player>& players, const vector<StaticPoints>& staticPoints);
private:
    float getDirection(float x, float y);
    void makeShape();
    const int NEARBY_SQ = 1000*1000;
    const int MAX_DIST_TO_SPIKES = 600;
};

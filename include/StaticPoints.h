#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Player.h"

using namespace sf;
enum StaticPointsTypes {FOOD = 0, SPIKES};

class StaticPoints
{
private:
    CircleShape shape;
    int type;
    int mass = 5;
    void makeShape(const View& window, std::vector<Player> rect);
public:
    StaticPoints(const View& window, int type, std::vector<Player> rect);
    virtual ~StaticPoints();

    const CircleShape getShape() const;
    const int& getType() const;
    const int& getMass() const;

    void eatMass(const int food);
    void checkSpikeMass(const View& window);
    void render(RenderTarget& target);
};
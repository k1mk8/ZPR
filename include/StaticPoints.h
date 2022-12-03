#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

using namespace sf;
enum StaticPointsTypes {FOOD = 0, SPIKES};

class StaticPoints
{
private:
    CircleShape shape;
    int type;
    int mass = 5;
    void makeShape(const RenderWindow& window);
public:
    StaticPoints(const RenderWindow& window, int type);
    virtual ~StaticPoints();

    const CircleShape getShape() const;
    const int& getType() const;
    const int& getMass() const;

    void render(RenderTarget& target);
};

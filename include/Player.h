#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "StaticPoints.h"

using namespace sf;
class Player
{
private:
    CircleShape shape;
    float speed;
    int mass;
    int timeOfLive;
    void Variables(const int mass);
    void makeShape();
public:
    Player(float x = 0.f, float y = 0.f, const int mass = 10);
    virtual ~Player();

    const CircleShape& getShape() const;
    const int& getMass() const;
    const int& getSpeed() const;
    const Vector2f& getPlayerPostion() const;

    void setMass(const int weight);
    void grow(const int food);

    void splitMass();
    void split();

    void loseMass();
    void shootingMass();

    void move();
    void checkMapCollision(const View* target);
    void setPosition(const View* target);
    void render(RenderTarget& target);
};
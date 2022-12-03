#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

using namespace sf;
class Player
{
private:
    CircleShape shape;
    float speed;
    int mass;
    void Variables();
    void makeShape();
public:
    Player(float x = 0.f, float y = 0.f);
    virtual ~Player();

    const CircleShape& getShape() const;
    const int& getMass() const;
    const int& getSpeed() const;

    void setMass(const int weight);
    void grow(const int food);

    void splitMass();
    void split();

    void loseMass();
    void shootingMass();

    void move();
    void checkMapCollision(const RenderTarget* target);
    void setPosition(const RenderTarget* target);
    void render(RenderTarget* target);
};
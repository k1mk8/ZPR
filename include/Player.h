#include <vector>
#include <cmath>
#include <iostream>
#include <time.h>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

using namespace sf;
using namespace std;
class Player
{
private:
    clock_t splitTime;
    CircleShape shape;
    float speed;
    float startingSpeed;
    int mass;
    int timeOfLive;
    void Variables(const int mass);
    void makeShape();
    void calculateSpeed();
    void connect(std::vector<Player>& players);
public:
    Player(float x = 0.f, float y = 0.f, const int mass = 10);
    virtual ~Player();
    const CircleShape& getShape() const;
    const int& getMass() const;
    const float& getSpeed() const;
    const Vector2f& getPlayerPostion() const;
    void setMass(const int weight);
    void grow(const int food);
    void split(std::vector <Player>& players);
    void splitBySpike(std::vector <Player>& players);
    void move();
    void checkMapCollision();
    void loseMass();
    void splitMass();
    void shootingMass();
    void setPosition(std::vector <Player>& players);
    void render(RenderTarget& target);
};
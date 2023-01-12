#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Player.h"

using namespace sf;
enum StaticPointsTypes {FOOD = 0, SPIKES}; // typy punktów statycznych

class StaticPoints : public Player // klasa punktów statycznych w grze
{
private:
    CircleShape shape; // kształ punktu
    clock_t freshSpawnedTime; // czas podziału gracza
    int type; // typ punktu
    int mass = 5; // masa punktu
    float speed = 0;
    float direction = 0;
    void makeShape(std::vector<Player> rect); // tworzy punkt
public:
    StaticPoints(int type, std::vector<Player> rect); // domyślny konstruktor
    StaticPoints(int type, float X, float Y); // konstruktor pozycyjny
    StaticPoints(int type, float X, float Y, float speed, float direction); // konstruktor pozycyjny
    virtual ~StaticPoints(); // destruktor 
    const CircleShape getShape() const; // zwraca kształt punktu
    const Vector2f& getPlayerPostion() const; // getter pozycji gracza
    const int& getType() const; // zwraca typ punktu
    const int& getMass() const; // zwraca mase punktu
    void render(RenderTarget& target); // renderowanie punktu
    void calculateSpeed();
};
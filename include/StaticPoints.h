#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Player.h"

using namespace sf;
enum StaticPointsTypes {FOOD = 0, SPIKES}; // typy punktów statycznych

class StaticPoints // klasa punktów statycznych w grze
{
private:
    CircleShape shape; // kształ punktu
    int type; // typ punktu
    int mass = 5; // masa punktu
    void makeShape(std::vector<Player> rect); // tworzy punkt
public:
    StaticPoints(int type, std::vector<Player> rect); // domyślny konstruktor
    StaticPoints(int type, float X, float Y); // konstruktor pozycyjny
    virtual ~StaticPoints(); // destruktor 
    const CircleShape getShape() const; // zwraca kształt punktu
    const int& getType() const; // zwraca typ punktu
    const int& getMass() const; // zwraca mase punktu
    void eatMass(const int food); // zwiększenie masy punktu
    void checkSpikeMass(const View& window); // sprawdzanie masy Spike'a
    void render(RenderTarget& target); // renderowanie punktu
};
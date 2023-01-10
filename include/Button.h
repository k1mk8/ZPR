#include <bits/stdc++.h>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>


using namespace sf;
using namespace std;

class Button // klasa odpowiedzialna za klikalny button do interakcji z użytkownikiem
{
private:
    RectangleShape button; // zmienna przetrzymująca kształt przycisku
public:
    Button(); // konstruktor domyślny
    Button(Vector2f size, Color color, Vector2f pos); // konstruktor przyjmujący wartości startowe
    ~Button(); // destruktor
    const RectangleShape& getButton() const; // zwraca przycisk
    bool isButtonPressed(RenderWindow* window); // sprawdza czy button jest wciśnięty
};
#include <bits/stdc++.h>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Player.h"
using namespace sf;
using namespace std;

class Button
{
private:
    RectangleShape button;
public:
    Button(Vector2f size, Color color, Vector2f pos);
    ~Button();
    const RectangleShape& getButton() const;
    const bool isButtonPressed(RenderWindow* window) const;
};
#include <bits/stdc++.h>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "Interface.h"
using namespace sf;


class GameOver
{
private:
    Button buttonYes;
    Button buttonNo;
    VideoMode videoMode;
    Event sfmlEvent;

    Sprite sprajt;
    Texture texture;

    void initWindow();
    void initButton();
public:
    RenderWindow* window;
    GameOver();
    ~GameOver();
    const int buttonPressed() const;
    void render();
};
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
    RenderWindow* window;
    Button buttonYes;
    Button buttonNo;
    VideoMode videoMode;
    Event sfmlEvent;
    Sprite sprite;
    Texture texture;
    void initWindow();
    void initButton();
public:
    GameOver();
    ~GameOver();
    const int buttonPressed() const;
    void pollEvents();
    const bool update();
    void render();
};
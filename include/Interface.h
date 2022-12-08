#include <bits/stdc++.h>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Player.h"
#include "Button.h"
using namespace sf;

class Interface
{
private:

    Button button;
    VideoMode videoMode;
    Event sfmlEvent;

    Player player;

    Sprite sprajt;
    Texture texture;

    Text standardText;
    Text guiText;
    Text buttonText;
    Text maxPointsText;
    Font font;

    void initWindow();
    void initFonts();
    void initText();
    void initButton();
public:
    RenderWindow* window;
    Interface();
    ~Interface();
    const bool isButtonPressed() const;
    const bool running() const;
    void pollEvents();
    const bool update();
    void renderGui(RenderTarget* target);
    void render();
};
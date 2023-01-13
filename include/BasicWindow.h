#ifndef BasicWindow_H
#define BasicWindow_H

#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "Button.h"
using namespace sf;


class BasicWindow
{
public:
    RenderWindow* window; // okno końca gry
    VideoMode videoMode; // okno wyświetlane
    Sprite sprite; // wygląd okna
    Texture texture; // tekstura
    Event sfmlEvent; // event
    Font font;
    virtual void setTexture();
    virtual void initWindow(); // inicjowanie okna
    virtual void initFonts();
    virtual void setNewTextParams(Text& name, Color color, int size, Vector2f setPosition = {0, 0}, string text = "");
    virtual bool running();
    virtual void pollEvents(); // sprawdzanie wydarzeń 
    ~BasicWindow(); // destruktor domyślny
    virtual int update() = 0; // uaktualnianie okna
    virtual void render() = 0; // renderowanie i wyświetlanie okna 
};
#endif
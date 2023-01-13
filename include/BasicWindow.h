#ifndef BasicWindow_H
#define BasicWindow_H

#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "Button.h"


class BasicWindow
{
public:
    sf::RenderWindow* window; // okno końca gry
    sf::VideoMode videoMode; // okno wyświetlane
    sf::Sprite sprite; // wygląd okna
    sf::Texture texture; // tekstura
    sf::Event sfmlEvent; // event
    sf::Font font;
    virtual void setTexture();
    virtual void initWindow(); // inicjowanie okna
    virtual void initFonts();
    virtual void setNewTextParams(sf::Text& name, sf::Color color, int size, sf::Vector2f setPosition = {0, 0}, std::string text = "");
    virtual bool running();
    virtual void pollEvents(); // sprawdzanie wydarzeń 
    ~BasicWindow(); // destruktor domyślny
    virtual int update() = 0; // uaktualnianie okna
    virtual void render() = 0; // renderowanie i wyświetlanie okna 
};
#endif
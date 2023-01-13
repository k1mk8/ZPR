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
/// @brief podstawowa klasa odpowiedzialna za wszystkie ekrany
public:
    sf::RenderWindow* window_; // okno końca gry
    sf::VideoMode video_mode_; // okno wyświetlane
    sf::Sprite sprite_; // wygląd okna
    sf::Texture texture_; // tekstura
    sf::Event sfml_event_; // event
    sf::Font font_; // czcionka
    virtual void setTexture(); // ustawia teksture
    virtual void initWindow(); // inicjowanie okna
    virtual void initFonts(); // inicjuje czcionke
    virtual void setNewTextParams(sf::Text& name, sf::Color color, int size, sf::Vector2f set_position = {0, 0}, std::string text = ""); // ustawia parametry napisów
    virtual bool running(); // sprawdzenie działania okna
    virtual void pollEvents(); // sprawdzanie wydarzeń 
    ~BasicWindow(); // destruktor domyślny
    virtual int update() = 0; // uaktualnianie okna
    virtual void render() = 0; // renderowanie i wyświetlanie okna 
};
#endif
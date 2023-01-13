#ifndef Interface_H
#define Interface_H

#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "BasicWindow.h"

class Interface:public BasicWindow
{
private:
    Button button; // przycisk rozpoczęcia gry
    Button speed1;  // przycisk doboru prędkości
    Button speed2;  // przycisk doboru prędkości
    Button speed3;  // przycisk doboru prędkości
    sf::Text standardText; // tekst paska 
    sf::Text buttonText; // tekst przycisku
    sf::Text maxPointsText; // tekst maksymalnej historycznej liczby punktów
    sf::Text buttonText1; // tekst paska prędkości
    sf::Text buttonText2; // tekst paska prędkości
    sf::Text buttonText3; // tekst paska prędkości
    void setTexture();
    void initText(); // inicjowanie tekstu
    void initButton(); // inicjowanie przycisków
public:
    Interface(); // konstruktor domyślny
    int update(); // uaktualnianie okna
    void renderGui(sf::RenderTarget* target); // renderowanie GUI
    void render(); // renderowanie i wyświetlanie okna 
};
#endif
/*
    @file Interface.h
    @author Karol Kasperek, Szymon Dyszewski
    @brief plik zawierający deklarację klasy Interface
*/

#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "BasicWindow.h"

class Interface : public BasicWindow
{
/// @brief klasa odpowiedzialna za ekran początkowego interfejsu
private:
    Button button_; // przycisk rozpoczęcia gry
    Button speed1_;  // przycisk doboru prędkości
    Button speed2_;  // przycisk doboru prędkości
    Button speed3_;  // przycisk doboru prędkości
    sf::Text standard_text_; // tekst paska 
    sf::Text button_text_; // tekst przycisku
    sf::Text max_points_text_; // tekst maksymalnej historycznej liczby punktów
    sf::Text button_text1_; // tekst paska prędkości
    sf::Text button_text2_; // tekst paska prędkości
    sf::Text button_text3_; // tekst paska prędkości
    void setTexture(); // ustawia tekstury
    void initText(); // inicjowanie tekstu
    void initButton(); // inicjowanie przycisków
public:
    Interface(); // konstruktor domyślny
    int update(); // uaktualnianie okna
    void renderGui(sf::RenderTarget* target); // renderowanie GUI
    void render(); // renderowanie i wyświetlanie okna 
};
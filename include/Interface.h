#include <bits/stdc++.h>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Button.h"
using namespace sf;

class Interface
{
private:

    Button button; // przycisk rozpoczęcia gry
    Button speed1;  // przycisk doboru prędkości
    Button speed2;  // przycisk doboru prędkości
    Button speed3;  // przycisk doboru prędkości
    VideoMode videoMode; // wyświetlanie okno
    Event sfmlEvent; // eventy
    Sprite sprite; // wygląd okna
    Texture texture; // tekstura
    Text standardText; // tekst paska 
    Text guiText; // tekst głównego ekranu
    Text buttonText; // tekst przycisku
    Text maxPointsText; // tekst maksymalnej historycznej liczby punktów
    Text buttonText1; // tekst paska prędkości
    Text buttonText2; // tekst paska prędkości
    Text buttonText3; // tekst paska prędkości
    Font font; // czcionka
    void initWindow(); // inicjowanie okna
    void initFonts(); // inicjowanie czcionki
    void initText(); // inicjowanie tekstu
    void initButton(); // inicjowanie przycisków
public:
    RenderWindow* window; // okno gry
    Interface(); // konstruktor domyślny
    ~Interface(); // destruktor domyślny
    bool running(); // sprawdzenie czy okno działa
    void pollEvents(); // // sprawdzanie wydarzeń
    int update(); // uaktualnianie okna
    void renderGui(RenderTarget* target); // renderowanie GUI
    void render(); // renderowanie i wyświetlanie okna 
};
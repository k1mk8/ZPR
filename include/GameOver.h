#ifndef GameOver_H
#define GameOver_H

#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "BasicWindow.h"

using namespace sf;


class GameOver:public BasicWindow
{
private:
    RenderWindow* window; // okno końca gry
    Button buttonYes; // przycisk powtórzenia gry
    Button buttonNo; // przycisk zakończenia gry
    VideoMode videoMode; // okno wyświetlane
    Event sfmlEvent; // event
    Sprite sprite; // wygląd okna
    Texture texture; // tekstura
    virtual void initWindow(); // inicjowanie okna
    virtual void initButton(); // inicjowanie przycisków
public:
    GameOver(); // konstruktor domyślny
    ~GameOver(); // destruktor domyślny
    int whichButtonPressed(); // sprawdzenie czy przycisk wciśnięty
    void pollEvents(); // sprawdzanie wydarzeń 
    int update(); // uaktualnianie okna
    void render(); // renderowanie i wyświetlanie okna 
};

#endif
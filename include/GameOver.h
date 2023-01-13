#ifndef GameOver_H
#define GameOver_H

#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "BasicWindow.h"


class GameOver:public BasicWindow
{
private:
    Button buttonYes; // przycisk powtórzenia gry
    Button buttonNo; // przycisk zakończenia gry
    void setTexture(); // inicjowanie okna
    void initButton(); // inicjowanie przycisków
public:
    GameOver(); // konstruktor domyślny
    int update(); // uaktualnianie okna
    void render(); // renderowanie i wyświetlanie okna 
};

#endif
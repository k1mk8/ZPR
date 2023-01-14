/*
    @file GameOver.h
    @author Karol Kasperek, Szymon Dyszewski
    @brief plik zawierający deklarację klasy GameOver
*/

#ifndef GameOver_H
#define GameOver_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <bits/stdc++.h>

#include "BasicWindow.h"

class GameOver : public BasicWindow {
  /// @brief klasa odpowiedzialna za ekran końcowy
private:
  Button button_yes_; // przycisk powtórzenia gry
  Button button_no_;  // przycisk zakończenia gry
  void setTexture();  // inicjowanie okna
  void initButton();  // inicjowanie przycisków
public:
  GameOver();    // konstruktor domyślny
  int update();  // uaktualnianie okna
  void render(); // renderowanie i wyświetlanie okna
};

#endif
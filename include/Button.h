/*
    @file Button.h
    @author Karol Kasperek, Szymon Dyszewski
    @brief plik zawierający deklarację klasy Button
*/

#ifndef Button_H
#define Button_H

#include <bits/stdc++.h>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class Button {
  /// @brief klasa odpowiedzialna za klikalny button do interakcji z
  /// użytkownikiem
private:
  sf::RectangleShape button_; // zmienna przetrzymująca kształt przycisku
public:
  Button(); // konstruktor domyślny
  Button(sf::Vector2f size, sf::Color color,
         sf::Vector2f pos); // konstruktor przyjmujący wartości startowe
  ~Button();                // destruktor
  const sf::RectangleShape &getButton() const; // zwraca przycisk
  bool isButtonPressed(
      sf::RenderWindow *window); // sprawdza czy button jest wciśnięty
};
#endif
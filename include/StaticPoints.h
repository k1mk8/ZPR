/*
    @file StaticPoints.h
    @author Karol Kasperek, Szymon Dyszewski
    @brief plik zawierający deklarację klasy StaticPoints
*/

#ifndef StaticPoints_H
#define StaticPoints_H

#include <vector>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "Player.h"

enum StaticPointsTypes { FOOD = 0, SPIKES }; // typy punktów statycznych

class StaticPoints : public Player {
  /// @brief klasa odpowiedzialna za obiekty statyczne na mapie
private:
  sf::CircleShape shape_;                      // kształ punktu
  clock_t fresh_spawned_time_;                 // czas podziału gracza
  int type_;                                   // typ punktu
  int mass_ = 5;                               // masa punktu
  float speed_ = 0;                            // prędkość punktu
  float direction_ = 0;                        // kierunek punktu
  void makeShape(std::vector<Player> players); // tworzy punkt
public:
  StaticPoints(int type, std::vector<Player> players); // domyślny konstruktor
  StaticPoints(int type, float X, float Y);            // konstruktor pozycyjny
  StaticPoints(int type, float X, float Y, float speed,
               float direction);                // konstruktor pozycyjny
  virtual ~StaticPoints();                      // destruktor
  const sf::CircleShape getShape() const;       // zwraca kształt punktu
  const sf::Vector2f &getPlayerPostion() const; // getter pozycji gracza
  const int &getType() const;                   // zwraca typ punktu
  const int &getMass() const;                   // zwraca mase punktu
  void render(sf::RenderTarget &target);        // renderowanie punktu
  void calculateSpeed(); // oblicza prędkość wystrzeliwanych punktów
};
#endif
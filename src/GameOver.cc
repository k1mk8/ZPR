/*
    @file GameOver.cc
    @author Karol Kasperek, Szymon Dyszewski
    @brief plik zawierający implementację klasy GameOver
*/

#include "GameOver.h"

using namespace std;
using namespace sf;

void GameOver::setTexture() {
  /// @brief inifcuje początkowe wartości interfejsu
  this->texture_.loadFromFile("images/game_over.png");
  this->sprite_.setTexture(texture_);
  this->video_mode_ = VideoMode(1920, 1080);
}

void GameOver::initButton() {
  /// @brief iniciuje przyciski do zakończenia gry
  this->button_yes_ =
      Button(Vector2f(125, 60), Color::Transparent, Vector2f(800, 750));
  this->button_no_ =
      Button(Vector2f(125, 60), Color::Transparent, Vector2f(1000, 750));
}

GameOver::GameOver() {
  /// @brief konstruktor domyślny
  this->initWindow();
  this->initButton();
}

int GameOver::update() {
  /// @brief funkcja sprawdzająca czy wydarzyły się jakieś interakcje od
  /// użytkownika
  /// @return czy przycisk rozpoczęcia gry został wciśnięty
  this->pollEvents();
  if (this->button_yes_.isButtonPressed(window_))
    return 1;
  else if (this->button_no_.isButtonPressed(window_))
    return 2;
  return 0;
}

void GameOver::render() {
  /// @brief funkcja renderująca i wyświetlająca okno
  this->window_->clear(Color::White);
  this->window_->draw(sprite_);
  this->window_->draw(button_yes_.getButton());
  this->window_->draw(button_no_.getButton());
  this->window_->display();
}
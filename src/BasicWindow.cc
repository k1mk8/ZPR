/*
    @file BasicWindow.cc
    @author Karol Kasperek, Szymon Dyszewski
    @brief plik zawierający implementację klasy BasicWindow
*/

#include "BasicWindow.h"

using namespace std;
using namespace sf;

void BasicWindow::setTexture() {}

void BasicWindow::initWindow() {
  /// @brief inifcuje początkowe wartości interfejsu
  this->setTexture();
  this->window_ = new RenderWindow(this->video_mode_, "Agario",
                                   Style::Close | Style::Titlebar);
  this->window_->clear(Color::White);
  this->window_->setFramerateLimit(60);
}

void BasicWindow::initFonts() {
  /// @brief ustawia czcionkę tekstu
  if (!this->font_.loadFromFile("fonts/MilkyHoney.ttf")) {
    cout << "COULD NOT LOAD MilkyHoney.ttf"
         << "\n";
  }
}

void BasicWindow::setNewTextParams(Text &name, Color color, int size,
                                   Vector2f setPosition, string text) {
  /// @brief ustawia parametry podanego tekstu
  /// @param name nazwa tekstu
  /// @param color kolor tekstu
  /// @param size wielkość tekstu
  /// @param setPosition pozycja tekstu na ekranie
  /// @param text zawartość
  name.setFont(this->font_);
  name.setFillColor(color);
  name.setCharacterSize(size);
  name.setPosition(setPosition);
  name.setString(text);
}

bool BasicWindow::running() {
  /// @brief funkcja sprawdzająca czy okno jest otwarte
  /// @return prawda lub fałsz, czy okno jest otwarte
  return this->window_->isOpen();
}

bool BasicWindow::pollEvents() {
  /// @brief funkcja sprawdzająca czy okno ma być zamknięte
  bool close = false;
  while (this->window_->pollEvent(this->sfml_event_)) {
    if (this->sfml_event_.type == Event::Closed || 
        this->sfml_event_.key.code == Keyboard::Escape) {
      this->window_->close();
      close = true;
      break;
    }
    break;
  }
  return close;
}

BasicWindow::~BasicWindow() {
  /// @brief destruktor domyślny
  delete this->window_;
}

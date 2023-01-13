#include "GameOver.h"

using namespace std;
using namespace sf;

void GameOver::setTexture()
{
    /// @brief inifcuje początkowe wartości interfejsu
    this->texture.loadFromFile("images/game_over.png");
    this->sprite.setTexture(texture);
    this->videoMode = VideoMode(1920, 1080);
}

void GameOver::initButton()
{
    /// @brief iniciuje przyciski do zakończenia gry
    this->buttonYes = Button(Vector2f(125, 60), Color::Transparent, Vector2f(800, 750));
    this->buttonNo = Button(Vector2f(125, 60), Color::Transparent, Vector2f(1000, 750));
}

GameOver::GameOver()
{
    /// @brief konstruktor domyślny
    this->initWindow();
    this->initButton();
}

int GameOver::update()
{
    /// @brief funkcja sprawdzająca czy wydarzyły się jakieś interakcje od użytkownika
    /// @return czy przycisk rozpoczęcia gry został wciśnięty
    this->pollEvents();
    if(this->buttonYes.isButtonPressed(window))
        return 1;
    else if(this->buttonNo.isButtonPressed(window))
        return 2;
    return 0;
}

void GameOver::render()
{
    /// @brief funkcja renderująca i wyświetlająca okno
    this->window->clear(Color::White);
    this->window->draw(sprite);
    this->window->draw(buttonYes.getButton());
    this->window->draw(buttonNo.getButton());
    this->window->display();
}
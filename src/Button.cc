/*
    @file Button.cc
    @author Karol Kasperek, Szymon Dyszewski
    @brief plik zawierający implementację klasy Button
*/

#include <Button.h>

using namespace std;
using namespace sf;

Button::Button()
{
    /// @brief konstruktor domyślny klasy button
    this->button_.setSize(Vector2f(1, 1));
    this->button_.setFillColor(Color::Blue);
    this->button_.setPosition(Vector2f(5, 5));
}
Button::Button(Vector2f size = Vector2f(125, 60), Color color = Color::Cyan, Vector2f pos = Vector2f(560, 500))
{
    /// @brief konstruktor klasy button tworzący obiekt o podanych na wejściu danych
    /// @param size wielkość przycisku
    /// @param color kolor przycisku
    /// @param pos pozycja przycisku
    this->button_.setSize(size);
    this->button_.setFillColor(color);
    this->button_.setPosition(pos);
}
Button::~Button()
{
    /// @brief destruktor klasy
}

const RectangleShape& Button::getButton() const
{
    /// @brief getter przycisku
    /// @return przycisk RectangleShape
    return this->button_;
}

bool Button::isButtonPressed(RenderWindow* window)
{
    /// @brief sprawdza czy dany przycisk jest wciśnięty
    /// @param window ekran gry
    /// @return prawda lub fałsz czy przycisk wciśnięty
    IntRect rect(this->button_.getPosition().x, this->button_.getPosition().y, this->button_.getGlobalBounds().width, this->button_.getGlobalBounds().height);
        if (rect.contains(Mouse::getPosition(*window)) && (sf::Mouse::isButtonPressed(sf::Mouse::Left))) {
                return true;
        }
        return false;
}
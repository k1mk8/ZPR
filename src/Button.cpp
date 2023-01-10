#include <Button.h>

using namespace std;
Button::Button()
{
    /// @brief konstruktor domyślny klasy button
    this->button.setSize(Vector2f(1, 1));
    this->button.setFillColor(Color::Blue);
    this->button.setPosition(Vector2f(5, 5));
}
Button::Button(Vector2f size = Vector2f(125, 60), Color color = Color::Cyan, Vector2f pos = Vector2f(560, 500))
{
    /// @brief konstruktor klasy button tworzący obiekt o podanych na wejściu danych
    /// @param size wielkość przycisku
    /// @param color kolor przycisku
    /// @param pos pozycja przycisku
    this->button.setSize(size);
    this->button.setFillColor(color);
    this->button.setPosition(pos);
}
Button::~Button()
{
    /// @brief destruktor klasy
}

const RectangleShape& Button::getButton() const
{
    /// @brief getter przycisku
    /// @return przycisk RectangleShape
    return this->button;
}

const bool Button::isButtonPressed(RenderWindow* window) const
{
    /// @brief sprawdza czy dany przycisk jest wciśnięty
    /// @param window ekran gry
    /// @return prawda lub fałsz czy przycisk wciśnięty
    IntRect rect(this->button.getPosition().x, this->button.getPosition().y, this->button.getGlobalBounds().width, this->button.getGlobalBounds().height);
        if (rect.contains(Mouse::getPosition(*window)) && (sf::Mouse::isButtonPressed(sf::Mouse::Left))) {
                return true;
        }
        return false; 
}
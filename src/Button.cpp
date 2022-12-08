#include <Button.h>

using namespace std;

Button::Button(Vector2f size = Vector2f(125, 60), Color color = Color::Cyan, Vector2f pos = Vector2f(560, 500))
{
    this->button.setSize(size);
    this->button.setFillColor(color);
    this->button.setPosition(pos);
}
Button::~Button()
{

}

const RectangleShape& Button::getButton() const
{
    return this->button;
}

const bool Button::isButtonPressed(RenderWindow* window) const
{
    IntRect rect(this->button.getPosition().x, this->button.getPosition().y, this->button.getGlobalBounds().width, this->button.getGlobalBounds().height);
        if (rect.contains(Mouse::getPosition(*window)) && (sf::Mouse::isButtonPressed(sf::Mouse::Left))) {
                return true;
        }
        return false; 
}
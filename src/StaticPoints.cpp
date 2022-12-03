#include "StaticPoints.h"

void StaticPoints::makeShape(const RenderWindow& window)
{

    this->shape.setRadius(5);
    Color color;
    switch (this->type)
    {
    case FOOD:
        color = Color::Blue;
        break;
    case SPIKES:
        color = Color::Yellow;
        this->shape.setOutlineColor(Color::Red);
        break;
    }
    this->shape.setFillColor(color);
    this->shape.setPosition(
        Vector2f(static_cast<float>(rand() % window.getSize().x - this->shape.getGlobalBounds().width),
        static_cast<float>(rand() % window.getSize().y - this->shape.getGlobalBounds().height))
    );
}

StaticPoints::StaticPoints(const RenderWindow& window, int type)
        : type(type)
{
    this->makeShape(window);
}

StaticPoints::~StaticPoints()
{

}

const CircleShape StaticPoints::getShape() const
{
    return this->shape;
}

const int& StaticPoints::getType() const
{
    return this->type;
}

const int& StaticPoints::getMass() const
{
    return this->mass;
}

void StaticPoints::render(RenderTarget& target)
{
    target.draw(this->shape);
}
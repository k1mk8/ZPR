#include "StaticPoints.h"

void StaticPoints::makeShape(const View& view, IntRect rect)
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
    Vector2f size = view.getSize();
    int t[2];
    t[0] = -1;
    t[1] = 1;
    int x = static_cast<float>((rand() % (int(size.x) / 2)) * t[(rand() % 2)] - this->shape.getGlobalBounds().width);
    int y = static_cast<float>((rand() % (int(size.y) / 2)) * t[(rand() % 2)] - this->shape.getGlobalBounds().height);
    while(rect.contains(x,y))
    {
        x = static_cast<float>((rand() % (int(size.x) / 2)) * t[(rand() % 2)] - this->shape.getGlobalBounds().width);
        y = static_cast<float>((rand() % (int(size.y) / 2)) * t[(rand() % 2)] - this->shape.getGlobalBounds().height);
    }
    this->shape.setPosition(Vector2f(x,y));
}

StaticPoints::StaticPoints(const View& window, int type, IntRect rect)
        : type(type)
{
    this->makeShape(window, rect);
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

void StaticPoints::eatMass(const int food)
{
    this->mass += food;
}
// void StaticPoints::checkSpikeMass(const View& window)
// {
//     if(this->type == StaticPointsTypes::SPIKES){
//         if(this->mass > 25){
//             this->mass = 5;
//             StaticPoints(window, SPIKES);
//         }
//     }
// }

void StaticPoints::render(RenderTarget& target)
{
    target.draw(this->shape);
}
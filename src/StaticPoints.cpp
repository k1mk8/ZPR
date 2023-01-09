#include "StaticPoints.h"

void StaticPoints::makeShape(std::vector<Player> rect)
{
    Color color;
    switch (this->type)
    {
    case FOOD:
        color = Color::Blue;
        this->mass = 1;
        this->shape.setRadius(5);
        break;
    case SPIKES:
        color = Color::Red;
        this->shape.setRadius(30);
        this->mass = 30;
        break;
    }
    this->shape.setFillColor(color);
    Vector2f size = Vector2f(9600, 5400);
    int t[2];
    t[0] = -1;
    t[1] = 1;
    bool contain = true;
    int x, y;
    while(contain)
    {
        x = static_cast<float>((rand() % (int(size.x) / 2)) * t[(rand() % 2)] - this->shape.getGlobalBounds().width);
        y = static_cast<float>((rand() % (int(size.y) / 2)) * t[(rand() % 2)] - this->shape.getGlobalBounds().height);
        for(auto& it : rect)
        {
            CircleShape point;
            point.setRadius(5);
            point.setPosition(x,y);
            if(it.getShape().getGlobalBounds().intersects(point.getGlobalBounds())){
                contain = true;
                break;
            }
            else
            {
                contain = false;
            }
        }
    }
    this->shape.setPosition(Vector2f(x,y));
}

StaticPoints::StaticPoints(int type, std::vector <Player> rect)
        : type(type)
{
    this->makeShape(rect);
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
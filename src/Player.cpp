#include "Player.h"

void Player::Variables(const int mass)
{
    this->speed = 5.f;
    this->mass = 10;
}

void Player::makeShape()
{
    this->shape.setFillColor(Color::Green);
    this->shape.setRadius(getMass());
}

Player::Player(float x, float y, const int mass)
{
    this->shape.setPosition(x,y);
    this->timeOfLive = 0;
    this->Variables(mass);
    this->makeShape();
}

Player::~Player()
{

}

const CircleShape & Player::getShape() const
{
    return this->shape;
}

const int & Player::getMass() const
{
    return this->mass;
}

const int & Player::getSpeed() const
{
    return this->speed;
}

const Vector2f & Player::getPlayerPostion() const
{
    return this->shape.getPosition();
}

void Player::setMass(const int weight)
{
    this->mass = weight;
}

void Player::grow(const int food)
{
    this->mass += food;
    this->shape.setRadius(this->getMass());
}

void Player::splitMass()
{
    if(mass > 20){
        this->mass /= 2;    
    }   
}

void Player::split()
{
    if(Keyboard::isKeyPressed(Keyboard::Space)){
        this->splitMass();
        this->shape.setRadius(this->getMass());
    }
}

void Player::loseMass()
{
    if(this->mass > 20)
    {
        this->mass -= 10;
    }
}

void Player::shootingMass()
{
    if(Keyboard::isKeyPressed(Keyboard::T)){
        this->loseMass();
        this->shape.setRadius(this->getMass());
    }
}

void Player::move()
{
    if(Keyboard::isKeyPressed(Keyboard::W)){
        this->shape.move(0.f, -this->speed);
    }
    else if(Keyboard::isKeyPressed(Keyboard::S)){
        this->shape.move(0.f, this->speed);
    }
    else if(Keyboard::isKeyPressed(Keyboard::A)){
        this->shape.move(-this->speed, 0.f);
    }
    else if(Keyboard::isKeyPressed(Keyboard::D)){
        this->shape.move(this->speed, 0.f);
    }
}

void Player::checkMapCollision(const View* target)
{

    if(this->shape.getGlobalBounds().left <= -9600.f){
    this->shape.setPosition(-9600.f, this->shape.getGlobalBounds().top);
    }
    if(this->shape.getGlobalBounds().left + this->shape.getGlobalBounds().width >= target->getSize().x){
        this->shape.setPosition(target->getSize().x - this->shape.getGlobalBounds().width, this->shape.getGlobalBounds().top);
    }
    if(this->shape.getGlobalBounds().top <= -5400.f){
        this->shape.setPosition(this->shape.getGlobalBounds().left, -5400.f);
    }
    if(this->shape.getGlobalBounds().top + this->shape.getGlobalBounds().height >= target->getSize().y){
        this->shape.setPosition(this->shape.getGlobalBounds().left, target->getSize().y - this->shape.getGlobalBounds().height);
    }
}

void Player::setPosition(const View* target)
{
    this->move();
    this->split();
    this->checkMapCollision(target);
}

void Player::render(RenderTarget* target)
{
    target->draw(this->shape);
}
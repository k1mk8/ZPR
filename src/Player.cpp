#include "Player.h"

void Player::Variables(const int mass)
{
    this->speed = 10;
    this->startingSpeed = 10;
    this->mass = mass;
}

void Player::makeShape()
{
    this->shape.setFillColor(Color::Green);
    this->shape.setRadius(log(mass)/log(1.05));
}

void Player::calculateSpeed()
{
    this->speed = this->startingSpeed - (log(this->mass) / log(4));
}

void Player::connect(std::vector<Player>& players)
{
    clock_t actualTime = clock();
    if(players.size() > 1){
        cout<<((double)(actualTime - this->splitTime) / CLOCKS_PER_SEC)<<endl;
        if(((double)(actualTime - this->splitTime) / CLOCKS_PER_SEC) > 30.0){
            int mass = 0;
            for(auto& it : players){
                mass += it.getMass();
            }
            Player player = Player(players[0].getPlayerPostion().x, players[0].getPlayerPostion().x, mass);
            players.clear();
            players.push_back(player);
        }
    }
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

const float & Player::getSpeed() const
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
    int mass = this->getMass();
    this->shape.setRadius(log(mass)/log(1.05));
}

void Player::splitMass()
{
    if(this->mass > 20){
        this->mass /= 2;    
        this->shape.setRadius(log(mass)/log(1.05));
    }   
}

void Player::split(std::vector<Player>& players)
{
    bool flag = false;
    while(Keyboard::isKeyPressed(Keyboard::Space)){
        flag = true;
    }
    if(flag){
        for(auto& it : players){
            if(players.size() < 16){
                if(it.getMass() > 30){
                    splitTime = clock();
                    it.splitMass();
                    Player player = Player(it.getPlayerPostion().x+ 2 * log(it.getMass())/log(1.05), it.getPlayerPostion().y + 2 * log(it.getMass())/log(1.05), it.getMass());
                    players.push_back(player);
                }
            }
        }
    }
}

void Player::splitBySpike(std::vector <Player>& players)
{
    if(players.size() + 8 <=16){
        this->setMass(this->getMass()/8);
        for(int i=0;i<8;++i){
            Player player = Player(this->getPlayerPostion().x, this->getPlayerPostion().x, this->getMass());
        }
    }
}

void Player::loseMass()
{
    if(this->mass >= 20)
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
    this->calculateSpeed();
    if(Keyboard::isKeyPressed(Keyboard::W)){
        this->shape.move(0, -this->speed);
    }
    else if(Keyboard::isKeyPressed(Keyboard::S)){
        this->shape.move(0, this->speed);
    }
    else if(Keyboard::isKeyPressed(Keyboard::A)){
        this->shape.move(-this->speed, 0);
    }
    else if(Keyboard::isKeyPressed(Keyboard::D)){
        this->shape.move(this->speed, 0);
    }
    else if(Keyboard::isKeyPressed(Keyboard::P)){
        this->setMass(0);
    }
}

void Player::checkMapCollision()
{

    if(this->shape.getGlobalBounds().left <= -4800){
        this->shape.setPosition(-4800, this->shape.getGlobalBounds().top);
    }
    if(this->shape.getGlobalBounds().left + this->shape.getGlobalBounds().width >= 4800){
        this->shape.setPosition(4800 - this->shape.getGlobalBounds().width, this->shape.getGlobalBounds().top);
    }
    if(this->shape.getGlobalBounds().top <= -2700){
        this->shape.setPosition(this->shape.getGlobalBounds().left, -2700);
    }
    if(this->shape.getGlobalBounds().top + this->shape.getGlobalBounds().height >= 2700){
        this->shape.setPosition(this->shape.getGlobalBounds().left, 2700 - this->shape.getGlobalBounds().height);
    }
}

void Player::setPosition(std::vector<Player>& players)
{
    this->move();
    this->split(players);
    this->connect(players);
    this->checkMapCollision();
}

void Player::render(RenderTarget& target)
{
    target.draw(this->shape);
}
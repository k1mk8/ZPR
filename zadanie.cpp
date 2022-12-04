#include<iostream>
#include<ctime>
#include<vector>
#include<sstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>


enum StaticPointsTypes {FOOD = 0, SPIKES};
using namespace sf;
using namespace std;

class Player
{
private:
    CircleShape shape;
    float speed;
    int mass;
    int timeOfLive;
    vector<Player> playerBalls;
    void Variables(const int mass);
    void makeShape();
public:
    Player(float x = 0.f, float y = 0.f, const int mass = 10);
    virtual ~Player();

    const CircleShape& getShape() const;
    const int& getMass() const;
    const int& getSpeed() const;
    const vector<Player>& getPlayerBalls() const;
    const Vector2f& getPlayerPostion() const;

    void setMass(const int weight);
    void grow(const int food);

    void splitMass();
    void split();

    void loseMass();
    void shootingMass();

    void move();
    void checkMapCollision(const View* target);
    void setPosition(const View* target);
    void render(RenderTarget* target);
};

class StaticPoints
{
private:
    CircleShape shape;
    int type;
    int mass = 5;
    void makeShape(const View& window);
public:
    StaticPoints(const View& window, int type);
    virtual ~StaticPoints();

    const CircleShape getShape() const;
    const int& getType() const;
    const int& getMass() const;

    void eatMass(const int food);
    void checkSpikeMass(const View& window);
    void render(RenderTarget& target);
};

class Interface
{
private:
    VideoMode videoMode;
    Event sfmlEvent;

    Player player;

    Sprite sprajt;
    Texture texture;

    Text standardText;
    Font font;
    Text guiText;
    IntRect playGame;

    void initWindow();
    void initFonts();
    void initText();
public:
    RenderWindow* window;
    Interface();
    ~Interface();

    const bool running() const;
    void pollEvents();
    void update();
    void renderGui(RenderTarget* target);
    void render();
};

class Game
{
private:
    VideoMode videoMode;
    RenderWindow* window;
    bool endGame;
    Event sfmlEvent;

    Player player;

    Font font;
    Text guiText;
    Text endGameText;

    vector<StaticPoints> staticPoints;
    float spawnTimerMax;
    float spawnTimer;
    int maxStaticPoints;
    int totalPoints;

    void variables();
    void initWindow();
    void initFonts();
    void initText();
    void initButtons();
public:
    Game();
    ~Game();

    const bool& getEndGame() const;

    const bool running() const;
    void pollEvents();

    void calculateTotalPoints();
    void spawnStaticPoints();
    const int randPointType() const;
    void updatePlayer();
    void updateCollision();
    void updateGui();
    void update();

    void renderGui(RenderTarget* target);
    void render();
};

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

const vector<Player>& Player::getPlayerBalls() const
{
    return this->playerBalls;
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
        if(this->playerBalls.size() == 0){
            Vector2f x = this->shape.getPosition();
            playerBalls.push_back(Player(x.x+this->mass, x.y, this->mass / 2));
            playerBalls.push_back(Player(x.x, x.y, this->mass / 2));
        }
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
        if(this->getPlayerBalls().size() > 0)
        {
            for(auto i : this->getPlayerBalls()){
            i.shape.move(0.f, -this->speed);
            }
        }
        else
        {
            this->shape.move(0.f, -this->speed);
        }
    }
    else if(Keyboard::isKeyPressed(Keyboard::S)){
        if(this->getPlayerBalls().size() > 0)
        {
            for(auto i : this->getPlayerBalls()){
            i.shape.move(0.f, this->speed);
            }
        }
        else
        {
            this->shape.move(0.f, this->speed);
        }
    }
    else if(Keyboard::isKeyPressed(Keyboard::A)){
        if(this->getPlayerBalls().size() > 0)
        {
            for(auto i : this->getPlayerBalls()){
            i.shape.move(-this->speed, 0.f);
            }
        }
        else
        {
            this->shape.move(-this->speed, 0.f);
        }
    }
    else if(Keyboard::isKeyPressed(Keyboard::D)){
        if(this->getPlayerBalls().size() > 0)
        {
            for(auto i : this->getPlayerBalls()){
            i.shape.move(this->speed, 0.f);
            }
        }
        else
        {
            this->shape.move(this->speed, 0.f);
        }
    }
}

void Player::checkMapCollision(const View* target)
{
    if(this->getPlayerBalls().size() > 0)
    {
        for(auto i : this->getPlayerBalls())
        { 
            if(i.shape.getGlobalBounds().left <= 0.f){
                i.shape.setPosition(0.f, i.shape.getGlobalBounds().top);
            }
            if(i.shape.getGlobalBounds().left + i.shape.getGlobalBounds().width >= target->getSize().x){
                i.shape.setPosition(target->getSize().x - i.shape.getGlobalBounds().width, i.shape.getGlobalBounds().top);
            }
            if(i.shape.getGlobalBounds().top <= 0.f){
                i.shape.setPosition(i.shape.getGlobalBounds().left, 0.f);
            }
            if(i.shape.getGlobalBounds().top + i.shape.getGlobalBounds().height >= target->getSize().y){
                i.shape.setPosition(i.shape.getGlobalBounds().left, target->getSize().y - i.shape.getGlobalBounds().height);
            }   
        }
    }
    else
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

void StaticPoints::makeShape(const View& view)
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
    this->shape.setPosition(
        Vector2f(static_cast<float>((rand() % (int(size.x) / 2)) * t[(rand() % 2)] - this->shape.getGlobalBounds().width),
        static_cast<float>((rand() % (int(size.y) / 2)) * t[(rand() % 2)] - this->shape.getGlobalBounds().height))
    );
}

StaticPoints::StaticPoints(const View& window, int type)
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

void StaticPoints::eatMass(const int food)
{
    this->mass += food;
}
void StaticPoints::checkSpikeMass(const View& window)
{
    if(this->type == StaticPointsTypes::SPIKES){
        if(this->mass > 25){
            this->mass = 5;
            StaticPoints(window, SPIKES);
        }
    }
}

void StaticPoints::render(RenderTarget& target)
{
    target.draw(this->shape);
}

void Interface::initWindow()
{
    texture.loadFromFile("tlo.png");
    sprajt.setTexture(texture);
    this->videoMode = VideoMode(1200.f, 630.f);
    this->window = new RenderWindow(this->videoMode, "Agario", Style::Close | Style::Titlebar);
    this->window->clear(Color::White);
    this->window->setFramerateLimit(60);
}

void Interface::initFonts()
{
    if(!this->font.loadFromFile("fonts/MilkyHoney.ttf")){
        cout << " COULD NOT LOAD MilkyHoney.ttf" << "\n";
    }
}

void Interface::initText()
{
    this->guiText.setFont(this->font);
    this->guiText.setFillColor(Color::Black);
    this->guiText.setCharacterSize(32);

    this->standardText.setFont(this->font);
    this->standardText.setFillColor(Color::Black);
    this->standardText.setCharacterSize(25);
    this->standardText.setPosition(Vector2f(280,100));
    this->standardText.setString("\t\t\t\t\t\tWitamy w grze AGARIO!\n Prosze wcisnac przycisk graj, aby rozpoczac rozgrywke!");
}

Interface::Interface()
{
    this->initWindow();
    this->initFonts();
    this->initText();
}

Interface::~Interface()
{
    delete this->window;
}

const bool Interface::running() const
{
    return this->window->isOpen();
}

void Interface::pollEvents()
{
    while(this->window->pollEvent(this->sfmlEvent))
    {
        switch(this->sfmlEvent.type)
        {
        case Event::Closed:
            this->window->close();
            break;
        case Event::KeyPressed:
            if(this->sfmlEvent.key.code == Keyboard::Escape){
                this->window->close();
            }
        }
        break;
    }
}

void Interface::update()
{
    this->pollEvents();
}

void Interface::renderGui(RenderTarget* target)
{
    target->draw(this->standardText);
}

void Interface::render()
{
    this->window->clear(Color::White);
    this->window->draw(sprajt);
    this->renderGui(this->window);
    this->window->display();
}

void Game::variables()
{
    this->endGame = false;
    this->spawnTimerMax = 2.f;
    this->spawnTimer = this->spawnTimerMax;
    this->maxStaticPoints = 1000;
    this->totalPoints = 10;

}

void Game::initWindow()
{
    View view(Vector2f(920.f, 540.f), Vector2f(19200.f, 10800.f));
    view.zoom(0.1f);
    view.setCenter(this->player.getPlayerPostion());
    this->videoMode = VideoMode(1920.f, 1080.f);
    this->window = new RenderWindow(this->videoMode, "Agario", Style::Close | Style::Titlebar);
    this->window->clear(Color::White);
    this->window->setFramerateLimit(60);
    this->window->setView(view);
}

void Game::initFonts()
{
    if(!this->font.loadFromFile("fonts/MilkyHoney.ttf")){
        cout << " COULD NOT LOAD MilkyHoney.ttf" << "\n";
    }
}

void Game::initText()
{
    this->guiText.setFont(this->font);
    this->guiText.setFillColor(Color::Black);
    this->guiText.setCharacterSize(32);

    this->endGameText.setFont(this->font);
    this->endGameText.setFillColor(Color::Red);
    this->endGameText.setCharacterSize(60);
    Vector2f playerPos = this->player.getPlayerPostion();
    this->endGameText.setPosition(Vector2f(20, 100));
    this->endGameText.setString("YOU HAVE BEEN EATEN! GAME OVER!");
}

Game::Game()
{
    this->variables();
    this->initWindow();
    this->initFonts();
    this->initText();
}

Game::~Game()
{
    delete this->window;
}

const bool& Game::getEndGame() const
{
    return this->endGame;
}

const bool Game::running() const
{
    return this->window->isOpen();
}

void Game::pollEvents()
{
    while(this->window->pollEvent(this->sfmlEvent))
    {
        switch(this->sfmlEvent.type)
        {
        case Event::Closed:
            this->window->close();
            break;
        case Event::KeyPressed:
            if(this->sfmlEvent.key.code == Keyboard::Escape){
                this->window->close();
            }
        }
        break;
    }
}

void Game::calculateTotalPoints()
{
    int points = 0;
    vector<Player> totalMass = this->player.getPlayerBalls();
    for(auto i : totalMass){
        points += i.getMass();
    }
    this->totalPoints = points;
}

void Game::spawnStaticPoints()
{
    if(this->spawnTimer < this->spawnTimerMax){
        this->spawnTimer += 1.f;
    }
    else{
        if(this->staticPoints.size() < this->maxStaticPoints){
            this->staticPoints.push_back(StaticPoints(this->window->getView(), this->randPointType()));
            this->spawnTimer = 0.f;
        }
    }
}

const int Game::randPointType() const
{
    int type = StaticPointsTypes::FOOD;
    int value = rand() % 100 + 1;
    if(value > 98){
        type = StaticPointsTypes::SPIKES;
    }

    return type;
}

void Game::updatePlayer()
{
    this->player.setPosition(&this->window->getView());
    View view = this->window->getView();
    view.setCenter(this->player.getPlayerPostion());
    this->window->setView(view);
}

void Game::updateCollision()
{
    for(size_t i = 0; i < this->staticPoints.size(); i++){
        if(this->player.getShape().getGlobalBounds().intersects(this->staticPoints[i].getShape().getGlobalBounds())){
            switch(this->staticPoints[i].getType())
            {
                case StaticPointsTypes::FOOD:
                    this->player.grow(staticPoints[i].getMass());
                    break;
                // TODO co jeśli się zetknie ze SPIKE
            }
            this->staticPoints.erase(this->staticPoints.begin() + i);
        }
    }
}

void Game::updateGui()
{
    stringstream ss;
    ss << " - Points: " << this->player.getMass() << "\n";
    Vector2f playerPos = this->player.getPlayerPostion();
    this->guiText.setPosition(playerPos + Vector2f(-960, -540));
    this->guiText.setString(ss.str());
}

void Game::update()
{
    this->pollEvents();
    if(this->endGame == false){
        this->spawnStaticPoints();
        this->updatePlayer();
        this->updateCollision();
        this->updateGui();
    }
}

void Game::renderGui(RenderTarget* target)
{
    target->draw(this->guiText);
}

void Game::render()
{
    this->window->clear(Color::White);

    if(player.getPlayerBalls().size() == 0){
        this->player.render(this->window);
    }
    else{
        for(auto i : this->player.getPlayerBalls()){
            i.render(this->window);
        }
    }

    for(auto i : this->staticPoints){

        i.render(*this->window);
    }

    this->renderGui(this->window);

    if(this->endGame == true){
        this->window->draw(this->endGameText);
    }

    this->window->display();
}

int main()
{
    srand(static_cast<unsigned>(time(0)));

    Game game;

    Interface interface;
    Event event;
    // while(interface.running())
    // {
    //     interface.update();
    //     interface.render();
    // }
    while(game.running())
    {
        game.update();
        game.render();
    }
    return 0;
}
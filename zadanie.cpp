#include<iostream>
#include<ctime>
#include<vector>
#include<sstream>
#include<fstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>


enum StaticPointsTypes {FOOD = 0, SPIKES};
using namespace sf;
using namespace std;




class Button
{
private:
    RectangleShape button;
public:
    Button(Vector2f size, Color color, Vector2f pos);
    ~Button();
    const RectangleShape& getButton() const;
    const bool isButtonPressed(RenderWindow* window) const;
};

class GameOver
{
private:
    Button buttonYes;
    Button buttonNo;
    VideoMode videoMode;
    Event sfmlEvent;

    Sprite sprajt;
    Texture texture;

    void initWindow();
    void initButton();
public:
    RenderWindow* window;
    GameOver();
    ~GameOver();
    const int buttonPressed() const;
    void render();
};

class Player
{
private:
    CircleShape shape;
    float speed;
    int mass;
    int timeOfLive;
    void Variables(const int mass);
    void makeShape();
public:
    Player(float x = 0.f, float y = 0.f, const int mass = 10);
    virtual ~Player();

    const CircleShape& getShape() const;
    const int& getMass() const;
    const int& getSpeed() const;
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
    void makeShape(const View& window, IntRect rect);
public:
    StaticPoints(const View& window, int type, IntRect rect);
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

    Button button;
    VideoMode videoMode;
    Event sfmlEvent;

    Player player;

    Sprite sprajt;
    Texture texture;

    Text standardText;
    Text guiText;
    Text buttonText;
    Text maxPointsText;
    Font font;

    void initWindow();
    void initFonts();
    void initText();
    void initButton();
public:
    RenderWindow* window;
    Interface();
    ~Interface();
    const bool isButtonPressed() const;
    const bool running() const;
    void pollEvents();
    const bool update();
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
    int maxPoints = 10;

    void variables();
    void initWindow();
    void initFonts();
    void initText();
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
    void updateMaxPoints();
    void update();

    void renderGui(RenderTarget* target);
    void render();
};

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

void GameOver::initWindow()
{
    this->texture.loadFromFile("game_over.png");
    this->sprajt.setTexture(texture);
    this->videoMode = VideoMode(1920.f, 1080.f);
    this->window = new RenderWindow(this->videoMode, "Agario", Style::Close | Style::Titlebar);
    this->window->clear(Color::White);
    this->window->setFramerateLimit(60);
}

void GameOver::initButton()
{
    this->buttonYes = Button(Vector2f(125, 60), Color::Transparent, Vector2f(800, 750));
    this->buttonNo = Button(Vector2f(125, 60), Color::Transparent, Vector2f(1000, 750));
}

GameOver::GameOver()
{
    this->initWindow();
    this->initButton();
}

GameOver::~GameOver()
{
    delete this->window;
}

const int GameOver::buttonPressed() const
{
    int choice = 0;
    if(this->buttonYes.isButtonPressed(window)){
        choice = 1;
    }
    else if(this->buttonNo.isButtonPressed(window)){
        choice = 2;
    }
    return choice;
}

void GameOver::render()
{
    this->window->clear(Color::White);
    this->window->draw(sprajt);
    this->window->draw(buttonYes.getButton());
    this->window->draw(buttonNo.getButton());
    this->window->display();
}

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
    else if(Keyboard::isKeyPressed(Keyboard::P)){
        this->setMass(0);
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

void StaticPoints::makeShape(const View& view, IntRect rect)
{
    Color color;
    switch (this->type)
    {
    case FOOD:
        color = Color::Blue;
        this->shape.setRadius(5);
        break;
    case SPIKES:
        color = Color::Red;
        this->shape.setRadius(30);
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

void Interface::initWindow()
{
    this->texture.loadFromFile("tlo.png");
    this->sprajt.setTexture(texture);
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

void Interface::initButton()
{
    this->button = Button(Vector2f(125, 60), Color::Cyan, Vector2f(560, 500));
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

    this->buttonText.setFont(this->font);
    this->buttonText.setFillColor(Color::Black);
    this->buttonText.setCharacterSize(25);
    this->buttonText.setPosition(Vector2f(590,515));
    this->buttonText.setString("Graj!");

    this->maxPointsText.setFont(this->font);
    this->maxPointsText.setFillColor(Color::Black);
    this->maxPointsText.setCharacterSize(25);
    this->maxPointsText.setPosition(Vector2f(380,425));
    int allMaxPoints = 0;
    ifstream Plik("./maxPoints.txt");
    Plik >> allMaxPoints;
    Plik.close();
    auto s = to_string(allMaxPoints);
    this->maxPointsText.setString("Twoj najlepszy dotychczasowy wynik to: " + s);
}

Interface::Interface()
{
    this->initWindow();
    this->initFonts();
    this->initText();
    this->initButton();
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
                break;
            }
        }
        break;
    }
}

const bool Interface::update()
{
    this->pollEvents();
    return this->button.isButtonPressed(this->window);
}

void Interface::renderGui(RenderTarget* target)
{
    target->draw(this->guiText);
    target->draw(this->standardText);
    target->draw(this->maxPointsText);
    target->draw(this->buttonText);
}

void Interface::render()
{
    this->window->clear(Color::White);
    this->window->draw(sprajt);
    this->window->draw(this->button.getButton());
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
    this->totalPoints = this->player.getMass();
}

void Game::spawnStaticPoints()
{
    if(this->spawnTimer < this->spawnTimerMax){
        this->spawnTimer += 1.f;
    }
    else{
        if(this->staticPoints.size() < this->maxStaticPoints){
            IntRect rect(this->player.getPlayerPostion().x, this->player.getPlayerPostion().y,
            this->player.getShape().getGlobalBounds().width,this->player.getShape().getGlobalBounds().height);
            this->staticPoints.push_back(StaticPoints(this->window->getView(), this->randPointType(), rect));
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
    view.setCenter(this->player.getPlayerPostion()+Vector2f(this->player.getMass(),this->player.getMass()));
    this->window->setView(view);
}

void Game::updateCollision()
{
    for(size_t i = 0; i < this->staticPoints.size(); i++){
        if(this->player.getShape().getGlobalBounds().intersects(this->staticPoints[i].getShape().getGlobalBounds())){
            switch(this->staticPoints[i].getType())
            {
                case StaticPointsTypes::FOOD:
                    this->player.grow(this->staticPoints[i].getMass());
                    break;
                case StaticPointsTypes::SPIKES:
                    if(this->player.getMass() > this->staticPoints[i].getMass() * 1.1){
                        //this->player.splitBySpike();
                        continue;
                    }
            }
            this->staticPoints.erase(this->staticPoints.begin() + i);
        }
    }
}

void Game::updateGui()
{
    stringstream ss;
    int mass = this->player.getMass();
    if(mass > maxPoints){
        maxPoints = mass;
    }
    ss << " - Points: " << mass << "\n";
    Vector2f playerPos = this->player.getPlayerPostion() + Vector2f(mass, mass);
    this->guiText.setPosition(playerPos + Vector2f(-960, -540));
    this->guiText.setString(ss.str());
}

void Game::updateMaxPoints()
{
    int allMaxPoints = 0;
    ifstream Plik("./maxPoints.txt");
    Plik >> allMaxPoints;
    Plik.close();
    if(maxPoints > allMaxPoints){
        ofstream Plik("./maxPoints.txt");
        Plik << maxPoints;
        Plik.close();
    }
}

void Game::update()
{
    this->pollEvents();
    if(this->player.getMass() <= 0){
        this->endGame = true;
        this->updateMaxPoints();
    }
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

    this->player.render(this->window);

    for(auto i : this->staticPoints){

        i.render(*this->window);
    }

    this->renderGui(this->window);

    if(this->endGame == true){
        this->window->close();
    }

    this->window->display();
}

int main()
{
    srand(static_cast<unsigned>(time(0)));
    int choice = 0;
    while(true)
    {
        // Interface interface;
        // bool change = false;
        // while(interface.running() && change == false)
        // {
        //     change = interface.update();
        //     interface.render();
        // }
        // interface.~Interface();
        Game game;
        cout<<game.running()<<endl;
        while(game.running())
        {
            game.update();
            game.render();
        }
        game.~Game();
        GameOver gameOver;
        while(choice == 0)
        {
            choice = gameOver.buttonPressed();
            gameOver.render();
        }
        if(choice == 1){
            choice = 0;
        }
        else if(choice == 2){
            gameOver.~GameOver();
            break;
        }
        gameOver.~GameOver();
    }
    return 0;
}
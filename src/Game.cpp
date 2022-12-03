#include "Game.h"

void Game::variables()
{
    this->endGame = false;
    this->spawnTimerMax = 10.f;
    this->spawnTimer = this->spawnTimerMax;
    this->maxStaticPoints = 10;
}

void Game::initWindow()
{
    this->videoMode = VideoMode(800, 600);
    this->window = new RenderWindow(this->videoMode, "Agario", Style::Close | Style::Titlebar);
    this->window->clear(Color::White);
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

void Game::spawnStaticPoints()
{
    if(this->spawnTimer < this->spawnTimerMax){
        this->spawnTimer += 1.f;
    }
    else{
        if(this->staticPoints.size() < this->maxStaticPoints){
            this->staticPoints.push_back(StaticPoints(*this->window, this->randPointType()));
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
    this->player.setPosition(this->window);
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

    this->guiText.setString(ss.str());
}

void Game::update()
{
    this->pollEvents();
    if(this->endGame == false){
        this->spawnStaticPoints();
        this->updatePlayer();
        this->updateGui();
    }
}

void Game::renderGui(RenderTarget* target)
{
    target->draw(this->guiText);
}

void Game::render()
{
    this->window->clear(); //Maybe Color::White

    this->player.render(this->window);

    for(auto i : this->staticPoints){
        i.render(*this->window);
    }

    this->renderGui(this->window);

    if(this->endGame == true){
        this->window->draw(this->endGameText);
    }

    this->window->display();
}
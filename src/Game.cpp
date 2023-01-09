#include "Game.h"

void Game::variables()
{
    this->endGame = false;
    this->maxStaticPoints = 1000;
    this->totalPoints = 10;
    Player player;
    this->players.push_back(player);
}

void Game::initWindow()
{
    View view(Vector2f(920, 540), Vector2f(9600, 5400));
    view.zoom(0.2);
    view.setCenter(this->players[0].getPlayerPostion());
    this->videoMode = VideoMode(1920, 1080);
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
}

void Game::zoomOut()
{
    View view = this->window->getDefaultView();
    view.zoom(1+ log(this->totalPoints) / log(4) / 10);
    this->window->setView(view);
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
    this->totalPoints = 0;
    for(auto& it : this->players)
    {
        this->totalPoints += it.getMass();
    }
}

void Game::spawnStaticPoints()
{
    if(this->staticPoints.size() < this->maxStaticPoints){
        this->staticPoints.push_back(StaticPoints(this->randPointType(), this->players));
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
    View view = this->window->getView();
    Vector2f viewCenter;
    for(auto& it : this->players)
    {
        it.setPosition(this->players);
        viewCenter += it.getPlayerPostion();
        viewCenter += Vector2f(log(it.getMass())/log(1.05),log(it.getMass())/log(1.05));
    }
    viewCenter.x = viewCenter.x / this->players.size();
    viewCenter.y = viewCenter.y / this->players.size();
    view.setCenter(viewCenter);
    this->window->setView(view);
}

void Game::updateCollision()
{
    for(size_t i = 0; i < this->staticPoints.size(); ++i){
        for(auto& it : this->players)
        {
            if(it.getShape().getGlobalBounds().intersects(this->staticPoints[i].getShape().getGlobalBounds())){
            switch(this->staticPoints[i].getType())
            {
                case StaticPointsTypes::FOOD:
                    it.grow(this->staticPoints[i].getMass());
                    break;
                case StaticPointsTypes::SPIKES:
                    if(it.getMass() > this->staticPoints[i].getMass() * 1.1){
                        it.grow(this->staticPoints[i].getMass());
                        it.splitBySpike(this->players);
                    }
            }
            this->staticPoints.erase(this->staticPoints.begin() + i);
            }
        }
    }
}

void Game::updateGui()
{
    stringstream ss;
    if(this->totalPoints > maxPoints){
        maxPoints = this->totalPoints;
    }
    ss << " - Points: " << this->totalPoints << "\n";
    Vector2f viewCenter;
    for(auto& it : this->players)
    {
        viewCenter += it.getPlayerPostion();
        viewCenter += Vector2f(log(it.getMass())/log(1.05),log(it.getMass())/log(1.05));
    }
    viewCenter.x = viewCenter.x / this->players.size();
    viewCenter.y = viewCenter.y / this->players.size();
    View view = window->getView();
    Vector2f size = view.getSize();
    viewCenter += Vector2f(-size.x/2, -size.y/2);
    this->guiText.setPosition(viewCenter);
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
    if(!this->endGame){
        this->zoomOut();
        this->calculateTotalPoints();
        this->spawnStaticPoints();
        this->updatePlayer();
        this->updateCollision();
        this->updateGui();
    }
    if(this->totalPoints <= 0){
        this->endGame = true;
        this->updateMaxPoints();
    }
}

void Game::renderGui(RenderTarget* target)
{
    target->draw(this->guiText);
}

void Game::render()
{
    this->window->clear(Color::White);

    for(auto& it : players){
        it.render(*this->window);
    }

    for(auto& it : this->staticPoints){

        it.render(*this->window);
    }

    this->renderGui(this->window);

    if(this->endGame){
        this->window->close();
    }
    this->window->display();
}
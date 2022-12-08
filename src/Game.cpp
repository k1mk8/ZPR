#include "Game.h"

void Game::variables()
{
    this->endGame = false;
    this->spawnTimerMax = 2.f;
    this->spawnTimer = this->spawnTimerMax;
    this->maxStaticPoints = 1000;
    this->totalPoints = 10;
    Player player;
    this->players.push_back(player);

}

void Game::initWindow()
{
    View view(Vector2f(920.f, 540.f), Vector2f(19200.f, 10800.f));
    view.zoom(0.1f);
    view.setCenter(this->players[0].getPlayerPostion());
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
    Vector2f playerPos = this->players[0].getPlayerPostion();
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
    this->totalPoints = 0;
    for(auto& it : this->players)
    {
        this->totalPoints += it.getMass();
    }
}

void Game::spawnStaticPoints()
{
    if(this->spawnTimer < this->spawnTimerMax){
        this->spawnTimer += 1.f;
    }
    else{
        if(this->staticPoints.size() < this->maxStaticPoints){
            this->staticPoints.push_back(StaticPoints(this->window->getView(), this->randPointType(), this->players));
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
    View view = this->window->getView();
    Vector2f viewCenter;
    for(auto& it : this->players)
    {
        it.setPosition(&this->window->getView());
        viewCenter +=  it.getPlayerPostion();
        viewCenter += Vector2f(it.getMass(),it.getMass());
    }
    viewCenter.x = viewCenter.x / this->players.size();
    viewCenter.y = viewCenter.y / this->players.size();
    view.setCenter(viewCenter);
    this->window->setView(view);
}

void Game::updateCollision()
{
    for(size_t i = 0; i < this->staticPoints.size(); i++){
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
                        //this->player.splitBySpike();
                        continue;
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
        viewCenter += Vector2f(it.getMass(),it.getMass());
    }
    viewCenter.x = viewCenter.x / this->players.size();
    viewCenter.y = viewCenter.y / this->players.size();
    viewCenter += Vector2f(-960, -540);
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
    if(this->endGame == false){
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

    cout<<players.size()<<endl;
    for(auto& it : players){
        cout<<it.getMass()<<endl;
        it.render(*this->window);
    }

    for(auto& it : this->staticPoints){

        it.render(*this->window);
    }

    this->renderGui(this->window);

    if(this->endGame == true){
        this->window->close();
    }

    this->window->display();
}
#include "Game.h"

void Game::variables(const int speed)
{
    /// @brief ustawia zmienne klasy
    this->endGame = false;
    this->maxStaticPoints = 1000;
    this->totalPoints = 10;
    Player player(0, 0, 10, speed);
    this->players.push_back(player);
}

void Game::initWindow()
{
    /// @brief inicjuje okno gry
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
    /// @brief ustawia czcionkę tekstu
    if(!this->font.loadFromFile("fonts/MilkyHoney.ttf")){
        cout << " COULD NOT LOAD MilkyHoney.ttf" << "\n";
    }
}

void Game::initText()
{
    /// @brief iniciuje teksty w grze
    this->guiText.setFont(this->font);
    this->guiText.setFillColor(Color::Black);
    this->guiText.setCharacterSize(32);
}

void Game::zoomOut()
{
    /// @brief oddala obraz aby gracz mieścił się w oknie
    View view = this->window->getDefaultView();
    view.zoom(1+ log(this->totalPoints) / log(4) / 10);
    this->window->setView(view);
}

Game::Game(const int speed)
{
    /// @brief konstruktor klasy tworzący jej obiekt
    this->variables(speed);
    this->initWindow();
    this->initFonts();
    this->initText();
}

Game::~Game()
{
    /// @brief destruktor domyślny
    delete this->window;
}

const bool& Game::getEndGame() const
{
    /// @brief getter końca gry
    /// @return prawda lub fałsz czy koniec gry 
    return this->endGame;
}

bool Game::running()
{
    /// @brief funkcja sprawdzająca czy okno jest otwarte
    /// @return prawda lub fałsz, czy okno jest otwarte
    return this->window->isOpen();
}

void Game::pollEvents()
{
    /// @brief funkcja sprawdzająca czy okno ma być zamknięte
    while(this->window->pollEvent(this->sfmlEvent))
    {
        if (this->sfmlEvent.type == Event::Closed)
        {
            this->window->close();
            break;
        }
        else if(this->sfmlEvent.type == Event::KeyPressed)
        {
            if(this->sfmlEvent.key.code == Keyboard::Escape)
            {
                this->window->close();
                break;
            }
        }
        break;
    }
}

const int & Game::getTotalPoints() const
{
    /// @brief getter sumarycznej liczby punktów
    /// @return sumaryczną ilość punktów
    return this->totalPoints;
}

void Game::calculateTotalPoints()
{
    /// @brief oblicza łączną liczbę punktów gracza
    this->totalPoints = 0;
    for(auto& it : this->players)
    {
        this->totalPoints += it.getMass();
    }
}

void Game::spawnStaticPoints()
{
    /// @brief tworzy obiekty statyczne na mapie
    if((int)this->staticPoints.size() < this->maxStaticPoints){
        this->staticPoints.push_back(StaticPoints(this->randPointType(), this->players));
    }
}

int Game::randPointType()
{
    /// @brief generuje losowy punkt 
    /// @return typ punktu statycznego
    int type = StaticPointsTypes::FOOD;
    int value = rand() % 100 + 1;
    if(value > 98){
        type = StaticPointsTypes::SPIKES;
    }

    return type;
}

void Game::updatePlayer()
{
    /// @brief funkcja uaktualniająca informację o graczu
    View view = this->window->getView();
    Vector2f viewCenter;
    for(auto& it : this->players)
    {
        it.setPosition(this->players, *this->window);
        bool shooting = false;
        while(Keyboard::isKeyPressed(Keyboard::E)){
            shooting = true;
        }
        if(shooting && it.getMass() > 20){ // sprawdza czy gracz strzelił
            int type = StaticPointsTypes::FOOD;
            float mouseX = Mouse::getPosition(*this->window).x;
            float mouseY = Mouse::getPosition(*this->window).y;
            mouseX -= this->window->getSize().x / 2;
            mouseY -= this->window->getSize().y / 2;
            mouseX += it.getPlayerPostion().x;
            mouseY += it.getPlayerPostion().y;
            this->staticPoints.push_back(StaticPoints(type, mouseX, mouseY));
            it.loseMass();
        }
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
    /// @brief funkcja sprawdzająca kolizję na mapie
    for(size_t i = 0; i < this->staticPoints.size(); ++i){ // iteracja po wszystkich punktach na mapie
        for(auto& it : this->players) // iteracja po wszystkich graczach
        {
            if(it.getShape().getGlobalBounds().intersects(this->staticPoints[i].getShape().getGlobalBounds()))
            { // sprawdzenie czy punkty się nie przecinają
                switch(this->staticPoints[i].getType())
                {
                    case StaticPointsTypes::FOOD: // jeśli jedzenie zwiększ mase
                        it.grow(this->staticPoints[i].getMass());
                        this->staticPoints.erase(this->staticPoints.begin() + i); // usuń punkt z mapy
                        break;
                    case StaticPointsTypes::SPIKES: // jeśli spike'a porównaj mase
                        if(it.getMass() > this->staticPoints[i].getMass() * 1.1)
                        {
                            it.grow(this->staticPoints[i].getMass());
                            it.splitBySpike(this->players);
                            this->staticPoints.erase(this->staticPoints.begin() + i); // usuń punkt z mapy
                        }
                }
            }
        }
    }
}

void Game::updateGui()
{
    /// @brief aktualizowanie informacji interfejsu
    stringstream ss;
    if(this->totalPoints > maxPoints){
        maxPoints = this->totalPoints;
    }
    ss << " - Points: " << this->totalPoints << "\n"; // uaktualnienie liczby punktów
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
    /// @brief funkcja po zakończeniu gry zapisuje maksymalną ilość punktów do pliku
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
    /// @brief funkcja uaktualniająca wydarzenia na mapie
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
    /// @brief funkcja generująca GUI dla okna
    /// @param target miejsce renderu obiektu
    target->draw(this->guiText);
}

void Game::render()
{
    /// @brief funkcja renderująca i wyświetlająca okno oraz obiekty na nim
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
#include "Game.h"

void Game::variables(const int& speed)
{
    /// @brief ustawia zmienne klasy
    this->endGame = false;
    this->maxStaticPoints = 1000;
    this->totalPoints = 10;
    Player player(0, 0, 512, speed);
    this->players.push_back(player);
}

void Game::initWindow()
{
    /// @brief inicjuje okno gry
    srand( time( NULL ) );
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
    this->table.setFont(this->font);
    this->table.setFillColor(Color::Black);
    this->table.setCharacterSize(32);
}

void Game::initBots(const float& speed)
{
    /// @brief iniciuje boty w grze
    if(this->bots.size() < 10)
    {
        for(int i = (int)this->bots.size(); i < this->maxBots; ++i)
        {
            Bot bot(rand()%8000 - 4000, rand()%5000 - 2500, 10, speed);
            this->bots.push_back(bot);
        }
    }
}

void Game::zoomOut()
{
    /// @brief oddala obraz aby gracz mieścił się w oknie
    View view = this->window->getDefaultView();
    view.zoom(1+ log(this->totalPoints) / log(4) / 10);
    this->window->setView(view);
}

Game::Game(const int& speed)
{
    /// @brief konstruktor klasy tworzący jej obiekt
    this->variables(speed);
    this->initWindow();
    this->initFonts();
    this->initText();
    this->initBots(speed);
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
        if(this->sfmlEvent.key.code == Keyboard::Escape)
        {
            this->window->close();
            break;
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
    bool shooting = false;
    while(Keyboard::isKeyPressed(Keyboard::E)){
        shooting = true;
    }
    for(auto& it : this->players)
    {
        it.setPosition(this->players, *this->window);
        if(shooting && it.getMass() > 20){ // sprawdza czy gracz strzelił
            int type = StaticPointsTypes::FOOD;
            auto& window = *this->window;
            float mouseX = Mouse::getPosition(window).x;
            float mouseY = Mouse::getPosition(window).y;
            mouseX -= window.getSize().x / 2;
            mouseY -= window.getSize().y / 2;
            float direction = atan2(-mouseY, mouseX);
            this->staticPoints.push_back(StaticPoints(type, it.getRadius() + it.getPlayerPostion().x + 1.8 * it.getRadius() * cos(direction),
                 it.getRadius() + it.getPlayerPostion().y - 1.8 * it.getRadius() * sin(direction), it.getStartingSpeed(), direction));
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

template<typename T>
void Game::updateCollision(vector<T>& participants, bool isBot)
{
    /// @brief funkcja sprawdzająca kolizję na mapie
    for(size_t i = 0; i < this->staticPoints.size(); ++i){ // iteracja po wszystkich punktach na mapie
        for(auto& it : participants) // iteracja po wszystkich graczach
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
                            this->staticPoints.erase(this->staticPoints.begin() + i); // usuń punkt z mapy
                            if(isBot == false)
                                it.splitBySpike(participants);
                            break;
                        }
                }
            }
        }
    }
    if(isBot == true)
        for(auto& it : participants)
            for(size_t i = 0; i < this->players.size(); ++i){
            {
                if(it.getShape().getGlobalBounds().intersects(this->players[i].getShape().getGlobalBounds()))
                { // sprawdzenie czy punkty się nie przecinają
                    if(it.getMass() > this->players[i].getMass() * 1.1)
                    {
                        it.grow(this->players[i].getMass());
                        this->players.erase(this->players.begin() + i); // usuń punkt z mapy
                        break;
                    }
                }
            }
        }
    for(auto& it : participants)
        for(size_t i = 0; i < this->bots.size(); ++i){
        {
            if(it.getShape().getGlobalBounds().intersects(this->bots[i].getShape().getGlobalBounds()))
            { // sprawdzenie czy punkty się nie przecinają
                if(it.getMass() > this->bots[i].getMass() * 1.1)
                {
                    it.grow(this->bots[i].getMass());
                    this->bots.erase(this->bots.begin() + i); // usuń punkt z mapy
                    break;
                }
            }
        }
    }
}

void Game::updateGui()
{
    /// @brief aktualizowanie informacji interfejsu
    stringstream ss, ss2;
    if(this->totalPoints > maxPoints){
        maxPoints = this->totalPoints;
    }
    ss << " - Points: " << this->totalPoints << "\n"; // uaktualnienie liczby punktów
    Vector2f viewCenter;
    ss2 << "TABLICA WYNIKOW\n";
    int playerMass = 0;
    for(auto& it: players)
    {
        viewCenter += it.getPlayerPostion();
        viewCenter += Vector2f(log(it.getMass())/log(1.05), log(it.getMass())/log(1.05));
        playerMass += it.getMass();
    }
    vector<int> bestFive;
    bestFive.push_back(-playerMass);
    for(auto& it: bots)
        bestFive.push_back(-it.getMass());
    sort(bestFive.begin(), bestFive.end());
    for(int i = 0; i < min(5, (int)bestFive.size()); ++i)
        ss2 << -bestFive[i] << "\n";
    viewCenter.x = viewCenter.x / this->players.size();
    viewCenter.y = viewCenter.y / this->players.size();
    View view = window->getView();
    Vector2f size = view.getSize();
    Vector2f tablePosition = viewCenter;
    tablePosition += Vector2f(size.x/2 - 300, -size.y/2);
    viewCenter += Vector2f(-size.x/2, -size.y/2);
    this->guiText.setPosition(viewCenter);
    this->guiText.setString(ss.str());
    this->table.setPosition(tablePosition);
    this->table.setString(ss2.str());
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

void Game::updateBot()
{
    for(auto& it: this->bots)
    {
        it.moveBot(this->bots, this->players, this->staticPoints);
    }
}

void Game::update()
{
    /// @brief funkcja uaktualniająca wydarzenia na mapie
    this->pollEvents();
    if(!this->endGame){
        this->zoomOut();
        this->spawnStaticPoints();
        this->updatePlayer();
        this->updateBot();
        this->updateCollision(this->players, false);
        this->updateCollision(this->bots, true);
        this->updateGui();
        this->initBots(this->players[0].getStartingSpeed());
        this->calculateStaticPoints();
    }
    this->calculateTotalPoints();
    if(this->totalPoints <= 0){
        this->endGame = true;
        this->updateMaxPoints();
    }
}

void Game::calculateStaticPoints()
{
    for(auto& it: this->staticPoints)
        it.calculateSpeed();
}

void Game::renderGui(RenderTarget* target)
{
    /// @brief funkcja generująca GUI dla okna
    /// @param target miejsce renderu obiektu
    target->draw(this->guiText);
    target->draw(this->table);
}

void Game::render()
{
    /// @brief funkcja renderująca i wyświetlająca okno oraz obiekty na nim
    this->window->clear(Color::White);

    for(auto& it : this->players){
        it.render(*this->window);
    }

    for(auto& it : this->bots){
        it.render(*this->window);
    }

    for(auto& it : this->staticPoints){
        it.render(*this->window);
    }

    this->renderGui(this->window);

    if(this->endGame){
        this->window->close();
        return;
    }
    this->window->display();
}
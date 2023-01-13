#include "Game.h"

using namespace std;
using namespace sf;

void Game::variables(const int& speed)
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

void Game::initText()
{
    /// @brief iniciuje teksty w grze
    setNewTextParams(this->guiText, Color::Black, 32);
    setNewTextParams(this->table, Color::Black, 32);
}

void Game::initBots(const float& speed)
{
    /// @brief iniciuje boty w grze
    if(this->bots.size() < 10)
        for(int i = (int)this->bots.size(); i < this->maxBots; ++i)
        {
            Bot bot(rand()%8000 - 4000, rand()%5000 - 2500, 10, speed);
            this->bots.push_back(bot);
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

const bool& Game::getEndGame() const
{
    /// @brief getter końca gry
    /// @return prawda lub fałsz czy koniec gry 
    return this->endGame;
}

const int & Game::getTotalPoints() const
{
    /// @brief getter sumarycznej liczby punktów
    /// @return sumaryczną ilość punktów
    return this->totalPoints;
}

int Game::calculateTotalPoints()
{
    /// @brief oblicza łączną liczbę punktów gracza
    this->totalPoints = 0;
    for(auto& it : this->players)
        this->totalPoints += it.getMass();
    
    if(this->totalPoints > this->maxPoints)
        this->maxPoints = this->totalPoints;

    return this->totalPoints;
}

void Game::spawnStaticPoints()
{
    /// @brief tworzy obiekty statyczne na mapie
    if((int)this->staticPoints.size() < this->maxStaticPoints)
        this->staticPoints.push_back(StaticPoints(this->randPointType(), this->players));
}

int Game::randPointType()
{
    /// @brief generuje losowy punkt 
    /// @return typ punktu statycznego
    int type = StaticPointsTypes::FOOD;
    int value = rand() % 100 + 1;
    if(value > 98)
        type = StaticPointsTypes::SPIKES;
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

template<typename T, typename U>
void Game::updateCollisionForObject(T& participant, vector<U>& objects, vector<T>& participants)
{
    int i = 0;
    for(auto& it : objects) // iteracja po wszystkich graczach
    {
        if(it.getShape().getGlobalBounds().intersects(participant.getShape().getGlobalBounds()))
        { // sprawdzenie czy punkty się nie przecinają
            switch(it.getType())
            {
                case StaticPointsTypes::FOOD: // jeśli jedzenie zwiększ mase
                    participant.grow(it.getMass());
                    objects.erase(objects.begin() + i); // usuń punkt z mapy
                    break;
                case StaticPointsTypes::SPIKES: // jeśli spike'a porównaj mase
                    if(participant.getMass() > it.getMass() * 1.1)
                    {
                        participant.grow(it.getMass());
                        objects.erase(objects.begin() + i); // usuń punkt z mapy
                        if(participant.getType() == 3)
                            participant.splitBySpike(participants);
                    }
                    break;
                default:
                    if(participant.getMass() > it.getMass() * 1.1)
                    {
                        participant.grow(it.getMass());
                        objects.erase(objects.begin() + i); // usuń punkt z mapy
                    }
                    break;
            }
        }
        ++i;
    }
}

void Game::updateCollision()
{
    /// @brief funkcja sprawdzająca kolizję na mapie
    for(auto& it:players)
    {
        this->updateCollisionForObject(it, this->bots, this->players);
        this->updateCollisionForObject(it, this->staticPoints, this->players);
    }
    for(auto& it:bots)
    {
        this->updateCollisionForObject(it, this->players, this->bots);
        this->updateCollisionForObject(it, this->staticPoints, this->bots);
    }
}

void Game::updateTable(stringstream& ss, stringstream& ss2, Vector2f& viewCenter)
{
    ss << " - Points: " << this->totalPoints << "\n"; // uaktualnienie liczby punktów
    ss2 << "TABLICA WYNIKOW\n";

    vector<int> bestFive;
    for(auto& it: bots)
        bestFive.push_back(-it.getMass());
    for(auto& it: players)
    {
        viewCenter += it.getPlayerPostion();
        viewCenter += Vector2f(it.getRadius()+30, it.getRadius()+30);
    }
    bestFive.push_back(-this->calculateTotalPoints());
    sort(bestFive.begin(), bestFive.end());
    
    for(int i = 0; i < min(5, (int)bestFive.size()); ++i)
        ss2 << -bestFive[i] << "\n";
}

void Game::updateGui()
{
    /// @brief aktualizowanie informacji interfejsu
    stringstream ss, ss2;
    Vector2f viewCenter;
    this->updateTable(ss, ss2 , viewCenter);
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
        it.moveBot(this->bots, this->players, this->staticPoints);
}

int Game::update()
{
    /// @brief funkcja uaktualniająca wydarzenia na mapie
    this->pollEvents();
    if(!this->endGame){
        this->zoomOut();
        this->spawnStaticPoints();
        this->updatePlayer();
        this->updateBot();
        this->updateCollision();
        this->updateGui();
        this->initBots(this->players[0].getStartingSpeed());
        this->calculateStaticPoints();
    }
    if(this->calculateTotalPoints() <= 0 || this->endGame == true){
        this->endGame = true;
        this->updateMaxPoints();
    }
    return 0;
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

    for(auto& it : this->players)
        it.render(*this->window);

    for(auto& it : this->bots)
        it.render(*this->window);

    for(auto& it : this->staticPoints)
        it.render(*this->window);

    this->renderGui(this->window);

    if(this->endGame){
        this->window->close();
        return;
    }

    this->window->display();
}
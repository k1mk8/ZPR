#include "Game.h"

using namespace std;
using namespace sf;

void Game::variables(const int& speed)
{
    /// @brief ustawia zmienne klasy
    this->end_game_ = false;
    this->max_static_points_ = 1000;
    this->total_points_ = 10;
    Player player(0, 0, 10, speed);
    this->players_.push_back(player);
}

void Game::initWindow()
{
    /// @brief inicjuje okno gry
    srand( time( NULL ) );
    View view(Vector2f(920, 540), Vector2f(9600, 5400));
    view.zoom(0.2);
    view.setCenter(this->players_[0].getPlayerPostion());
    this->video_mode_ = VideoMode(1920, 1080);
    this->window_ = new RenderWindow(this->video_mode_, "Agario", Style::Close | Style::Titlebar);
    this->window_->clear(Color::White);
    this->window_->setFramerateLimit(60);
    this->window_->setView(view);
}

void Game::initText()
{
    /// @brief iniciuje teksty w grze
    setNewTextParams(this->gui_text_, Color::Black, 32);
    setNewTextParams(this->table_, Color::Black, 32);
}

void Game::initBots(const float& speed)
{
    /// @brief iniciuje boty w grze
    if(this->bots_.size() < 10)
        for(int i = (int)this->bots_.size(); i < this->max_bots_; ++i)
        {
            Bot bot(rand()%8000 - 4000, rand()%5000 - 2500, 10, speed);
            this->bots_.push_back(bot);
        }
}

void Game::zoomOut()
{
    /// @brief oddala obraz aby gracz mieścił się w oknie
    View view = this->window_->getDefaultView();
    view.zoom(1+ log(this->total_points_) / log(4) / 10);
    this->window_->setView(view);
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
    return this->end_game_;
}

const int & Game::getTotalPoints() const
{
    /// @brief getter sumarycznej liczby punktów
    /// @return sumaryczną ilość punktów
    return this->total_points_;
}

int Game::calculateTotalPoints()
{
    /// @brief oblicza łączną liczbę punktów gracza
    this->total_points_ = 0;
    for(auto& it : this->players_)
        this->total_points_ += it.getMass();
    
    if(this->total_points_ > this->max_points_)
        this->max_points_ = this->total_points_;

    return this->total_points_;
}

void Game::spawnStaticPoints()
{
    /// @brief tworzy obiekty statyczne na mapie
    if((int)this->static_points_.size() < this->max_static_points_)
        this->static_points_.push_back(StaticPoints(this->randPointType(), this->players_));
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
    View view = this->window_->getView();
    Vector2f viewCenter;
    bool shooting = false;
    while(Keyboard::isKeyPressed(Keyboard::E)){ // sprawdzamy przyciśnięcie przycisku E na klawiaturze
        shooting = true;
    }
    for(auto& it : this->players_)
    {
        it.setPosition(this->players_, *this->window_);
        if(shooting && it.getMass() > 20){ // sprawdza czy gracz strzelił i ma masę większą niż 20
            int type = StaticPointsTypes::FOOD;
            auto& window_ = *this->window_;
            float mouseX = Mouse::getPosition(window_).x;
            float mouseY = Mouse::getPosition(window_).y;
            mouseX -= window_.getSize().x / 2;
            mouseY -= window_.getSize().y / 2;
            float direction = atan2(-mouseY, mouseX); // oblicza kierunek strzału
            this->static_points_.push_back(StaticPoints(type, 
                it.getRadius() + it.getPlayerPostion().x + 1.8 * it.getRadius() * cos(direction),
                it.getRadius() + it.getPlayerPostion().y - 1.8 * it.getRadius() * sin(direction),
                it.getStartingSpeed(), direction)); // tworzy nowy obiekt statyczny wystrzliwany przez gracza
            it.loseMass();
        }
        viewCenter += it.getPlayerPostion();
        viewCenter += Vector2f(log(it.getMass())/log(1.05),log(it.getMass())/log(1.05));
    }
    viewCenter.x = viewCenter.x / this->players_.size();
    viewCenter.y = viewCenter.y / this->players_.size();
    view.setCenter(viewCenter);
    this->window_->setView(view);
}

template<typename T, typename U>
void Game::updateCollisionForObject(T& participant, vector<U>& objects, vector<T>& participants)
{
    /// @brief funkcja odpowiadająca za kolizje poszczególnych obiektów
    /// @tparam T template dla uczestnika, na którym sprawdzane są kolizje
    /// @tparam U template dla obiektów, z którymi może się zderzyć uczestnik
    /// @param participant uczestnik kolizji
    /// @param objects obiekty do kolizji
    /// @param participants wektor wszystkich danych uczestników
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
                        if(participant.getType() == 3) // jeśli obiekt jest graczem to rozbij
                            participant.splitBySpike(participants);
                    }
                    break;
                default:
                    if(participant.getMass() > it.getMass() * 1.1) // jeśli jest to gracz lub bot
                    {
                        participant.grow(it.getMass()); // uczestnik rośnie
                        objects.erase(objects.begin() + i); // mniejszy obiekt rośnie
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
    for(auto& it:players_)
    {
        this->updateCollisionForObject(it, this->bots_, this->players_);
        this->updateCollisionForObject(it, this->static_points_, this->players_);
    }
    for(auto& it:bots_)
    {
        this->updateCollisionForObject(it, this->players_, this->bots_);
        this->updateCollisionForObject(it, this->static_points_, this->bots_);
    }
}

void Game::updateTable(stringstream& ss, stringstream& ss2, Vector2f& viewCenter)
{
    /// @brief funkcja uaktualniająca tablice wyników
    /// @param ss napisz 1
    /// @param ss2 napis 2
    /// @param viewCenter środek ekranu
    ss << " - Points: " << this->total_points_ << "\n"; // uaktualnienie liczby punktów
    ss2 << "TABLICA WYNIKOW\n";

    vector<int> bestFive;
    for(auto& it: bots_)
        bestFive.push_back(-it.getMass());
    for(auto& it: players_)
    {
        viewCenter += it.getPlayerPostion();
        viewCenter += Vector2f(it.getRadius()+30, it.getRadius()+30); // obliczanie środka ekranu
    }
    bestFive.push_back(-this->calculateTotalPoints());
    sort(bestFive.begin(), bestFive.end()); // obliczamy 5 najlepszy zawodników
    
    for(int i = 0; i < min(5, (int)bestFive.size()); ++i)
        ss2 << -bestFive[i] << "\n";
}

void Game::updateGui()
{
    /// @brief aktualizowanie informacji interfejsu
    stringstream ss, ss2;
    Vector2f viewCenter;
    this->updateTable(ss, ss2 , viewCenter);
    viewCenter.x = viewCenter.x / this->players_.size();
    viewCenter.y = viewCenter.y / this->players_.size();
    View view = window_->getView();
    Vector2f size = view.getSize();
    Vector2f tablePosition = viewCenter;
    tablePosition += Vector2f(size.x/2 - 300, -size.y/2);
    viewCenter += Vector2f(-size.x/2, -size.y/2);
    this->gui_text_.setPosition(viewCenter);
    this->gui_text_.setString(ss.str());
    this->table_.setPosition(tablePosition);
    this->table_.setString(ss2.str());
}

void Game::updateMaxPoints()
{
    /// @brief funkcja po zakończeniu gry zapisuje maksymalną ilość punktów do pliku
    int allMaxPoints = 0;
    ifstream Plik("./max_points_.txt");
    Plik >> allMaxPoints;
    Plik.close();
    if(max_points_ > allMaxPoints){
        ofstream Plik("./max_points_.txt");
        Plik << max_points_;
        Plik.close();
    }
}

void Game::updateBot()
{
    /// @brief funkcja odpowiedzialna za aktualizacje ruchu botów
    for(auto& it: this->bots_)
        it.moveBot(this->bots_, this->players_, this->static_points_);
}

int Game::update()
{
    /// @brief funkcja uaktualniająca wydarzenia na mapie
    this->pollEvents();
    if(!this->end_game_){
        this->zoomOut();
        this->spawnStaticPoints();
        this->updatePlayer();
        this->updateBot();
        this->updateCollision();
        this->updateGui();
        this->initBots(this->players_[0].getStartingSpeed());
        this->calculateStaticPoints();
    }
    if(this->calculateTotalPoints() <= 0 || this->end_game_ == true){
        this->end_game_ = true;
        this->updateMaxPoints();
    }
    return 0;
}

void Game::calculateStaticPoints()
{
    /// @brief funkcja oblicza prędkość wystrzelonych punktów
    for(auto& it: this->static_points_)
        it.calculateSpeed();
}

void Game::renderGui(RenderTarget* target)
{
    /// @brief funkcja generująca GUI dla okna
    /// @param target miejsce renderu obiektu
    target->draw(this->gui_text_);
    target->draw(this->table_);
}

void Game::render()
{
    /// @brief funkcja renderująca i wyświetlająca okno oraz obiekty na nim
    this->window_->clear(Color::White);

    for(auto& it : this->players_)
        it.render(*this->window_);

    for(auto& it : this->bots_)
        it.render(*this->window_);

    for(auto& it : this->static_points_)
        it.render(*this->window_);

    this->renderGui(this->window_);

    if(this->end_game_){
        this->window_->close();
        return;
    }

    this->window_->display();
}
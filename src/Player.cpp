#include "Player.h"

using namespace std;
using namespace sf;

void Player::Variables(const int mass_, const int speed_)
{
    /// @brief ustawia zmienne klasy
    /// @param mass_ masa punktu
    /// @param speed_ prędkość punktu
    this->starting_speed_ = (float)speed_;
    this->mass_ = mass_;
    this->speed_ = this->starting_speed_ - (log(this->mass_) / log(4));
    this->shape_.setOutlineColor(Color::Cyan);
    this->shape_.setOutlineThickness(10);
}

void Player::makeShape()
{
    /// @brief tworzy obiekt
    this->shape_.setFillColor(Color::Green);
    this->shape_.setRadius(this->getRadius());
}

Player::Player(float x, float y, const int mass_, const int speed_)
{
    /// @brief konstruktor klasy tworzący jej obiekt
    /// @param x pozycja horyzontalna gracza
    /// @param y pozycja wertykalna gracza
    /// @param mass_ masa gracza
    this->shape_.setPosition(x,y);
    this->Variables(mass_, speed_);
    this->makeShape();
    this->setType(3);
}

Player::~Player()
{
    /// destruktor klasy
}

CircleShape & Player::getShape()
{
    /// @brief getter kształtu gracza
    /// @return kształt gracza
    return this->shape_;
}

const int & Player::getMass() const
{
    /// @brief getter masy gracza
    /// @return masa gracza
    return this->mass_;
}

float Player::getStartingSpeed()
{
    /// @brief getter prędkości gracza
    /// @return prędkość gracza
    return this->starting_speed_;
}

float Player::getRadius()
{
    /// @brief getter promienia gracza
    /// @return promień gracza
    return log(this->mass_)/log(1.05) - 30;
}

int Player::getType()
{
    /// @brief getter typu obiektu
    /// @return typ obiektu
    return this->type_;
}

const float & Player::getSpeed() const
{
    /// @brief getter prędkości gracza
    /// @return prędkość gracza
    return this->speed_;
}

const Vector2f & Player::getPlayerPostion() const
{
    /// @brief getter pozycji gracza na mapie
    /// @return pozycja
    return this->shape_.getPosition();
}

const clock_t & Player::getFreshSpawnedTime() const
{
    /// @brief getter czasu podziału
    /// @return splittime
    return this->fresh_spawned_time_;
}

void Player::setFreshSpawnedTime(clock_t fresh_spawned_time_)
{
    /// @brief getter czasu podziału
    /// @return splittime
    this->fresh_spawned_time_ = fresh_spawned_time_;
}

const clock_t & Player::getSplitTime() const
{
    /// @brief getter czasu podziału
    /// @return splittime
    return this->split_time_;
}

void Player::setSplitTime(clock_t splittime)
{
    /// @brief setter czasu podziału
    /// @param splittime czasu podziału gracza
    this->split_time_ = splittime;
}

void Player::setType(int type_)
{
    /// @brief setter typu obiektu
    /// @param type_ typu obiektu
    this->type_ = type_;
}

void Player::setMass(const int weight)
{
    /// @brief setter masy, ustawia również promień gracza
    /// @param weight masa gracza
    this->mass_ = weight;
    this->shape_.setRadius(this->getRadius());
}

void Player::calculateSpeed()
{
    /// @brief oblicza aktualną prędkość gracza na podstawie masy
    if((double)(clock() - this->getFreshSpawnedTime()) / CLOCKS_PER_SEC < 0.3 &&
        (double)(clock() - this->getFreshSpawnedTime()) / CLOCKS_PER_SEC > 0)
    {
        this->calculateFreshSpawnedSpeed();
        return;
    }
    this->speed_ = this->starting_speed_ - (log(this->mass_) / log(4));
}

void Player::calculateFreshSpawnedSpeed()
{
    /// @brief oblicza aktualną prędkość gracza na podstawie masy
    this->speed_ = this->starting_speed_ * 3 - 100 * (double)(clock() - this->getFreshSpawnedTime()) / CLOCKS_PER_SEC;
}

void Player::connect(vector<Player>& players)
{
    /// @brief łączy rozdzielonego gracza po określonym czasie
    /// @param players wektor graczy na mapie
    clock_t actualTime = clock();
    if(players.size() > 1){
        if(((double)(actualTime - players[0].getSplitTime()) / CLOCKS_PER_SEC) > 20.0){ // sprawdza czy od ostatniego podziału minął określony czas
            int mass_ = 0;
            Vector2f oldPlayersPos;
            for(auto& it : players){ // łączy wszystkich graczy w jedną masę
                mass_ += it.getMass();
                oldPlayersPos += it.getPlayerPostion();
            }
            Player player = Player(oldPlayersPos.x / players.size(), oldPlayersPos.y / players.size(), mass_, starting_speed_); // tworzy gracza po połączeniu
            players.clear(); // usuwa połączonych graczy
            players.push_back(player);
        }
    }
}

void Player::grow(const int food)
{
    /// @brief funkcja zwiekszająca masę i promień gracza
    /// @param food masa do zjedzenia
    this->mass_ += food;
    this->shape_.setRadius(this->getRadius());
}

void Player::splitMass()
{
    /// @brief funkcja dzieli masę gracza
    if(this->mass_ > 20){
        this->mass_ /= 2;    
        this->shape_.setRadius(this->getRadius());
    }   
}

void Player::split(RenderWindow& window, vector<Player>& players)
{
    /// @brief funkcja dzieląca gracza na pół po wciśnięciu przycisku spacji
    /// @param players wektor graczy na mapie
    bool flag = false;
    while(Keyboard::isKeyPressed(Keyboard::Space)){
        flag = true;
    }
    if(flag){
        std::vector<Player> tempPlayers;
        for(auto& it : players){
            if(players.size() + tempPlayers.size() < 8){ // sprawdzenie czy nie przekroczono maksymalnej ilości kul
                if(it.getMass() > 30){ // sprawdzenie, czy można podzielić
                    players[0].setSplitTime(clock());
                    it.splitMass();
                    float radius = it.getRadius();
                    pair<float, float> relativePos = getRelativeMousePositon(window, players); // pobiera pozycje myszki
                    float direction = atan2(-relativePos.second, relativePos.first); // obliczenie kierunku
                    Player player = Player(it.getPlayerPostion().x + 2.5 * radius * cos(direction),
                        it.getPlayerPostion().y - 2.5 * radius * sin(direction), it.getMass(), starting_speed_); // tworzy nowego gracza wystrzelonego w konkretnym kierunku
                    player.setFreshSpawnedTime(clock()); // ustawia czas respawnu
                    tempPlayers.push_back(player); // wrzuca na wektor tymczasowych graczy
                }
            }
        }
        for(auto& it : tempPlayers){
            players.push_back(it);
        }
    }
}

void Player::splitBySpike(vector<Player>& players)
{
    /// @brief funkcja dzieląca gracza po dotknięciu spike'a
    /// @param players wektor graczy na mapie
    int maxPartsNumber = min(3, (8 - (int)players.size()));//maksymalna ilosc kulek jednego gracza wynosi 8
    if(maxPartsNumber > 0)
    {
        this->setMass(this->getMass() / (maxPartsNumber + 1));
        for(int i = 1; i <= maxPartsNumber; ++i)
        {
            players[0].setSplitTime(clock());
            Player player = Player(this->getPlayerPostion().x + 2 * i * this->getRadius(), 
                this->getPlayerPostion().y, this->getMass(), starting_speed_);
            players.push_back(player);
        }
    }
}

void Player::loseMass()
{
    /// @brief funkcja tracąca masę gracza
    if(this->mass_ >= 20)
    {
        this->mass_ -= 10;
    }
    this->shape_.setRadius(this->getRadius());
}

pair<float, float> Player::getRelativeMousePositon(RenderWindow& window, vector <Player>& players)
{
    /// @brief funkcja zwraca relatywną pozycję myszki na mapie
    /// @param window okno gry
    /// @param players wektor graczy
    /// @return para zawierająca pozycję x i y myszki
    float mouseX = Mouse::getPosition(window).x;
    float mouseY = Mouse::getPosition(window).y;
    mouseX -= window.getSize().x / 2;
    mouseY -= window.getSize().y / 2;
    float centralPositionX = 0;
    float centralPositionY = 0;
    for(auto& it : players)
    { // łączy wszystkich graczy w jedną masę
        centralPositionX += it.getPlayerPostion().x;
        centralPositionY += it.getPlayerPostion().y;
    }
    centralPositionX /= players.size();
    centralPositionY /= players.size();
    mouseX += -this->getPlayerPostion().x + centralPositionX;
    mouseY += -this->getPlayerPostion().y + centralPositionY;
    return {mouseX, mouseY};
}

void Player::move(RenderWindow& window, vector <Player>& players)
{
    /// @brief funkcja odpowiedzialna za poruszanie się gracza w każdą stronę 
    this->calculateSpeed(); // obliczanie prędkości gracza
    pair<float, float> mouseXY = this->getRelativeMousePositon(window, players);
    float direction = atan2(-mouseXY.second, mouseXY.first);
    this->shape_.move(cos(direction) * this->speed_, -sin(direction) * this->speed_);

    if((double)(clock() - this->getFreshSpawnedTime()) / CLOCKS_PER_SEC < 0.3 &&
        (double)(clock() - this->getFreshSpawnedTime()) / CLOCKS_PER_SEC > 0) // oddzielna reguła dla nowo powstałych kul
            return;

    for(auto& it : players) // iteracja po każdej kuli gracza
    { 
        if(this->getShape().getGlobalBounds().intersects(it.getShape().getGlobalBounds())) // sprawdzenie czy kule nie nachodzą na siebie
        {
            float x1 = this->getPlayerPostion().x;
            float y1 = this->getPlayerPostion().y;
            float x2 = it.getPlayerPostion().x;
            float y2 = it.getPlayerPostion().y; // pobranie pozycju

            if(abs(mouseXY.first - x1) + abs(mouseXY.second - y1) 
                <= abs(mouseXY.first - x2) + abs(mouseXY.second - y2))
                    continue;
                    
            float d = this->getRadius() + it.getRadius();
            float diffx = x2 - x1;
            float diffy = y2 - y1;
            float direction = atan2(-diffy, diffx);
            it.getShape().setPosition(x1 + cos(direction) * d, y1 - sin(direction) * d); // omijanie kuli
        }
    }
}

void Player::checkMapCollision()
{
    /// @brief funkcja odpowiedzialna za nie wykraczanie gracza poza obszar mapy
    if(this->shape_.getGlobalBounds().left <= -4800){
        this->shape_.setPosition(-4770, this->shape_.getGlobalBounds().top);
    }
    if(this->shape_.getGlobalBounds().left + this->shape_.getGlobalBounds().width >= 4800){
        this->shape_.setPosition(4800 - this->shape_.getGlobalBounds().width, this->shape_.getGlobalBounds().top);
    }
    if(this->shape_.getGlobalBounds().top <= -2700){
        this->shape_.setPosition(this->shape_.getGlobalBounds().left, -2670);
    }
    if(this->shape_.getGlobalBounds().top + this->shape_.getGlobalBounds().height >= 2700){
        this->shape_.setPosition(this->shape_.getGlobalBounds().left, 2700 - this->shape_.getGlobalBounds().height);
    }
}

void Player::setPosition(std::vector<Player>& players, RenderWindow& window)
{
    /// @brief setter pozyji gracza
    /// @param players wektor graczy na planszy
    this->move(window, players);
    this->split(window, players);
    this->connect(players);
    this->checkMapCollision();
}

void Player::render(RenderTarget& target)
{
    /// @brief renderuje obiekt na mapie
    /// @param target miejsce renderu obiektu
    target.draw(this->shape_);
}
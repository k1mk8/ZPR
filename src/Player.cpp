#include "Player.h"

void Player::Variables(const int mass, const int speed)
{
    /// @brief ustawia zmienne klasy
    /// @param mass masa punktu
    this->startingSpeed = speed;
    this->mass = mass;
    this->speed = this->startingSpeed - (log(this->mass) / log(4));
    this->shape.setOutlineColor(Color::Cyan);
    this->shape.setOutlineThickness(10);
}

void Player::makeShape()
{
    /// @brief tworzy obiekt
    this->shape.setFillColor(Color::Green);
    this->shape.setRadius(this->getRadius());
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
    this->speed = this->startingSpeed - (log(this->mass) / log(4));
}

void Player::calculateFreshSpawnedSpeed()
{
    /// @brief oblicza aktualną prędkość gracza na podstawie masy
    this->speed = this->startingSpeed * 3 - 100 * (double)(clock() - this->getFreshSpawnedTime()) / CLOCKS_PER_SEC;
}

void Player::connect(vector<Player>& players)
{
    /// @brief łączy rozdzielonego gracza po określonym czasie
    /// @param players wektor graczy na mapie
    clock_t actualTime = clock();
    if(players.size() > 1){
        if(((double)(actualTime - players[0].getSplitTime()) / CLOCKS_PER_SEC) > 20.0){ // sprawdza czy od ostatniego podziału minął określony czas
            int mass = 0;
            Vector2f oldPlayersPos;
            for(auto& it : players){ // łączy wszystkich graczy w jedną masę
                mass += it.getMass();
                oldPlayersPos += it.getPlayerPostion();
            }
            Player player = Player(oldPlayersPos.x / players.size(), oldPlayersPos.y / players.size(), mass, startingSpeed); // tworzy gracza po połączeniu
            players.clear(); // usuwa połączonych graczy
            players.push_back(player);
        }
    }
}
Player::Player(float x, float y, const int mass, const int speed)
{
    /// @brief konstruktor klasy tworzący jej obiekt
    /// @param x pozycja horyzontalna gracza
    /// @param y pozycja wertykalna gracza
    /// @param mass masa gracza
    this->shape.setPosition(x,y);
    this->Variables(mass, speed);
    this->makeShape();
}

Player::~Player()
{
    /// destruktor klasy
}

CircleShape & Player::getShape()
{
    /// @brief getter kształtu gracza
    /// @return kształt gracza
    return this->shape;
}

const int & Player::getMass() const
{
    /// @brief getter masy gracza
    /// @return masa gracza
    return this->mass;
}

float Player::getRadius()
{
    /// @brief getter promienia gracza
    /// @return promień gracza
    return log(this->mass)/log(1.05) - 30;
}

const float & Player::getSpeed() const
{
    /// @brief getter prędkości gracza
    /// @return prędkość gracza
    return this->speed;
}

const Vector2f & Player::getPlayerPostion() const
{
    /// @brief getter pozycji gracza na mapie
    /// @return pozycja
    return this->shape.getPosition();
}

const clock_t & Player::getFreshSpawnedTime() const
{
    /// @brief getter czasu podziału
    /// @return splittime
    return this->freshSpawnedTime;
}

void Player::setFreshSpawnedTime(clock_t freshSpawnedTime)
{
    /// @brief getter czasu podziału
    /// @return splittime
    this->freshSpawnedTime = freshSpawnedTime;
}

const clock_t & Player::getSplitTime() const
{
    /// @brief getter czasu podziału
    /// @return splittime
    return this->splitTime;
}

void Player::setSplitTime(clock_t splittime)
{
    /// @brief setter czasu podziału
    /// @param splittime czasu podziału gracza
    this->splitTime = splittime;
}

void Player::setMass(const int weight)
{
    /// @brief setter masy, ustawia również promień gracza
    /// @param weight masa gracza
    this->mass = weight;
    this->shape.setRadius(this->getRadius());
}

void Player::grow(const int food)
{
    /// @brief funkcja zwiekszająca masę i promień gracza
    /// @param food masa do zjedzenia
    this->mass += food;
    this->shape.setRadius(this->getRadius());
}

void Player::splitMass()
{
    /// @brief funkcja dzieli masę gracza
    if(this->mass > 20){
        this->mass /= 2;    
        this->shape.setRadius(this->getRadius());
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
            if(players.size() + tempPlayers.size() < 8){
                if(it.getMass() > 30){
                    players[0].setSplitTime(clock());
                    it.splitMass();
                    float radius = it.getRadius();
                    pair<float, float> relativePos = getRelativeMousePositon(window, players);
                    float direction = atan2(-relativePos.second, relativePos.first);
                    Player player = Player(it.getPlayerPostion().x + 2.5 * radius * cos(direction),
                        it.getPlayerPostion().y - 2.5 * radius * sin(direction), it.getMass(), startingSpeed);
                    player.setFreshSpawnedTime(clock());
                    tempPlayers.push_back(player);
                }
            }
        }
        for(auto& it : tempPlayers){
            players.push_back(it);
        }
    }
}

template<typename T>
void Player::splitBySpike(vector <T>& participants)
{
    /// @brief funkcja dzieląca gracza po dotknięciu spike'a
    /// @param participants wektor graczy na mapie
    int maxPartsNumber = min(3, (8 - (int)participants.size()));//maksymalna ilosc kulek jednego gracza wynosi 8
    if(maxPartsNumber > 0)
    {
        this->setMass(this->getMass() / (maxPartsNumber + 1));
        for(int i = 1; i <= maxPartsNumber; ++i)
        {
            participants[0].setSplitTime(clock());
            T participant = T(this->getPlayerPostion().x + 2 * i * this->getRadius(), this->getPlayerPostion().y, this->getMass(), startingSpeed);
            participants.push_back(participant);
        }
    }
}

void Player::loseMass()
{
    /// @brief funkcja tracąca masę gracza
    if(this->mass >= 20)
    {
        this->mass -= 10;
    }
    this->shape.setRadius(this->getRadius());
}

pair<float, float> Player::getRelativeMousePositon(RenderWindow& window, vector <Player>& players)
{
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
    this->shape.move(cos(direction) * this->speed, -sin(direction) * this->speed);
    if((double)(clock() - this->getFreshSpawnedTime()) / CLOCKS_PER_SEC < 0.3 &&
        (double)(clock() - this->getFreshSpawnedTime()) / CLOCKS_PER_SEC > 0)
            return;
    for(auto& it : players)
    { 
        if(this->getShape().getGlobalBounds().intersects(it.getShape().getGlobalBounds()))
        {
            float x1 = this->getPlayerPostion().x;
            float y1 = this->getPlayerPostion().y;
            float x2 = it.getPlayerPostion().x;
            float y2 = it.getPlayerPostion().y;
            if(abs(mouseXY.first - x1) + abs(mouseXY.second - y1) 
                <= abs(mouseXY.first - x2) + abs(mouseXY.second - y2))
                    continue;
            float d = this->getRadius() + it.getRadius();
            float diffx = x2 - x1;
            float diffy = y2 - y1;
            float direction = atan2(-diffy, diffx);
            it.getShape().setPosition(x1 + cos(direction) * d, y1 - sin(direction) * d);
        }
    }
}

void Player::checkMapCollision()
{
    /// @brief funkcja odpowiedzialna za nie wykraczanie gracza poza obszar mapy
    if(this->shape.getGlobalBounds().left <= -4800){
        this->shape.setPosition(-4750, this->shape.getGlobalBounds().top);
    }
    if(this->shape.getGlobalBounds().left + this->shape.getGlobalBounds().width >= 4800){
        this->shape.setPosition(4800 - this->shape.getGlobalBounds().width, this->shape.getGlobalBounds().top);
    }
    if(this->shape.getGlobalBounds().top <= -2700){
        this->shape.setPosition(this->shape.getGlobalBounds().left, -2650);
    }
    if(this->shape.getGlobalBounds().top + this->shape.getGlobalBounds().height >= 2700){
        this->shape.setPosition(this->shape.getGlobalBounds().left, 2700 - this->shape.getGlobalBounds().height);
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
    target.draw(this->shape);
}
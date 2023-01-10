#include "Player.h"

void Player::Variables(const int mass)
{
    /// @brief ustawia zmienne klasy
    /// @param mass masa punktu
    this->speed = 10;
    this->startingSpeed = 10;
    this->mass = mass;
}

void Player::makeShape()
{
    /// @brief tworzy obiekt
    this->shape.setFillColor(Color::Green);
    this->shape.setRadius(log(mass)/log(1.05));
}

void Player::calculateSpeed()
{
    /// @brief oblicza aktualną prędkość gracza na podstawie masy
    this->speed = this->startingSpeed - (log(this->mass) / log(4));
}

void Player::connect(std::vector<Player>& players)
{
    /// @brief łączy rozdzielonego gracza po określonym czasie
    /// @param players wektor graczy na mapie
    clock_t actualTime = clock();
    if(players.size() > 1){
        if(((double)(actualTime - players[0].getSplitTime()) / CLOCKS_PER_SEC) > 30.0){ // sprawdza czy od ostatniego podziału minął określony czas
            int mass = 0;
            for(auto& it : players){ // łączy wszystkich graczy w jedną masę
                mass += it.getMass();
            }
            Player player = Player(players[0].getPlayerPostion().x, players[0].getPlayerPostion().x, mass); // tworzy gracza po połączeniu
            players.clear(); // usuwa połączonych graczy
            players.push_back(player);
        }
    }
}

Player::Player(float x, float y, const int mass)
{
    /// @brief konstruktor klasy tworzący jej obiekt
    /// @param x pozycja horyzontalna gracza
    /// @param y pozycja wertykalna gracza
    /// @param mass masa gracza
    this->shape.setPosition(x,y);
    this->Variables(mass);
    this->makeShape();
    }

Player::~Player()
{
    /// destruktor klasy
}

const CircleShape & Player::getShape() const
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
    this->shape.setRadius(log(weight)/log(1.05));
}

void Player::grow(const int food)
{
    /// @brief funkcja zwiekszająca masę i promień gracza
    /// @param food masa do zjedzenia
    this->mass += food;
    int mass = this->getMass();
    this->shape.setRadius(log(mass)/log(1.05));
}

void Player::splitMass()
{
    /// @brief funkcja dzieli masę gracza
    if(this->mass > 20){
        this->mass /= 2;    
        this->shape.setRadius(log(mass)/log(1.05));
    }   
}

void Player::split(std::vector<Player>& players)
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
            if(players.size() + tempPlayers.size() < 16){
                if(it.getMass() > 30){
                    players[0].setSplitTime(clock());
                    it.splitMass();
                    Player player = Player(it.getPlayerPostion().x + 2 * log(it.getMass())/log(1.05),
                        it.getPlayerPostion().y + 2 * log(it.getMass())/log(1.05), it.getMass());
                    tempPlayers.push_back(player);
                }
            }
        }
        for(auto& it : tempPlayers){
            players.push_back(it);
        }
    }
}

void Player::splitBySpike(std::vector <Player>& players)
{
    /// @brief funkcja dzieląca gracza po dotknięciu spike'a
    /// @param players wektor graczy na mapie
    if(players.size() + 8 <=16){
        this->setMass(this->getMass()/8);
        for(int i=0;i<8;++i){
            Player player = Player(this->getPlayerPostion().x, this->getPlayerPostion().x, this->getMass());
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
}

void Player::shootingMass()
{
    // /// @brief funkcja odpowiedzialna za wystrzeliwanie masy przez gracza
    // /// @return prawda lub fałsz, czy gracz strzelił masą
    // bool shooting = false;
    // while(Keyboard::isKeyPressed(Keyboard::T)){
    //     shooting = true;
    // }
    // if(shooting){
    //     this->loseMass();
    //     this->shape.setRadius(log(this->getMass())/log(1.05));
    //     return true;
    // }
    // return false;
}

void Player::move()
{
    /// @brief funkcja odpowiedzialna za poruszanie się gracza w każdą stronę 
    this->calculateSpeed(); // obliczanie prędkości gracza
    if(Keyboard::isKeyPressed(Keyboard::W)){ // poruszanie do góry
        this->shape.move(0, -this->speed);
    }
    else if(Keyboard::isKeyPressed(Keyboard::S)){ // poruszanie do dołu
        this->shape.move(0, this->speed);
    }
    else if(Keyboard::isKeyPressed(Keyboard::A)){ // poruszanie w ewo
        this->shape.move(-this->speed, 0);
    }
    else if(Keyboard::isKeyPressed(Keyboard::D)){ // porzuszanie w prawo
        this->shape.move(this->speed, 0);
    }
    else if(Keyboard::isKeyPressed(Keyboard::P)){ // do usunięcia
        this->setMass(0);
    }
}

void Player::checkMapCollision()
{
    /// @brief funkcja odpowiedzialna za nie wykraczanie gracza poza obszar mapy
    if(this->shape.getGlobalBounds().left <= -4800){
        this->shape.setPosition(-4800, this->shape.getGlobalBounds().top);
    }
    if(this->shape.getGlobalBounds().left + this->shape.getGlobalBounds().width >= 4800){
        this->shape.setPosition(4800 - this->shape.getGlobalBounds().width, this->shape.getGlobalBounds().top);
    }
    if(this->shape.getGlobalBounds().top <= -2700){
        this->shape.setPosition(this->shape.getGlobalBounds().left, -2700);
    }
    if(this->shape.getGlobalBounds().top + this->shape.getGlobalBounds().height >= 2700){
        this->shape.setPosition(this->shape.getGlobalBounds().left, 2700 - this->shape.getGlobalBounds().height);
    }
}

void Player::setPosition(std::vector<Player>& players)
{
    /// @brief setter pozyji gracza
    /// @param players wektor graczy na planszy
    this->move();
    this->split(players);
    this->connect(players);
    this->shootingMass();
    this->checkMapCollision();
}

void Player::render(RenderTarget& target)
{
    /// @brief renderuje obiekt na mapie
    /// @param target miejsce renderu obiektu
    target.draw(this->shape);
}
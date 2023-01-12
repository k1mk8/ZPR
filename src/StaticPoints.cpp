#include "StaticPoints.h"

void StaticPoints::makeShape(std::vector<Player> rect)
{
    /// @brief tworzy kształt przycisku na podstawie typu obiektu
    /// @param rect lista graczy, aby punkty nie tworzyły się w graczach
    Color color;
    switch (this->type)
    {
    case FOOD: // tworzenie jedzenia
        color = Color::Blue;
        this->mass = 1;
        this->shape.setRadius(5);
        break;
    case SPIKES: // tworzenie spike, który rozbija większych graczy
        color = Color::Red;
        this->shape.setRadius(30);
        this->mass = 30;
        break;
    }
    this->shape.setFillColor(color);
    Vector2f size = Vector2f(9600, 5400);
    int t[2];
    t[0] = -1;
    t[1] = 1;
    bool contain = true;
    int x, y;
    while(contain)
    {
        x = static_cast<float>((rand() % (int(size.x) / 2)) * t[(rand() % 2)] - this->shape.getGlobalBounds().width);
        y = static_cast<float>((rand() % (int(size.y) / 2)) * t[(rand() % 2)] - this->shape.getGlobalBounds().height);
        for(auto& it : rect) // iteruje się po wszystkich graczach na planszy
        {
            CircleShape point;
            point.setRadius(5);
            point.setPosition(x,y);
            if(it.getShape().getGlobalBounds().intersects(point.getGlobalBounds())){ // sprawdza przecięcie się punktów na planszy
                contain = true;
                break;
            }
            else
            {
                contain = false;
            }
        }
    }
    this->shape.setPosition(Vector2f(x,y)); // ustawia pozycje punktu
}

StaticPoints::StaticPoints(int type, std::vector <Player> rect)
        : type(type)
{
    /// @brief konstruktor domyślny tworzący obiekt klasy
    /// @param type typ punktu
    /// @param rect wektor z graczami na planszy
    this->makeShape(rect);
}
StaticPoints::StaticPoints(int type, float X, float Y)
        : type(type)
{
    /// @brief konstruktor pozycyjny tworzący obiekt klasy
    /// @param type typ punktu
    /// @param rect wektor z graczami na planszy
    this->shape.setFillColor(Color::Blue);
    this->mass = 10;
    this->shape.setRadius(8);
    this->shape.setPosition(X, Y);
}
StaticPoints::StaticPoints(int type, float X, float Y, float speed, float direction)
        : type(type)
{
    /// @brief konstruktor pozycyjny tworzący obiekt klasy
    /// @param type typ punktu
    /// @param rect wektor z graczami na planszy
    this->shape.setFillColor(Color::Blue);
    this->mass = 10;
    this->shape.setRadius(8);
    this->shape.setPosition(X, Y);
    this->speed = speed;
    this->freshSpawnedTime = clock();
    this->direction = direction;
}
StaticPoints::~StaticPoints()
{
    /// destruktor klasy
}

const CircleShape StaticPoints::getShape() const
{
    /// @brief getter kształtu punktu
    /// @return kształt punktu
    return this->shape;
}

const Vector2f & StaticPoints::getPlayerPostion() const
{
    /// @brief getter pozycji gracza na mapie
    /// @return pozycja
    return this->shape.getPosition();
}

const int& StaticPoints::getType() const
{
    /// @brief getter typu punktu
    /// @return typ punktu
    return this->type;
}

const int& StaticPoints::getMass() const
{
    /// @brief getter masy punktu
    /// @return masa punktu
    return this->mass;
}

void StaticPoints::render(RenderTarget& target)
{
    /// @brief renderuje obiekt na mapie
    /// @param target miejsce renderu obiektu
    target.draw(this->shape);
}


void StaticPoints::calculateSpeed()
{
    if(this->speed > 0)
    {
        this->speed -= 0.6 * (double)(clock() - this->freshSpawnedTime) / CLOCKS_PER_SEC;
        this->shape.setPosition(this->getPlayerPostion().x + cos(direction) * speed, 
            this->getPlayerPostion().y - sin(direction) * speed);
    }
}
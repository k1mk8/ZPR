/*
    @file StaticPoints.cc
    @author Karol Kasperek, Szymon Dyszewski
    @brief plik zawierający implementację klasy StaticPoints
*/

#include "StaticPoints.h"

using namespace std;
using namespace sf;

void StaticPoints::makeShape(vector<Player> players) {
  /// @brief tworzy kształt przycisku na podstawie typu obiektu
  /// @param players lista graczy, aby punkty nie tworzyły się w graczach
  Color color;
  switch (this->type_) {
  case FOOD: // tworzenie jedzenia
    color = Color::Blue;
    this->mass_ = 1;
    this->shape_.setRadius(5);
    break;
  case SPIKES: // tworzenie spike, który rozbija większych graczy
    color = Color::Red;
    this->shape_.setRadius(30);
    this->mass_ = 30;
    break;
  }
  this->shape_.setFillColor(color);
  Vector2f size = Vector2f(9600, 5400);
  int t[2];
  t[0] = -1;
  t[1] = 1;
  bool contain = true;
  float x, y;
  while (contain) {
    x = float((rand() % (int(size.x) / 2)) * t[(rand() % 2)] -
              this->shape_.getGlobalBounds().width);
    y = float((rand() % (int(size.y) / 2)) * t[(rand() % 2)] -
              this->shape_.getGlobalBounds().height);
    for (auto &it : players) // iteruje się po wszystkich graczach na planszy
    {
      CircleShape point;
      point.setRadius(5);
      point.setPosition(x, y);
      if (it.getShape().getGlobalBounds().intersects(
              point.getGlobalBounds())) { // sprawdza przecięcie się punktów na
                                          // planszy
        contain = true;
        break;
      } else
        contain = false;
    }
  }
  this->shape_.setPosition(Vector2f(x, y)); // ustawia pozycje punktu
}

StaticPoints::StaticPoints(int type_, vector<Player> players) : type_(type_) {
  /// @brief konstruktor domyślny tworzący obiekt klasy
  /// @param type_ typ punktu
  /// @param players wektor z graczami na planszy
  this->makeShape(players);
}
StaticPoints::StaticPoints(int type_, float X, float Y) : type_(type_) {
  /// @brief konstruktor pozycyjny tworzący obiekt klasy
  /// @param type_ typ punktu
  /// @param X pozycja X
  /// @param Y pozycja Y

  this->shape_.setFillColor(Color::Blue);
  this->mass_ = 10;
  this->shape_.setRadius(8);
  this->shape_.setPosition(X, Y);
}
StaticPoints::StaticPoints(int type_, float X, float Y, float speed_,
                           float direction_)
    : type_(type_) {
  /// @brief konstruktor pozycyjny tworzący obiekt klasy
  /// @param type_ typ punktu
  /// @param X pozycja X
  /// @param Y pozycja Y
  /// @param speed_ prędkość
  /// @param direction_ kierunek

  this->shape_.setFillColor(Color::Blue);
  this->mass_ = 10;
  this->shape_.setRadius(8);
  this->shape_.setPosition(X, Y);
  this->speed_ = speed_;
  this->fresh_spawned_time_ = clock();
  this->direction_ = direction_;
}
StaticPoints::~StaticPoints() {
  /// destruktor klasy
}

const CircleShape StaticPoints::getShape() const {
  /// @brief getter kształtu punktu
  /// @return kształt punktu
  return this->shape_;
}

const Vector2f &StaticPoints::getPlayerPostion() const {
  /// @brief getter pozycji gracza na mapie
  /// @return pozycja
  return this->shape_.getPosition();
}

const int &StaticPoints::getType() const {
  /// @brief getter typu punktu
  /// @return typ punktu
  return this->type_;
}

const int &StaticPoints::getMass() const {
  /// @brief getter masy punktu
  /// @return masa punktu
  return this->mass_;
}

void StaticPoints::render(RenderTarget &target) {
  /// @brief renderuje obiekt na mapie
  /// @param target miejsce renderu obiektu
  target.draw(this->shape_);
}

void StaticPoints::calculateSpeed() {
  /// @brief funkcja obliczająca prędkość nowo wystrzelonych obiektów
  if (this->speed_ > 0) {
    this->speed_ -=
        0.6 * (double)(clock() - this->fresh_spawned_time_) / CLOCKS_PER_SEC;
    this->shape_.setPosition(
        this->getPlayerPostion().x + cos(direction_) * speed_,
        this->getPlayerPostion().y - sin(direction_) * speed_);
  }
}
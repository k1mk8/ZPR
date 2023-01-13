#include "Interface.h"

using namespace std;
using namespace sf;

void Interface::setTexture()
{
    /// @brief funkcja ustawia tekstury okna z pliku
    this->texture_.loadFromFile("images/tlo.png");
    this->sprite_.setTexture(texture_);
    this->video_mode_ = VideoMode(1200, 630);
}

void Interface::initButton()
{
    /// @brief iniciuje przycisk do rozpoczęcia gry
    this->button_ = Button(Vector2f(125, 60), Color::Cyan, Vector2f(560, 550));
    this->speed1_ = Button(Vector2f(125, 60), Color::Cyan, Vector2f(380, 470));
    this->speed2_ = Button(Vector2f(125, 60), Color::Cyan, Vector2f(560, 470));
    this->speed3_ = Button(Vector2f(125, 60), Color::Cyan, Vector2f(740, 470));
}

void Interface::initText()
{
    /// @brief iniciuje teksty do interfejsu
    // tekst początkowy ekranu
    setNewTextParams(this->standard_text_, Color::Black, 25, Vector2f(280,100), "\t\t\t\t\t\tWitamy w grze AGARIO!\n Prosze wcisnac przycisk graj, aby rozpoczac rozgrywke!");
    
    // tekst na przycisku
    setNewTextParams(this->button_text_, Color::Black, 25, Vector2f(590,565), "Graj!");

    // tekst na przycisku prędkości
    setNewTextParams(this->button_text1_, Color::Black, 35, Vector2f(420,475), "5x");

    // tekst na przycisku prędkości
    setNewTextParams(this->button_text2_, Color::Black, 35, Vector2f(600,475), "10x");

    // tekst na przycisku prędkości
    setNewTextParams(this->button_text3_, Color::Black, 35, Vector2f(780,475), "20x");

    // maksymalna ilość punktów w historii
    int all_max_points = 0;
    ifstream Plik("./maxPoints.txt"); // pobieranie danych z pliku o maksymalnej ilości punktów
    Plik >> all_max_points;
    Plik.close();
    auto s = to_string(all_max_points);
    setNewTextParams(this->max_points_text_, Color::Black, 25, Vector2f(380,425), "Twoj najlepszy dotychczasowy wynik to: " + s);
}

Interface::Interface()
{
    /// @brief konstruktor domyślny
    this->initWindow();
    this->initFonts();
    this->initText();
    this->initButton();
}

int Interface::update()
{
    /// @brief funkcja sprawdzająca czy wydarzyły się jakieś interakcje od użytkownika
    /// @return czy przycisk rozpoczęcia gry został wciśnięty
    this->pollEvents();
    if(this->button_.isButtonPressed(this->window_))
        return 1;
    if(this->speed1_.isButtonPressed(this->window_))
        return 2;
    if(this->speed2_.isButtonPressed(this->window_))
        return 3;
    if(this->speed3_.isButtonPressed(this->window_))
        return 4;
    return 0;
}

void Interface::renderGui(RenderTarget* target)
{
    /// @brief funkcja generująca GUI dla okna
    /// @param target miejsce renderu obiektu
    target->draw(this->standard_text_);
    target->draw(this->max_points_text_);
    target->draw(this->button_text_);
    target->draw(this->button_text1_);
    target->draw(this->button_text2_);
    target->draw(this->button_text3_);
}

void Interface::render()
{
    /// @brief funkcja renderująca i wyświetlająca okno
    this->window_->clear(Color::White);
    this->window_->draw(sprite_);
    this->window_->draw(this->button_.getButton());
    this->window_->draw(this->speed1_.getButton());
    this->window_->draw(this->speed2_.getButton());
    this->window_->draw(this->speed3_.getButton());
    this->renderGui(this->window_);
    this->window_->display();
}
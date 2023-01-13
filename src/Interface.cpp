#include "Interface.h"

using namespace std;
using namespace sf;

void Interface::setTexture()
{
    this->texture.loadFromFile("images/tlo.png");
    this->sprite.setTexture(texture);
    this->videoMode = VideoMode(1200, 630);
}

void Interface::initButton()
{
    /// @brief iniciuje przycisk do rozpoczęcia gry
    this->button = Button(Vector2f(125, 60), Color::Cyan, Vector2f(560, 550));
    this->speed1 = Button(Vector2f(125, 60), Color::Cyan, Vector2f(380, 470));
    this->speed2 = Button(Vector2f(125, 60), Color::Cyan, Vector2f(560, 470));
    this->speed3 = Button(Vector2f(125, 60), Color::Cyan, Vector2f(740, 470));
}

void Interface::initText()
{
    /// @brief iniciuje teksty do interfejsu
    // tekst początkowy ekranu
    setNewTextParams(this->standardText, Color::Black, 25, Vector2f(280,100), "\t\t\t\t\t\tWitamy w grze AGARIO!\n Prosze wcisnac przycisk graj, aby rozpoczac rozgrywke!");
    
    // tekst na przycisku
    setNewTextParams(this->buttonText, Color::Black, 25, Vector2f(590,565), "Graj!");

    // tekst na przycisku prędkości
    setNewTextParams(this->buttonText1, Color::Black, 35, Vector2f(420,475), "5x");

    // tekst na przycisku prędkości
    setNewTextParams(this->buttonText2, Color::Black, 35, Vector2f(600,475), "10x");

    // tekst na przycisku prędkości
    setNewTextParams(this->buttonText3, Color::Black, 35, Vector2f(780,475), "20x");

    // maksymalna ilość punktów w historii
    int allMaxPoints = 0;
    ifstream Plik("./maxPoints.txt"); // pobieranie danych z pliku o maksymalnej ilości punktów
    Plik >> allMaxPoints;
    Plik.close();
    auto s = to_string(allMaxPoints);
    setNewTextParams(this->maxPointsText, Color::Black, 25, Vector2f(380,425), "Twoj najlepszy dotychczasowy wynik to: " + s);
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
    if(this->button.isButtonPressed(this->window))
        return 1;
    if(this->speed1.isButtonPressed(this->window))
        return 2;
    if(this->speed2.isButtonPressed(this->window))
        return 3;
    if(this->speed3.isButtonPressed(this->window))
        return 4;
    return 0;
}

void Interface::renderGui(RenderTarget* target)
{
    /// @brief funkcja generująca GUI dla okna
    /// @param target miejsce renderu obiektu
    target->draw(this->standardText);
    target->draw(this->maxPointsText);
    target->draw(this->buttonText);
    target->draw(this->buttonText1);
    target->draw(this->buttonText2);
    target->draw(this->buttonText3);
}

void Interface::render()
{
    /// @brief funkcja renderująca i wyświetlająca okno
    this->window->clear(Color::White);
    this->window->draw(sprite);
    this->window->draw(this->button.getButton());
    this->window->draw(this->speed1.getButton());
    this->window->draw(this->speed2.getButton());
    this->window->draw(this->speed3.getButton());
    this->renderGui(this->window);
    this->window->display();
}
#include "BasicWindow.h"

void BasicWindow::setTexture(){}

void BasicWindow::initWindow()
{
    /// @brief inifcuje początkowe wartości interfejsu
    this->setTexture();
    this->window = new RenderWindow(this->videoMode, "Agario", Style::Close | Style::Titlebar);
    this->window->clear(Color::White);
    this->window->setFramerateLimit(60);
}

void BasicWindow::initFonts()
{
    /// @brief ustawia czcionkę tekstu
    if(!this->font.loadFromFile("fonts/MilkyHoney.ttf")){
        cout << "COULD NOT LOAD MilkyHoney.ttf" << "\n";
    }
}

void BasicWindow::initButton(){}


void BasicWindow::setNewTextParams(Text& name, Color color, int size, Vector2f setPosition, string text)
{
    name.setFont(this->font);
    name.setFillColor(color);
    name.setCharacterSize(size);
    name.setPosition(setPosition);
    name.setString(text);
}

bool BasicWindow::running()
{
    /// @brief funkcja sprawdzająca czy okno jest otwarte
    /// @return prawda lub fałsz, czy okno jest otwarte
    return this->window->isOpen();
}

void BasicWindow::pollEvents()
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

BasicWindow::BasicWindow()
{
    /// @brief konstruktor domyślny
}

BasicWindow::~BasicWindow()
{
    /// @brief destruktor domyślny
    delete this->window;
}

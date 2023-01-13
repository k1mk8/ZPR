#include "Interface.h"

using namespace std;
void Interface::initWindow()
{
    /// @brief inifcuje początkowe wartości interfejsu
    this->texture.loadFromFile("images/tlo.png");
    this->sprite.setTexture(texture);
    this->videoMode = VideoMode(1200, 630);
    this->window = new RenderWindow(this->videoMode, "Agario", Style::Close | Style::Titlebar);
    this->window->clear(Color::White);
    this->window->setFramerateLimit(60);
}

void Interface::initFonts()
{
    /// @brief ustawia czcionkę tekstu
    if(!this->font.loadFromFile("fonts/MilkyHoney.ttf")){
        cout << " COULD NOT LOAD MilkyHoney.ttf" << "\n";
    }
}

void Interface::initButton()
{
    /// @brief iniciuje przycisk do rozpoczęcia gry
    this->button = Button(Vector2f(125, 60), Color::Cyan, Vector2f(560, 550));
    this->speed1 = Button(Vector2f(125, 60), Color::Cyan, Vector2f(380, 470));
    this->speed2 = Button(Vector2f(125, 60), Color::Cyan, Vector2f(560, 470));
    this->speed3 = Button(Vector2f(125, 60), Color::Cyan, Vector2f(740, 470));
}

void Interface::setNewTextParams(Text& name, Color color, int size, Vector2f setPosition, string text)
{
    name.setFont(this->font);
    name.setFillColor(color);
    name.setCharacterSize(size);
    name.setPosition(setPosition);
    name.setString(text);
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

Interface::~Interface()
{
    /// @brief destruktor domyślny
    delete this->window;
}

bool Interface::running()
{
    /// @brief funkcja sprawdzająca czy okno jest otwarte
    /// @return prawda lub fałsz, czy okno jest otwarte
    return this->window->isOpen();
}

void Interface::pollEvents()
{
    /// @brief funkcja sprawdzająca czy okno ma być zamknięte
    while(this->window->pollEvent(this->sfmlEvent))
    {
if (this->sfmlEvent.type == Event::Closed)
        {
            this->window->close();
            break;
        }
        else if(this->sfmlEvent.type == Event::KeyPressed)
        {
            if(this->sfmlEvent.key.code == Keyboard::Escape)
            {
                this->window->close();
                break;
            }
        }
        break;
    }
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
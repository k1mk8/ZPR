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



void Interface::initText()
{
    /// @brief iniciuje teksty do interfejsu
    this->guiText.setFont(this->font);
    this->guiText.setFillColor(Color::Black);
    this->guiText.setCharacterSize(32);

    // tekst początkowy ekranu
    this->standardText.setFont(this->font);
    this->standardText.setFillColor(Color::Black);
    this->standardText.setCharacterSize(25);
    this->standardText.setPosition(Vector2f(280,100));
    this->standardText.setString("\t\t\t\t\t\tWitamy w grze AGARIO!\n Prosze wcisnac przycisk graj, aby rozpoczac rozgrywke!");

    // tekst na przycisku
    this->buttonText.setFont(this->font);
    this->buttonText.setFillColor(Color::Black);
    this->buttonText.setCharacterSize(25);
    this->buttonText.setPosition(Vector2f(590,565));
    this->buttonText.setString("Graj!");

    // tekst na przycisku prędkości
    this->buttonText1.setFont(this->font);
    this->buttonText1.setFillColor(Color::Black);
    this->buttonText1.setCharacterSize(35);
    this->buttonText1.setPosition(Vector2f(420,475));
    this->buttonText1.setString("5x");

    // tekst na przycisku prędkości
    this->buttonText2.setFont(this->font);
    this->buttonText2.setFillColor(Color::Black);
    this->buttonText2.setCharacterSize(35);
    this->buttonText2.setPosition(Vector2f(600,475));
    this->buttonText2.setString("10x");

    // tekst na przycisku prędkości
    this->buttonText3.setFont(this->font);
    this->buttonText3.setFillColor(Color::Black);
    this->buttonText3.setCharacterSize(35);
    this->buttonText3.setPosition(Vector2f(780,475));
    this->buttonText3.setString("20x");

    // maksymalna ilość punktów w historii
    this->maxPointsText.setFont(this->font);
    this->maxPointsText.setFillColor(Color::Black);
    this->maxPointsText.setCharacterSize(25);
    this->maxPointsText.setPosition(Vector2f(380,425));
    int allMaxPoints = 0;
    ifstream Plik("./maxPoints.txt"); // pobieranie danych z pliku o maksymalnej ilości punktów
    Plik >> allMaxPoints;
    Plik.close();
    auto s = to_string(allMaxPoints);
    this->maxPointsText.setString("Twoj najlepszy dotychczasowy wynik to: " + s);
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
    target->draw(this->guiText);
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
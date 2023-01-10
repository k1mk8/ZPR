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
    this->button = Button(Vector2f(125, 60), Color::Cyan, Vector2f(560, 500));
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
    this->buttonText.setPosition(Vector2f(590,515));
    this->buttonText.setString("Graj!");

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

bool Interface::update()
{
    /// @brief funkcja sprawdzająca czy wydarzyły się jakieś interakcje od użytkownika
    /// @return czy przycisk rozpoczęcia gry został wciśnięty
    this->pollEvents();
    return this->button.isButtonPressed(this->window);
}

void Interface::renderGui(RenderTarget* target)
{
    /// @brief funkcja generująca GUI dla okna
    /// @param target miejsce renderu obiektu
    target->draw(this->guiText);
    target->draw(this->standardText);
    target->draw(this->maxPointsText);
    target->draw(this->buttonText);
}

void Interface::render()
{
    /// @brief funkcja renderująca i wyświetlająca okno
    this->window->clear(Color::White);
    this->window->draw(sprite);
    this->window->draw(this->button.getButton());
    this->renderGui(this->window);
    this->window->display();
}
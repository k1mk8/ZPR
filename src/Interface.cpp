#include "Interface.h"

using namespace std;
void Interface::initWindow()
{
    this->texture.loadFromFile("tlo.png");
    this->sprajt.setTexture(texture);
    this->videoMode = VideoMode(1200.f, 630.f);
    this->window = new RenderWindow(this->videoMode, "Agario", Style::Close | Style::Titlebar);
    this->window->clear(Color::White);
    this->window->setFramerateLimit(60);
}

void Interface::initFonts()
{
    if(!this->font.loadFromFile("fonts/MilkyHoney.ttf")){
        cout << " COULD NOT LOAD MilkyHoney.ttf" << "\n";
    }
}

void Interface::initButton()
{
    this->button = Button(Vector2f(125, 60), Color::Cyan, Vector2f(560, 500));
}


void Interface::initText()
{
    this->guiText.setFont(this->font);
    this->guiText.setFillColor(Color::Black);
    this->guiText.setCharacterSize(32);

    this->standardText.setFont(this->font);
    this->standardText.setFillColor(Color::Black);
    this->standardText.setCharacterSize(25);
    this->standardText.setPosition(Vector2f(280,100));
    this->standardText.setString("\t\t\t\t\t\tWitamy w grze AGARIO!\n Prosze wcisnac przycisk graj, aby rozpoczac rozgrywke!");

    this->buttonText.setFont(this->font);
    this->buttonText.setFillColor(Color::Black);
    this->buttonText.setCharacterSize(25);
    this->buttonText.setPosition(Vector2f(590,515));
    this->buttonText.setString("Graj!");

    this->maxPointsText.setFont(this->font);
    this->maxPointsText.setFillColor(Color::Black);
    this->maxPointsText.setCharacterSize(25);
    this->maxPointsText.setPosition(Vector2f(380,425));
    int allMaxPoints = 0;
    ifstream Plik("./maxPoints.txt");
    Plik >> allMaxPoints;
    Plik.close();
    auto s = to_string(allMaxPoints);
    this->maxPointsText.setString("Twoj najlepszy dotychczasowy wynik to: " + s);
}

Interface::Interface()
{
    this->initWindow();
    this->initFonts();
    this->initText();
    this->initButton();
}

Interface::~Interface()
{
    delete this->window;
}

const bool Interface::running() const
{
    return this->window->isOpen();
}

void Interface::pollEvents()
{
    while(this->window->pollEvent(this->sfmlEvent))
    {
        switch(this->sfmlEvent.type)
        {
        case Event::Closed:
            this->window->close();
            break;
        case Event::KeyPressed:
            if(this->sfmlEvent.key.code == Keyboard::Escape){
                this->window->close();
                break;
            }
        }
        break;
    }
}

const bool Interface::update()
{
    this->pollEvents();
    return this->button.isButtonPressed(this->window);
}

void Interface::renderGui(RenderTarget* target)
{
    target->draw(this->guiText);
    target->draw(this->standardText);
    target->draw(this->maxPointsText);
    target->draw(this->buttonText);
}

void Interface::render()
{
    this->window->clear(Color::White);
    this->window->draw(sprajt);
    this->window->draw(this->button.getButton());
    this->renderGui(this->window);
    this->window->display();
}
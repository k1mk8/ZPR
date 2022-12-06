#include "Interface.h"

using namespace std;
void Interface::initWindow()
{
    texture.loadFromFile("tlo.png");
    sprajt.setTexture(texture);
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
    this->button.setSize(Vector2f(125, 65));
    this->button.setFillColor(Color::Cyan );
    this->button.setPosition(Vector2f(560,500));
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

    this->standardText.setFont(this->font);
    this->standardText.setFillColor(Color::Black);
    this->standardText.setCharacterSize(25);
    this->standardText.setPosition(Vector2f(590,515));
    this->standardText.setString("Graj!");
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

const bool Interface::isButtonPressed() const
{
    IntRect rect(button.getPosition().x, button.getPosition().y, button.getGlobalBounds().width, button.getGlobalBounds().height);
        if (rect.contains(Mouse::getPosition(*window)) && (sf::Mouse::isButtonPressed(sf::Mouse::Left))) {
                return true;
        }
        return false; 
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
            }
        }
        break;
    }
}

const bool Interface::update()
{
    this->pollEvents();
    return this->isButtonPressed();
}

void Interface::renderGui(RenderTarget* target)
{
    target->draw(this->standardText);
    target->draw(this->buttonText);
}

void Interface::render()
{
    this->window->clear(Color::White);
    this->window->draw(sprajt);
    this->window->draw(button);
    this->renderGui(this->window);
    this->window->display();
}
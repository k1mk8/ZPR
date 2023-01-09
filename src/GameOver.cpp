#include <GameOver.h>

void GameOver::initWindow()
{
    this->texture.loadFromFile("images/game_over.png");
    this->sprite.setTexture(texture);
    this->videoMode = VideoMode(1920, 1080);
    this->window = new RenderWindow(this->videoMode, "Agario", Style::Close | Style::Titlebar);
    this->window->clear(Color::White);
    this->window->setFramerateLimit(60);
}

void GameOver::initButton()
{
    this->buttonYes = Button(Vector2f(125, 60), Color::Transparent, Vector2f(800, 750));
    this->buttonNo = Button(Vector2f(125, 60), Color::Transparent, Vector2f(1000, 750));
}

GameOver::GameOver()
{
    this->initWindow();
    this->initButton();
}

GameOver::~GameOver()
{
    delete this->window;
}

const int GameOver::buttonPressed() const
{
    int choice = 0;
    if(this->buttonYes.isButtonPressed(window)){
        choice = 1;
    }
    else if(this->buttonNo.isButtonPressed(window)){
        choice = 2;
    }
    return choice;
}

void GameOver::pollEvents()
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

const bool GameOver::update()
{
    this->pollEvents();
    return this->buttonPressed();
}

void GameOver::render()
{
    this->window->clear(Color::White);
    this->window->draw(sprite);
    this->window->draw(buttonYes.getButton());
    this->window->draw(buttonNo.getButton());
    this->window->display();
}
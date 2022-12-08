#include <GameOver.h>
#include <Button.h>

void GameOver::initWindow()
{
    this->texture.loadFromFile("game_over.png");
    this->sprajt.setTexture(texture);
    this->videoMode = VideoMode(1920.f, 1080.f);
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

void GameOver::render()
{
    this->window->clear(Color::White);
    this->window->draw(sprajt);
    this->window->draw(buttonYes.getButton());
    this->window->draw(buttonNo.getButton());
    this->window->display();
}
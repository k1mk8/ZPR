#include <GameOver.h>

void GameOver::initWindow()
{
    /// @brief inifcuje początkowe wartości interfejsu
    this->texture.loadFromFile("images/game_over.png");
    this->sprite.setTexture(texture);
    this->videoMode = VideoMode(1920, 1080);
    this->window = new RenderWindow(this->videoMode, "Agario", Style::Close | Style::Titlebar);
    this->window->clear(Color::White);
    this->window->setFramerateLimit(60);
}

void GameOver::initButton()
{
    /// @brief iniciuje przyciski do zakończenia gry
    this->buttonYes = Button(Vector2f(125, 60), Color::Transparent, Vector2f(800, 750));
    this->buttonNo = Button(Vector2f(125, 60), Color::Transparent, Vector2f(1000, 750));
}

GameOver::GameOver()
{
    /// @brief konstruktor domyślny
    this->initWindow();
    this->initButton();
}

GameOver::~GameOver()
{
    /// @brief destruktor domyślny
    delete this->window;
}

const int GameOver::buttonPressed() const
{
    /// @brief funkcja sprawdzająca, jaki przycisk jest wciskany
    /// @return informacja na temat wciśniętego przycisku
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
    /// @brief funkcja sprawdzająca czy okno ma być zamknięte
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
    /// @brief funkcja sprawdzająca czy wydarzyły się jakieś interakcje od użytkownika
    /// @return czy przycisk rozpoczęcia gry został wciśnięty
    this->pollEvents();
    return this->buttonPressed();
}

void GameOver::render()
{
    /// @brief funkcja renderująca i wyświetlająca okno
    this->window->clear(Color::White);
    this->window->draw(sprite);
    this->window->draw(buttonYes.getButton());
    this->window->draw(buttonNo.getButton());
    this->window->display();
}
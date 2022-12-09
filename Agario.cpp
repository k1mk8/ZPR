#include "Game.h"
#include "GameOver.h"

int main()
{
    srand(static_cast<unsigned>(time(0)));
    int choice = 0;
    while(true)
    {
        Interface interface;
        bool change = false;
        while(interface.running() && change == false)
        {
            change = interface.update();
            interface.render();
        }
        interface.~Interface();
        Game game;
        while(game.running())
        {
            game.update();
            game.render();
        }
        game.~Game();
        GameOver gameOver;
        while(choice == 0)
        {
            choice = gameOver.buttonPressed();
            gameOver.render();
        }
        if(choice == 1){
            choice = 0;
        }
        else if(choice == 2){
            gameOver.~GameOver();
            return 0;
        }
        gameOver.~GameOver();
    }
    return 0;
}
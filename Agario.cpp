#include "Game.h"
#include "GameOver.h"

int main()
{
    srand(static_cast<unsigned>(time(0)));
    int choice = 0;
    while(true)
    {
        Interface interface;
        int change = 0;
        int speed = 10;
        while(interface.running() && change != 1)
        {
            change = interface.update();
            interface.render();
            if(change == 2)
                speed = 5;
            if(change == 3)
                speed = 10;
            if(change == 4)
                speed = 20;
        }
        Game game(speed);
        while(game.running())
        {
            game.update();
            game.render();
        }
        GameOver gameOver;
        while(choice == 0)
        {
            choice = gameOver.update();
            gameOver.render();
        }
        if(choice == 1){
            choice = 0;
        }
        else if(choice == 2){
            break;
        }
    }
    return 0;
}
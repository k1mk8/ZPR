/*
    @file Agario.cc
    @author Karol Kasperek, Szymon Dyszewski
    @brief plik zawierający główną pętlę gry
*/

#include "Game.h"
#include "GameOver.h"
#include "Interface.h"

using namespace std;
using namespace sf;

int main()
{
    srand(static_cast<unsigned>(time(0)));
    int choice = 0;
    while(true)
    {
        Interface interface; // stworzenie interfejsu
        int change = 0;
        int speed = 10;
        while(interface.running() && change != 1) // dopóki działa intefejs
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
        Game game(speed); // tworzenie gry z wybraną przez użytkownika prędkością
        while(game.running()) // dopóki działa okno gry
        {
            game.update();
            game.render();
        }
        GameOver gameOver; // stworzenie okna końcowego
        while(choice == 0) // dopóki działa okno
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
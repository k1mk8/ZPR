/*
    @file Game.h
    @author Karol Kasperek, Szymon Dyszewski
    @brief plik zawierający deklarację klasy Game
*/

#ifndef Game_H
#define Game_H

#include<iostream>
#include<ctime>
#include<vector>
#include<sstream>
#include<fstream>

#include "Bot.h"
#include "BasicWindow.h"

class Game : public BasicWindow
{
/// @brief klasa odpowiedzialna za symulację i obsługę rozgrywki i interakcji
private:
    bool end_game_; // czy koniec gry
    std::vector<Player> players_; // wektor graczy
    std::vector<Bot> bots_; // wektor botów
    std::vector<StaticPoints> static_points_; // punkty statyczne na mapie
    sf::Text gui_text_; // tekst GUI
    sf::Text table_; //tekst wyników
    const int MAX_STATIC_POINTS_ = 1000; // maksymalna ilość obiektó statycznych
    int total_points_; // sumaryczna ilośc punktów
    int max_points_ = 10; // maksymalna ilość punktów w grze
    const int MAX_BOTS_ = 10; // maksymalna ilość graczy w grze
    void variables(const int& speed); // inicjowanie zmiennych
    void initWindow(); // inicjowanie okna
    void initText(); // inicjowanie tekstu
    void initBots(const float& speed); // inicjowanie botów
    void zoomOut(); // oddalanie obrazu
public:
    Game(const int& speed); // konstruktor domyślny
    const bool& getEndGame() const; // zwraca informację o końcu gry
    const int& getTotalPoints() const; // zwraca sumaryczną ilośc punktów
    int calculateTotalPoints(); // obliczanie sumy punktów
    void spawnStaticPoints(); // tworzenie obiektów statycznych
    int randPointType(); // losowanie obiektów do stworzenia
    void updatePlayer(); // uaktualnianie graczy
    void updateCollision(); // sprawdzanie kolizji
    template<typename T, typename U>
    void updateCollisionForObject(T& participant, std::vector<U>& objects, std::vector<T>& participants); // sprawdzanie kolizji
    void updateTable(std::stringstream& ss, std::stringstream& ss2, sf::Vector2f& view_center); // aktualizowanie tablicy z wynikami
    void updateGui(); // uaktualnianie GUI
    void updateMaxPoints(); // uaktualnianie maksymalnej liczby punktów w grze
    void updateBot(); // wykonanie aktualizacji ruchow
    int update(); // uaktualnianie wydarzeń na mapie
    void calculateStaticPoints(); // obliczanie pozycji punktów statycznych
    void renderGui(sf::RenderTarget* target); // wyświetlanie GUI
    void render(); // renderowanie i wyświetlanie mapy oraz obiektów
};
#endif
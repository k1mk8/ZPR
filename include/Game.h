#include<iostream>
#include<ctime>
#include<vector>
#include<sstream>
#include<fstream>

#include "StaticPoints.h"

using namespace sf;
using namespace std;

class Game
{
private:
    VideoMode videoMode;
    RenderWindow* window;
    bool endGame;
    Event sfmlEvent;


    vector<Player> players;

    Font font;
    Text guiText;
    Text endGameText;

    vector<StaticPoints> staticPoints;
    float spawnTimerMax;
    float spawnTimer;
    int maxStaticPoints;
    int totalPoints;
    int maxPoints = 10;

    void variables();
    void initWindow();
    void initFonts();
    void initText();
public:
    Game();
    ~Game();

    const bool& getEndGame() const;

    const bool running() const;
    void pollEvents();

    void calculateTotalPoints();
    void spawnStaticPoints();
    const int randPointType() const;
    void updatePlayer();
    void updateCollision();
    void updateGui();
    void updateMaxPoints();
    void update();

    void renderGui(RenderTarget* target);
    void render();
};
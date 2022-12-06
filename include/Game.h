#include<iostream>
#include<ctime>
#include<vector>
#include<sstream>

#include "Player.h"
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

    Player player;

    Font font;
    Text guiText;
    Text endGameText;

    vector<StaticPoints> staticPoints;
    float spawnTimerMax;
    float spawnTimer;
    int maxStaticPoints;
    int totalPoints;

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
    void update();

    void renderGui(RenderTarget* target);
    void render();
};
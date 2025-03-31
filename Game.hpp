#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <vector>

struct convexShapeObstacle {
    sf::ConvexShape obs_shape;
    int x, y;
};

struct treasureStructure {
    sf::Sprite treasureSprite;
};

struct objectSprite {
    sf::Sprite sprite;
    int x, y;
};

struct parabolicObject {
    sf::Sprite sprite;
    int x, y;
    bool up;
};

class Game {
public:
    Game(sf::RenderWindow& window, int level); // Add level2Mode parameter
    int run();

private:
    void updateConvexShapeObstacles();
    bool checkCollisionConvexShapeVector();
    bool checkCollision(const sf::Sprite& sprite1, const sf::Sprite& sprite2);
    void updateScore();
    convexShapeObstacle createObstacle();


    float parabolicMovement(float x);
    float sineMovement(float x);
    void updateLevel2Obstacles();

    objectSprite exponenetialSineObstacle;



    float sec(float x);
    void updateLevel3Obstacles();
    float exponentialSineObstacleMovement(float x);
    void createTreasure();

    int x_of_secObstacle;
    float secObstacleMovement(float x);
    objectSprite secObstacle;




    sf::RenderWindow& window;
    sf::Font font;
    std::vector<convexShapeObstacle> obstacles;
    sf::Text scoreText;
    sf::Texture submarineTexture;
    sf::Texture treasureTexture;
    sf::Texture octupusTexture;
    sf::Texture seaUrchinTexture;
    sf::Texture crabTexture;
    sf::Texture laternFishTexture;
    sf::Texture backgroundtexture;
    sf::Sprite backgroundsprite;




    float obstacleSpeed;
    int score;
    bool isGameOver;
    int level;  // New variable to track mode
    objectSprite player;
    treasureStructure treasure;

    parabolicObject parabolicObstacle;
    objectSprite sineObstacle;






};

#endif
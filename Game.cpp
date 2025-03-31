#include "Game.hpp"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>

const int WIDTH = 800;
const int HEIGHT = 800;
const int BALL_SIZE = 20;
const int OBSTACLE_SIZE = 5;
const int INITIAL_OBSTACLE_SPEED = 4;

Game::Game(sf::RenderWindow& window, int level) : window(window), obstacleSpeed(INITIAL_OBSTACLE_SPEED), score(0), isGameOver(false), level(level) {
    srand(static_cast<unsigned int>(time(0)));

    if (!font.loadFromFile("./Bangers.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        exit(-1);
    }
    backgroundtexture.loadFromFile("backgroundsea.png");
    backgroundsprite.setTexture(backgroundtexture);
    backgroundsprite.setScale(0.245f, 0.245f);

    submarineTexture.loadFromFile("submarine.png");
    player.sprite.setTexture(submarineTexture);
    player.sprite.setPosition(0, HEIGHT / 2);
    player.sprite.setScale(0.6f, 0.6f);


    if (level == 2 || level == 3) {
        treasureTexture.loadFromFile("treasurechest.png");
        treasure.treasureSprite.setTexture(treasureTexture);
        treasure.treasureSprite.setScale(0.3f, 0.3f);
        createTreasure();

    }




    scoreText.setFont(font);
    scoreText.setCharacterSize(30);
    scoreText.setFillColor(sf::Color::Red);



    if (level == 2) {
        if (!crabTexture.loadFromFile("crab.png") || !seaUrchinTexture.loadFromFile("urchin.png")) {
            std::cerr << "Failed to load sprite texture" << std::endl;
            exit(-1);
        }
        sineObstacle.sprite.setTexture(seaUrchinTexture);
        sineObstacle.sprite.setPosition(WIDTH, HEIGHT / 2);
        sineObstacle.sprite.setScale(0.3f, 0.3f);

        parabolicObstacle.sprite.setTexture(crabTexture);
        parabolicObstacle.sprite.setPosition(WIDTH, HEIGHT / 2);
        parabolicObstacle.sprite.setScale(0.3f, 0.3f);
        parabolicObstacle.up = true;



        sineObstacle.x = 400 + std::rand() % (800 - 400 + 1);
        parabolicObstacle.x = 400 + std::rand() % (800 - 400 + 1);
    }

    if (level == 3) {
        if (!octupusTexture.loadFromFile("oct.png") || !laternFishTexture.loadFromFile("fish.png")) {
            std::cerr << "Failed to load sprite texture" << std::endl;
            exit(-1);
        }
        secObstacle.sprite.setTexture(octupusTexture);
        secObstacle.sprite.setPosition(WIDTH, HEIGHT / 2);
        secObstacle.sprite.setScale(0.3f, 0.3f);
        secObstacle.x = 400 + std::rand() % (800 - 400 + 1);

        exponenetialSineObstacle.sprite.setTexture(laternFishTexture);
        exponenetialSineObstacle.sprite.setPosition(WIDTH, HEIGHT / 2);
        exponenetialSineObstacle.sprite.setScale(0.3f, 0.3f);
        exponenetialSineObstacle.x = 400 + std::rand() % (800 - 400 + 1);
    }


}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

convexShapeObstacle Game::createObstacle() {
    convexShapeObstacle obstacle;
    obstacle.x = WIDTH;
    obstacle.y = rand() % (HEIGHT);
    obstacle.obs_shape.setPointCount(3); // A triangle has 3 points

    obstacle.obs_shape.setPoint(0, sf::Vector2f(0, 0));
    obstacle.obs_shape.setPoint(1, sf::Vector2f(OBSTACLE_SIZE / 2, OBSTACLE_SIZE));
    obstacle.obs_shape.setPoint(2, sf::Vector2f(OBSTACLE_SIZE, 0));

    obstacle.obs_shape.setFillColor(sf::Color(255, 165, 0));
    obstacle.obs_shape.setScale(sf::Vector2f(OBSTACLE_SIZE, OBSTACLE_SIZE));
    obstacle.obs_shape.setPosition(obstacle.x, obstacle.y);
    return obstacle;
}


// Update the collision check for the player and obstacles
bool Game::checkCollisionConvexShapeVector() {
    for (const auto& obstacle : obstacles) {
        if (player.sprite.getGlobalBounds().intersects(obstacle.obs_shape.getGlobalBounds())) {
              return true;
        }
    }
    return false;
}


void Game::updateConvexShapeObstacles() {
    for (auto& obstacle : obstacles) {
        obstacle.x -= obstacleSpeed;
        obstacle.obs_shape.setPosition(obstacle.x, obstacle.y);
        obstacle.obs_shape.rotate(1.0f);
    }

    obstacles.erase(
        std::remove_if(obstacles.begin(), obstacles.end(), [](const convexShapeObstacle& obs) { return obs.obs_shape.getPosition().x + OBSTACLE_SIZE < 0; }),
        obstacles.end()
    );

    if (rand() % 50 == 0) {
        obstacles.push_back(createObstacle());
    }

    if (score < 500) {
        obstacleSpeed = INITIAL_OBSTACLE_SPEED * pow(1.3, score / 100);
    }
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Game::createTreasure() {
    treasure.treasureSprite.setPosition(std::rand() % (700) + 1, std::rand() % (700) + 1);
}


void Game::updateLevel2Obstacles() {

    sineObstacle.sprite.setPosition(sineObstacle.x, sineMovement(sineObstacle.x));

    //sineObstacle.sprite.rotate(1.0f);
    sineObstacle.x -= 3;
    if (sineObstacle.x < 0)
        sineObstacle.x = 400 + std::rand() % (800 - 400 + 1);

    ////////////////////////////////////////////////////////////////////

    parabolicObstacle.sprite.setPosition(parabolicObstacle.x, parabolicMovement(parabolicObstacle.x));// parabolicMovement(parabolicObstacle.x));


    if (parabolicObstacle.up == true)
        parabolicObstacle.x -= 4;
    else
        parabolicObstacle.x += 4;


    if (parabolicObstacle.x < 0)
        parabolicObstacle.up = !parabolicObstacle.up;


    if (parabolicObstacle.up == false && parabolicObstacle.x > 800) {
        parabolicObstacle.up = !parabolicObstacle.up;
        parabolicObstacle.x = 400 + std::rand() % (800 - 400 + 1);
    }

   // std::cerr << parabolicObstacle.x << " " << parabolicObstacle.up << std::endl;
}


float Game::sineMovement(float x) {

    if (x <= 400)
        return 400 * (1 - sin(3.1415 / 400 * x));

    else {
        return 400 + ((abs(sin((3.1415 / 400) * (x - 400)))) * 400);
    }

}
float Game::parabolicMovement(float x) {


    if (parabolicObstacle.up == true)
        return (400 - sqrt(2.4997 * (80 * x + 6)));

    else
        return sqrt(2.4997 * (80 * x + 6)) + 400;


}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Game::checkCollision(const sf::Sprite& sprite1, const sf::Sprite& sprite2) {
    return sprite1.getGlobalBounds().intersects(sprite2.getGlobalBounds());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Level 3

float Game::sec(float x) {
    if (cos(x) == 0) return 1;
    return 1 / cos(x);
}

float Game::secObstacleMovement(float x) {

    float temp = sec((3.141 / 400) * 3 * x) / 6;

    if (temp > 0) {
        return temp * 400;
    }
    else {
        return 400 * (1 - abs(temp)) + 400;
    }

}

float Game::exponentialSineObstacleMovement(float x) {
    return HEIGHT / 2 + 100 * sin(0.01 * x) * exp(-0.001 * x);
}

void Game::updateLevel3Obstacles() {

    secObstacle.x -= 1;
    if (secObstacle.x < 0)
        secObstacle.x = 400 + std::rand() % (800 - 400 + 1);

    secObstacle.sprite.setPosition(secObstacle.x, secObstacleMovement(secObstacle.x));


    exponenetialSineObstacle.x -= 3;
    if (exponenetialSineObstacle.x < 0)
        exponenetialSineObstacle.x = 400 + std::rand() % (800 - 400 + 1);

    exponenetialSineObstacle.sprite.setPosition(exponenetialSineObstacle.x, exponentialSineObstacleMovement(exponenetialSineObstacle.x));





}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Game::updateScore() {
    score++;
    scoreText.setString("Score: " + std::to_string(score));
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool isPaused = false;
bool isKeyPressed = false;
int Game::run() {
    // Print player and obstacle positions at the start
    

    while (window.isOpen() && !isGameOver) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
std::        cout << isPaused<<"   below\n";
        //if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
        //    if (isPaused == true) {
        //        isPaused=false; // Skip further updates/rendering
        //    }
        //    else
        //        isPaused=true;
        //    std::cout << "Game Paused: " << isPaused << std::endl; // Debugging output
        //}
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P && !isKeyPressed) {
            if (isPaused == true) {
                        isPaused=false; // Skip further updates/rendering
                    }
                    else
                        isPaused=true;
            std::cout << "Game Paused: " << isPaused << std::endl;
            isKeyPressed = true;  // Set the flag to prevent toggling until key is released
        }

        // Reset the key pressed flag when the key is released
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::P) {
            isKeyPressed = false;
        }
    
    
       if (isPaused==true) {
           continue; // Skip further updates/rendering
      }
        window.clear();
        window.draw(backgroundsprite);


        // Handle player movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && player.sprite.getPosition().y > 0) {
            player.sprite.move(0, -6);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && player.sprite.getPosition().y + BALL_SIZE < HEIGHT) {
            player.sprite.move(0, 6);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && player.sprite.getPosition().x < 700) {
            player.sprite.move(6, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && player.sprite.getPosition().x > 0) {
            player.sprite.move(-6, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            isGameOver==true;
            break;
            std::cout << "Game Over: " << isPaused << std::endl; // Debugging output
        }


        ///////////////////////////         level 1      /////////////////////////////////// 

        if (level == 1) {
            updateConvexShapeObstacles();

            for (const auto& obstacle : obstacles) {
                window.draw(obstacle.obs_shape);
            }
            if (checkCollisionConvexShapeVector()) {
                isGameOver = true;
            }
            updateScore();

        }

        ///////////////////////            level 2     ///////////////////////////////////////////////       

            // Update score


        if (level == 2) {

            updateLevel2Obstacles();
            if (checkCollision(player.sprite, parabolicObstacle.sprite) || checkCollision(player.sprite, sineObstacle.sprite)) {
                isGameOver = true;
            }
            window.draw(sineObstacle.sprite);
            window.draw(parabolicObstacle.sprite);
        }

        ////////////////////////        level 3              ///////////////////////////
        if (level == 3) {

            updateLevel3Obstacles();
            if (checkCollision(player.sprite, secObstacle.sprite) || checkCollision(player.sprite, exponenetialSineObstacle.sprite)) {
                isGameOver = true;
            }
            window.draw(exponenetialSineObstacle.sprite);
            window.draw(secObstacle.sprite);

        }
        ///////////////////////////  level2 and 3   ///////////////////////////////////////
        if (level == 2 || level == 3) {

            if (checkCollision(player.sprite, treasure.treasureSprite)) {
                createTreasure();
                updateScore();

            }

        }

        //  treasure.treasureSprite.setPosition(45, 45);
        window.draw(treasure.treasureSprite);
        window.draw(player.sprite);
        scoreText.setPosition(10, 10);
        window.draw(scoreText);
        window.display();
        sf::sleep(sf::milliseconds(10));

    }

    sf::sleep(sf::seconds(.5f));

    // Display game over screen
    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setString("Game Over! \nYour score:\n     " + std::to_string(score));

    // Calculate the bounds of the text
    sf::FloatRect textBounds = gameOverText.getLocalBounds();

    // Set the position to center the text
    gameOverText.setPosition(
        (WIDTH - textBounds.width) / 2 - textBounds.left,
        (HEIGHT - textBounds.height) / 2 - textBounds.top
    );

    window.clear();
    window.draw(backgroundsprite);
    window.draw(gameOverText);
    window.display();
    sf::sleep(sf::seconds(1.75f));

    return 0;
}
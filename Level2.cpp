//#include "Level2.hpp"
//#include<iostream>
//#include<cmath>
//#include<SFML/Graphics.hpp>
//const int WIDTH = 800;
//const int HEIGHT = 800;
//const int BALL_SIZE = 20;
//
//Level2::Level2(sf::RenderWindow& window) : window(window), isGameOver(false),x_of_sineObstacle(1), x_of_parabolicObstacle(800) {
//    srand(static_cast<unsigned int>(time(0)));
//    if (!font.loadFromFile("./PressStart2P-Regular.ttf")) {
//        std::cerr << "Failed to load font" << std::endl;  
//        exit(-1);
//    }
//    if (!playerTexture.loadFromFile("D:\\visualstudio\\Project1\\ball.png")) {
//        std::cerr << "Failed to load sprite texture" << std::endl;
//        exit(-1);
//    }
//   
//
//    player.sprite.setTexture(playerTexture);
//    player.sprite.setPosition(50, HEIGHT / 2);
//    player.sprite.setScale(0.05f, 0.05f);
//    if (!obstacleTexture.loadFromFile("D:\\visualstudio\\Project1\\obstacle.png")) {
//        std::cerr << "Failed to load sprite texture" << std::endl;
//        exit(-1);
//    }
//    sineObstacle.sprite.setTexture(obstacleTexture);
//    sineObstacle.sprite.setPosition(WIDTH, HEIGHT / 2);
//    sineObstacle.sprite.setScale(0.01f, 0.01f);
//
//    parabolicObstacle.sprite.setTexture(obstacleTexture);
//    parabolicObstacle.sprite.setPosition(WIDTH, HEIGHT / 2);
//    parabolicObstacle.sprite.setScale(0.01f, 0.01f);
//    parabolicObstacle.up = true;
//
//}
//void Level2:: updateObstacles() {
//    
//    sineObstacle.sprite.setPosition(x_of_sineObstacle, sineMovement(x_of_sineObstacle));
//    
//    sineObstacle.sprite.rotate(1.0f);
//    x_of_sineObstacle += 1;
//    if (x_of_sineObstacle > 800)
//        x_of_sineObstacle = 1;
//
//    ////////////////////////////////////////////////////////////////////
//    
//    parabolicObstacle.sprite.setPosition(x_of_parabolicObstacle, parabolicMovement(x_of_parabolicObstacle));// parabolicMovement(x_of_parabolicObstacle));
//    
//
//    if (parabolicObstacle.up==true)
//        x_of_parabolicObstacle -= 1;
//    else
//        x_of_parabolicObstacle += 1;
//
//
//    if (x_of_parabolicObstacle == 0)
//        parabolicObstacle.up = !parabolicObstacle.up;
//
//
//    if (parabolicObstacle.up == false && x_of_parabolicObstacle > 800) {
//        parabolicObstacle.up = !parabolicObstacle.up;
//        x_of_parabolicObstacle = 800;
//    }
//
//    std::cerr << x_of_parabolicObstacle << " "<<parabolicObstacle.up<< std::endl;
//}
//
//bool Level2::checkCollision(const sf::Sprite& sprite1, const sf::Sprite& sprite2) {
//    return sprite1.getGlobalBounds().intersects(sprite2.getGlobalBounds());
//}
//
//float Level2::sineMovement(float x) {
//
//    if (x<=400)
//    return 400 * (1 - sin(3.1415 / 400 * x));
//
//    else {
//        return 400 + ((abs(sin((3.1415 / 400) * (x - 400)))) * 400);
//    }
//
//}
//float Level2::parabolicMovement(float x) {
//    //if (x<=400)
//
//    if (parabolicObstacle.up == true)
//    return (400 - sqrt(2.4997 * (80 * x + 6)));
//    
//    else
//       return sqrt(2.4997 * (80 * x + 6))+400;
//
// 
//}
//
//int Level2::run() {
//    window.clear();
//    window.display();
//    
//    
//    while (window.isOpen() && !isGameOver) {
//
//        sf::Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed) {
//                window.close();
//            }
//
//        }
//
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && player.sprite.getPosition().y > 0.0) {
//            player.sprite.move(0, -5);
//
//        }
//        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
//            player.sprite.getPosition().y + BALL_SIZE < HEIGHT){
//            player.sprite.move(0, 5);
//            }
//
//        if (checkCollision(player.sprite, sineObstacle.sprite)) {
//            std::cerr << "Collision" << std::endl;
//        }
//
//        updateObstacles();
//
//
//        window.clear();
//        window.draw(player.sprite);
//        window.draw(sineObstacle.sprite);
//        window.draw(parabolicObstacle.sprite);
//        window.display();
//        sf::sleep(sf::milliseconds(10));
//
//    }
//    return 0;
//}
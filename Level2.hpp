//#ifndef LEVEL2_HPP
//#define LEVEL2_HPP
//
//#include<SFML/Graphics.hpp>
//
//struct spriteObject {
//	sf::Sprite sprite;
//	int x, y;
//};
//
//struct parabolicObject {
//	sf::Sprite sprite;
//	int x, y;
//	bool up;
//};
//
//class Level2 {
//
//public:
//
//	Level2(sf::RenderWindow& window);
//	int run();
//
//
//private:
//	float parabolicMovement(float x);
//	float sineMovement(float x);
//	void updateObstacles();
//	bool checkCollision(const sf::Sprite& sprite1, const sf::Sprite& sprite2);
//	
//
//	sf::RenderWindow& window;
//	sf::Font font;
//	sf::Text scoreText;
//	sf::Texture playerTexture;
//	sf::Texture obstacleTexture;
//
//
//
//	spriteObject player;
//	spriteObject sineObstacle;
//	
//	bool isGameOver;
//	int x_of_sineObstacle;
//	int x_of_parabolicObstacle;
//
//	parabolicObject parabolicObstacle;
//
//};
//
//
//
//
//#endif
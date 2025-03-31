#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#include "Menu.hpp"
#include "Game.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 800), "Menu Example");

    sf::Music background;

    if (!background.openFromFile("back.mp3")) {
        std::cerr << "Failed to open sound file!" << std::endl;
        return -1;
    }
    background.setLoop(true);
    background.play();
    background.setVolume(10.0f);

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::Black);
        window.display();


        // Show the menu and get the result
        Menu menu(window);
        int result = menu.run();

        if (result == 0) {
            // Start Game without obs3 (level 1)
            Game game(window, 1); // false means no obs3 (level 1)
            game.run();
        }
        else if (result == 1) {
            Game game(window, 2); // true means with obs3 (level 2)
            game.run();
        }
        else if (result == 2) {
            // Start Game with obs3 (level 2)
            Game game(window, 3); // true means with obs3 (level 2)
            game.run();
        }
    }

    return 0;
}
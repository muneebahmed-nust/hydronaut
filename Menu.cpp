#include "Menu.hpp"

const int numberOfoptions = 3;

Menu::Menu(sf::RenderWindow& window) : window(window), selectedIndex(0) {
    if (!font.loadFromFile("./Bangers.ttf")) {
        std::cerr << "Error loading font" << std::endl;
        exit(-1);
    }
    backgroundtexture.loadFromFile("backgroundsea.png");
    backgroundsprite.setTexture(backgroundtexture);
    backgroundsprite.setScale(0.245f, 0.245f);

    menu[0].setString("Obstacles Unleashed");
    menu[1].setString("Arc of Chaos");
    menu[2].setString("Waves Of Danger");

    for (int i = 0; i < numberOfoptions; i++) {
        menu[i].setFont(font);
        menu[i].setCharacterSize(50);
        menu[i].setFillColor(sf::Color::Red);
    }

    sf::FloatRect bounds[numberOfoptions];
    float menuSpacing = 50.0f;
    float totalMenuHeight = (3 - 1) * menuSpacing;
    for (int i = 0; i < numberOfoptions; i++) {
        bounds[i] = menu[i].getLocalBounds();
        totalMenuHeight += bounds[i].height;
    }

    float startY = (window.getSize().y - totalMenuHeight) / 2.0f;
    for (int i = 0; i < numberOfoptions; i++) {
        bounds[i] = menu[i].getLocalBounds();
        menu[i].setOrigin(bounds[i].width / 2, bounds[i].height / 2);
        menu[i].setPosition(window.getSize().x / 2, startY + i * (bounds[i].height + menuSpacing));
    }

    highlight.setFillColor(sf::Color(255, 255, 255, 140));
    updateHighlight();
}

void Menu::updateHighlight() {
    sf::FloatRect bounds = menu[selectedIndex].getGlobalBounds();
    highlight.setSize({ bounds.width + 20, bounds.height + 10 });
    highlight.setPosition(bounds.left - 10, bounds.top - 5);
}

int Menu::run() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up) {
                    selectedIndex = (selectedIndex - 1 + numberOfoptions) % numberOfoptions;  // Adjusted to allow numberOfoptions menu options
                }
                else if (event.key.code == sf::Keyboard::Down) {
                    selectedIndex = (selectedIndex + 1) % numberOfoptions;
                }
                else if (event.key.code == sf::Keyboard::Enter) {
                    if (selectedIndex == 0) {
                        std::cout << "Game starting..." << std::endl;
                        return 0; // Return 1 to indicate "START" selection
                    }
                    else if (selectedIndex == 1) {
                        std::cout << "Exiting game..." << std::endl;
                        return 1; // Exit game
                    }
                    else if (selectedIndex == 2) {
                        std::cout << "Starting LEVEL 2..." << std::endl;
                        return 2; // Return 2 to indicate "LEVEL 2" selection
                    }
                }
                updateHighlight();
            }
        }

        window.clear(sf::Color::Black);
        window.draw(backgroundsprite);
        window.draw(highlight);
        for (int i = 0; i < numberOfoptions; i++) {
            window.draw(menu[i]);
        }
        window.display();
    }
}
#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

class Menu {
public:
    Menu(sf::RenderWindow& window);
    int run();

private:
    void updateHighlight();


    sf::RenderWindow& window;
    sf::Font font;
    sf::Text menu[4];
    sf::RectangleShape highlight;
    sf::Texture backgroundtexture;
    sf::Sprite backgroundsprite;
    int selectedIndex;

};

#endif
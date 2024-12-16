#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

class Sidebar {
public:
    Sidebar(float width, float height);

    void addItem(const std::string& item);
    void updateMouseCoordinates(const sf::RenderWindow &window);
    void handleTextInput(sf::Event event);
    void draw(sf::RenderWindow& window);

private:
    sf::RectangleShape background;
    sf::Text mouseCoordinatesText;
    sf::Font font;
    sf::Text inputText;
    vector<sf::Text> items;
    string inputString;
    float _width;
    float _height;
};

#endif // SIDEBAR_H
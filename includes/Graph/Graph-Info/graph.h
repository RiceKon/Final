#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


#include "../Plot/plot.h"
#include "../Plot/CoordinateTranslator.h"
#include "../../tokenizer/constants.h"

using namespace std;

class Graph {
public:
    Graph();
    Graph(const sf::Vector2f& origin, const sf::Vector2f& scale) : origin(origin), scale(scale) {}
    void draw(sf::RenderWindow& window);
    
    sf::Vector2f zoom(sf::Event event, sf::Vector2f &Domain);
private:

    void drawGridLines(sf::RenderWindow& window, const sf::Vector2f& origin, const sf::Vector2f& scale);
    void drawOriginLines(sf::RenderWindow& window, const sf::Vector2f& origin);
    sf::Vector2f origin;
    sf::Vector2f scale;
};

#endif // GRAPH_H

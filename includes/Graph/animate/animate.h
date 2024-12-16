#ifndef ANIMATE_H
#define ANIMATE_H


#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/OpenGL.hpp>
#include <cmath>
#include "../Graph-Info/graph.h"
#include "../../tokenizer/constants.h"

using namespace std;


// Animate: Controls the graphing system
class Animate {
public:
    int scaleX = 100;
    int scaleY = 100;
    double DomRight = 10;
    double DomLeft  = -10;
    Animate();
    void run();
    void drawGridLines(sf::RenderWindow& window, const sf::Vector2f& origin, const sf::Vector2f& scale);

private:
    Graph graph;
    sf::RenderWindow window;
};




#endif // ANIMATE_H
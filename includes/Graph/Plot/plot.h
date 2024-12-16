#ifndef PLOT_H
#define PLOT_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/OpenGL.hpp>

#include "../Graph-Info/graph.h"
#include "CoordinateTranslator.h"
#include "../../RPN/Rpn.h"



class Plot {
public:
    void generatePoints(Queue<Token> postfix, sf::Vector2f Domain, int numPoints);
    const Queue<sf::Vector2f>& getPoints() const;

    vector<sf::Vector2f> getScreenPoints(const sf::Vector2f& origin, const sf::Vector2f& scale);
private:
    Queue<sf::Vector2f> points;
    CoordinateTranslator translator;
    RPN rpn;
};

#endif // PLOT_H

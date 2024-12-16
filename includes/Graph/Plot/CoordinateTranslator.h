#ifndef COORDINATETRANSLATOR_H
#define COORDINATETRANSLATOR_H

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

class CoordinateTranslator {
public:
    sf::Vector2f translate(const sf::Vector2f& point, const sf::Vector2f& origin, const sf::Vector2f& scale) {
        return sf::Vector2f(origin.x + point.x * scale.x, origin.y - point.y * scale.y);
    }
};

#endif // COORDINATETRANSLATOR_H
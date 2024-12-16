#include "plot.h"
#include "../../RPN/Rpn.h"

void Plot::generatePoints(Queue<Token> postfix, sf::Vector2f Domain, int numPoints) {
    points.clear();
    float step = (Domain.x - Domain.y) / (numPoints - 1);

    cout << "Domain: " << Domain.x << " " << Domain.y << endl;

    for (int i = 0; i < numPoints; ++i) {
        float x = Domain.y + i * step;
        double y = rpn.evaluate(postfix, x);
        points.push(sf::Vector2f(x, y));
    }
}

const Queue<sf::Vector2f>& Plot::getPoints() const {
    return points;
}

vector<sf::Vector2f> Plot::getScreenPoints(const sf::Vector2f& origin, const sf::Vector2f& scale) {
    vector<sf::Vector2f> screenPoints;
    for (const auto& point : points) {
        float x = origin.x + point.x * scale.x;
        float y = origin.y - point.y * scale.y;
        if((y >= 0 || y <= HEIGHT) && (x >= 0 || x <= WIDTH)){
            screenPoints.push_back(sf::Vector2f(x, y));
        }
    }
    return screenPoints;
}
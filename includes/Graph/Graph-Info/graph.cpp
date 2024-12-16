#include "graph.h"

Graph::Graph() {
    origin = sf::Vector2f(0, 0);
    scale = sf::Vector2f(1, 1);
}

void Graph::draw(sf::RenderWindow& window) {
    drawGridLines(window, origin, scale);
    drawOriginLines(window, origin);
}

sf::Vector2f Graph::zoom(sf::Event event, sf::Vector2f &Domain) {
    if(event.mouseWheelScroll.delta > 0 && Domain.x > 0.1 && Domain.y < 0.1){
        scale.x += 20;
        scale.y += 20;
        Domain.x -= 0.1;
        Domain.y += 0.1;
    }else if (event.mouseWheelScroll.delta < 0 && scale.x > 20 && scale.y > 20){
        scale.x -= 20;
        scale.y -= 20;
        Domain.x += 0.1;
        Domain.y -= 0.1;
    }
    return scale;
}

void Graph::drawOriginLines(sf::RenderWindow& window, const sf::Vector2f& origin) {
    sf::Color originColor(0, 0, 0); // Black color for origin lines

    // Draw vertical origin line (y-axis)
    sf::Vertex yAxis[] = {
        sf::Vertex(sf::Vector2f(origin.x + CIRCLE_RADIUS * 2, 0), originColor),
        sf::Vertex(sf::Vector2f(origin.x + CIRCLE_RADIUS * 2, window.getSize().y), originColor)
    };
    window.draw(yAxis, 2, sf::Lines);

    // Draw horizontal origin line (x-axis)
    sf::Vertex xAxis[] = {
        sf::Vertex(sf::Vector2f(0, origin.y), originColor),
        sf::Vertex(sf::Vector2f(window.getSize().x, origin.y), originColor)
    };
    window.draw(xAxis, 2, sf::Lines);
}

void Graph::drawGridLines(sf::RenderWindow& window, const sf::Vector2f& origin, const sf::Vector2f& scale) {
    sf::Color gridColor(200, 200, 200); // Light gray color for grid lines

    // Draw vertical grid lines
    for (float x = origin.x; x < window.getSize().x; x += scale.x) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(x + CIRCLE_RADIUS * 2, 0), gridColor),
            sf::Vertex(sf::Vector2f(x + CIRCLE_RADIUS * 2, window.getSize().y), gridColor)
        };
        window.draw(line, 2, sf::Lines);
    }
    for (float x = origin.x; x > 0; x -= scale.x) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(x + CIRCLE_RADIUS * 2, 0), gridColor),
            sf::Vertex(sf::Vector2f(x + CIRCLE_RADIUS * 2, window.getSize().y), gridColor)
        };
        window.draw(line, 2, sf::Lines);
    }

    // Draw horizontal grid lines
    for (float y = origin.y; y < window.getSize().y; y += scale.y) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(0, y), gridColor),
            sf::Vertex(sf::Vector2f(window.getSize().x, y), gridColor)
        };
        window.draw(line, 2, sf::Lines);
    }
    for (float y = origin.y; y > 0; y -= scale.y) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(0, y), gridColor),
            sf::Vertex(sf::Vector2f(window.getSize().x, y), gridColor)
        };
        window.draw(line, 2, sf::Lines);
    }
}
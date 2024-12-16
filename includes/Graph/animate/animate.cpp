#include "animate.h"
#include "../Plot/plot.h"
#include "../sidebar/sidebar.h"
#include <SFML/Graphics.hpp>


Animate::Animate() : window(sf::VideoMode(WIDTH, HEIGHT), "Graph Plotter"), graph(sf::Vector2f((WIDTH + SWIDTH)/2, HEIGHT / 2), sf::Vector2f(scaleX,scaleY)) {}

void Animate::run() {
    
    Plot plot;
    Sidebar sidebar(SWIDTH, SHEIGHT); // Sidebar with width 200 and height 600

    // Example postfix expression for y = sin(x)
    Queue<Token> postfix;
    postfix.push(Token("1"));
    postfix.push(Token("x"));
    postfix.push(Token("/"));
    postfix.push(Token("sin"));

    // Define origin and scale for screen coordinates
    sf::Vector2f origin(float((WIDTH + SWIDTH) / 2), float(HEIGHT/2)); // Center of the window
    sf::Vector2f scale(scaleX, scaleY);    // Scale for x and y axes
    sf::Vector2f Domain(DomRight, DomLeft);


    // Generate points for the plot
    plot.generatePoints(postfix, Domain, 800);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::TextEntered) {
                sidebar.handleTextInput(event);
            }
            if(event.type == sf::Event::MouseWheelScrolled){
                scale = graph.zoom(event, Domain);
                plot.generatePoints(postfix, Domain, 800);
            }
        }

        sidebar.updateMouseCoordinates(window);

        window.clear(sf::Color::White);

        // Get screen points and draw them
        vector<sf::Vector2f> screenPoints = plot.getScreenPoints(origin, scale);
        for (const auto& point : screenPoints) {
            sf::CircleShape shape(CIRCLE_RADIUS);
            shape.setPosition(point);
            shape.setFillColor(sf::Color::Black);
            window.draw(shape);
        }
        // Draw the graph (origin and grid lines)
        graph.draw(window);

        // Draw the sidebar
        sidebar.draw(window);

        window.display();
    }
}


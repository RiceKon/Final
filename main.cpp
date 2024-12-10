#include <iostream>
#include <iomanip>
#include <SFML/Graphics.hpp>

using namespace std;

int main() {
    // Create a window with the title "SFML Application"
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Application");

    // Main loop that continues until the window is closed
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear the window with black color
        window.clear(sf::Color::Black);

        // Draw everything here...

        // End the current frame
        window.display();
    }

    return 0;
}

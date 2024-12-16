#include "sidebar.h"
#include "../../tokenizer/constants.h"
#include <sstream>

Sidebar::Sidebar(float width, float height) : _width(width), _height(height) {
    background.setSize(sf::Vector2f(_width, _height));
    background.setFillColor(sf::Color(200, 200, 200)); // Light gray background

    if (!font.loadFromFile("../../Roboto-Thin.ttf")) {
        // Handle error
        std::cerr << "Failed to load font 'Roboto-Thin.ttf'" << std::endl;
    }

    mouseCoordinatesText.setFont(font);
    mouseCoordinatesText.setCharacterSize(20);
    mouseCoordinatesText.setFillColor(sf::Color::Black);
    mouseCoordinatesText.setPosition(10, height - 30); // Position at the bottom of the sidebar

    inputText.setFont(font);
    inputText.setCharacterSize(20);
    inputText.setFillColor(sf::Color::Black);
    inputText.setPosition(10, 10); // Position above the mouse coordinates
}

void Sidebar::addItem(const std::string& item) {
    sf::Text text;
    text.setFont(font);
    text.setString(item);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::Black);
    text.setPosition(10, 40 + items.size() * 30); // Adjust position based on the number of items
    items.push_back(text);
}
void Sidebar::handleTextInput(sf::Event event) {
    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode == '\b') { // Handle backspace
            if (!inputString.empty()) {
                inputString.pop_back();
            }
        } else if (event.text.unicode < 128) { // Handle ASCII characters
            inputString += static_cast<char>(event.text.unicode);
        }
        inputText.setString(inputString);
    }
}


void Sidebar::updateMouseCoordinates(const sf::RenderWindow &window) {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    stringstream ss;
    ss << "Mouse: (" << mousePosition.x << ", " << mousePosition.y << ")";
    mouseCoordinatesText.setString(ss.str());
}

void Sidebar::draw(sf::RenderWindow& window) {
    window.draw(background);
    for (const auto& item : items) {
        window.draw(item);
    }
    window.draw(mouseCoordinatesText);
    window.draw(inputText);
}
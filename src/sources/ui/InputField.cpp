//
// Created by stefantacu on 10.04.2024.
//

#include "../../headers/ui/InputField.h"

#include <iostream>

#include "../../headers/ui/AssetManager.h"


InputField::InputField() {
    text.setFont(AssetManager::roboto_font);
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::Black);

    inputText = "Enter your name";
    text.setString(inputText);
    isSelected = false;

    outline.setOutlineColor(sf::Color::Black);
    outline.setOutlineThickness(2);
    outline.setSize(sf::Vector2f(70, 70));
}

std::string InputField::getText() {
    return inputText;
}

void InputField::handleEventCurrent(const sf::Event &event) {
    if (event.type == sf::Event::TextEntered) {
        if (isSelected) {
            if (event.text.unicode < 128) {
                if (event.text.unicode == '\b') {
                    // Backspace
                    if (inputText == "Enter your name") return;

                    if (!inputText.empty()) {
                        inputText.pop_back();
                        if (inputText.empty()) {
                            inputText = "Enter your name";
                            text.setFillColor(sf::Color::Red);
                        }
                    }
                } else if (event.text.unicode == '\r') {
                    // Enter
                    // Do something with the entered text, for example:
                    std::cout << "Entered text: " << inputText << std::endl;
                } else {
                    if (inputText == "Enter your name")
                        inputText = "";
                    inputText += static_cast<char>(event.text.unicode);
                    text.setFillColor(sf::Color::Black);
                }
                text.setString(inputText);
            }
        }
    }
}


void InputField::updateCurrent(const sf::Time &delta) {
    outline.setSize(sf::Vector2f(text.getGlobalBounds().width + 20, outline.getSize().y));
}

void InputField::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(outline, states);
    target.draw(text, states);
}

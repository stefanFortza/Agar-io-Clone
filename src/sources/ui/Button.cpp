//
// Created by stefantacu on 14.03.2024.
//

#include <utility>

#include "../../headers/ui/Button.h"

#include <iostream>


Button::Button(std::function<void()> onClick, sf::Color defaultColor,
               sf::Color markColor) : onClick(std::move(onClick)),
                                      defaultColor(defaultColor), markColor(markColor) {
	sf::Text::setFillColor(defaultColor);
}

void Button::handleEvent(const sf::Event &event) {
	switch (event.type) {
		case sf::Event::MouseMoved: {
			// std::cout << event.mouseMove.x << ' ' << event.mouseMove.y << '\n';
			bool contains = getGlobalBounds().contains(
				sf::Vector2f(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y)));
			if (contains && !focused) {
				focused = true;
				sf::Text::setFillColor(markColor);
			} else if (!contains && focused) {
				focused = false;
				sf::Text::setFillColor(defaultColor);
			}
		}

		case sf::Event::MouseButtonReleased: {
			bool contains = getGlobalBounds().contains(
				sf::Vector2f(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)));

			if (contains)
				onClick();
		}
	}
}


Button::~Button() {
}

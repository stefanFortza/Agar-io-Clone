//
// Created by stefantacu on 14.03.2024.
//
#pragma once
#include <functional>
#include <ostream>

#include "SFML/Graphics.hpp"


class Button : public sf::Text {
private:
	std::function<void()> onClick;
	sf::Color defaultColor;
	sf::Color markColor;
	bool focused = false;

public:
	Button(std::function<void()> onClick, sf::Color defaultColor = sf::Color::Black,
	       sf::Color markColor = sf::Color::Blue);

	void handleEvent(const sf::Event &event);

	friend std::ostream &operator<<(std::ostream &os, const Button &obj) {
		std::string str = obj.getString();
		return os << "Button: " << str << "\n";
	}

	~Button();
};


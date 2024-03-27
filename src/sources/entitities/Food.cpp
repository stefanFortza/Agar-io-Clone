//
// Created by stefantacu on 27.03.2024.
//

#include "../../headers/entities/Food.h"

#include <iostream>
#include <random>

int Food::getId() const {
    return m_id;
}

Food::Food(GameStateManager *manager, sf::RenderWindow *window, int id,
           const std::string &name): Entity(manager, window, name), m_shape(15.f), m_id(id) {
    m_shape.setFillColor(sf::Color::Green);
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(-500, 500); // define the range

    // for (int n = 0; n < 40; ++n)
    //     std::cout << distr(gen) << ' '; // generate numbers
    auto x = distr(gen);
    auto y = distr(gen);
    setPosition(sf::Vector2f(x, y));
}

sf::FloatRect Food::getBounds() {
    return getWorldTransform().transformRect(m_shape.getGlobalBounds());
}

void Food::handleEventCurrent(const sf::Event &event) {
}

void Food::updateCurrent(const sf::Time &delta) {
}

void Food::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(m_shape, states);
}

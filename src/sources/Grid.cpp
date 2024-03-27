//
// Created by stefantacu on 08.03.2024.
//

#include "../headers/Grid.hpp"

Grid::Grid(GameStateManager *manager, sf::RenderWindow *window, const std::string &name): SceneNode(
        manager, window, name),
    m_world_size(50000, 50000),
    m_grid_color(220, 220, 220, 255) {
    // vertical
    for (size_t i = 0; i < 100; i++) {
        this->m_vertical_grid[i].setSize(sf::Vector2f(5.f, 2000.f));
        this->m_vertical_grid[i].setFillColor(this->m_grid_color);
        this->m_vertical_grid[i].setPosition(sf::Vector2f(m_grid_spacing * i, -500.f));
    }

    // horizontal
    for (size_t i = 0; i < 100; i++) {
        sf::Color color(220, 220, 220, 255);
        this->m_horizontal_grid[i].setSize(sf::Vector2f(5.f, 2000.f));
        this->m_horizontal_grid[i].setFillColor(this->m_grid_color);
        this->m_horizontal_grid[i].setPosition(sf::Vector2f(1000.f, m_grid_spacing * i));
        this->m_horizontal_grid[i].setRotation(90.f);
    }
}

void Grid::handleEventCurrent(const sf::Event &event) {
}

void Grid::updateCurrent(const sf::Time &delta) {
}

void Grid::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
    for (const auto &i: this->m_vertical_grid) {
        target.draw(i, states);
    }

    for (const auto &i: this->m_horizontal_grid) {
        target.draw(i, states);
    }
}

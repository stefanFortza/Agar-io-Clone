//
// Created by stefantacu on 08.03.2024.
//

#include "../headers/Grid.hpp"

sf::Vector2i Grid::m_world_size = sf::Vector2i(10000, 10000);
int Grid::m_grid_spacing = 100.f;

Grid::Grid(GameStateManager *manager, sf::RenderWindow *window, const std::string &name): SceneNode(
        manager, window, name),
    m_grid_color(170, 170, 170, 255) {
    // vertical
    for (int i = 0; i < m_world_size.x / m_grid_spacing; i++) {
        this->m_vertical_grid[i].setSize(sf::Vector2f(5.f, m_world_size.y));
        this->m_vertical_grid[i].setOrigin(sf::Vector2f(5.f / 2, m_world_size.y / 2.f));
        this->m_vertical_grid[i].setFillColor(this->m_grid_color);
        // this->m_vertical_grid[i].setPosition(sf::Vector2f(m_grid_spacing * i, m_world_size.y / 2.f));
        this->m_vertical_grid[i].setPosition(sf::Vector2f(-m_world_size.x / 2 + m_grid_spacing * i, 0));
    }

    // horizontal
    for (int i = 0; i < m_world_size.y / m_grid_spacing; i++) {
        sf::Color color(220, 220, 220, 255);
        this->m_horizontal_grid[i].setSize(sf::Vector2f(5.f, m_world_size.y));
        this->m_horizontal_grid[i].setOrigin(sf::Vector2f(5.f / 2, m_world_size.y / 2.f));
        this->m_horizontal_grid[i].setFillColor(this->m_grid_color);
        // this->m_horizontal_grid[i].setPosition(sf::Vector2f(m_world_size.x / 2.f, m_grid_spacing * i));
        this->m_horizontal_grid[i].setPosition(sf::Vector2f(0.f, m_grid_spacing * i));
        this->m_horizontal_grid[i].setPosition(sf::Vector2f(0.f, -m_world_size.y / 2 + m_grid_spacing * i));
        this->m_horizontal_grid[i].setRotation(90.f);
    }

    m_origin.setSize(sf::Vector2f(30.f, 30.f));
    m_origin.setFillColor(sf::Color::Magenta);
    m_origin.setOrigin(sf::Vector2f(15.f, 15.f));
    m_origin.setPosition(sf::Vector2f(0, 0));

    m_world_outline.setSize(sf::Vector2f(m_world_size.x, m_world_size.y));
    m_world_outline.setOutlineColor(sf::Color::Magenta);
    m_world_outline.setOutlineThickness(10.f);
    m_world_outline.setFillColor(sf::Color::Transparent);
    m_world_outline.setOrigin(sf::Vector2f(m_world_size.x / 2.f, m_world_size.y / 2.f));
    m_world_outline.setPosition(sf::Vector2f(0, 0));
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

    target.draw(m_origin, states);
    target.draw(m_world_outline, states);
}

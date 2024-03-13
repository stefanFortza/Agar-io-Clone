//
// Created by stefantacu on 07.03.2024.
//
#include "Node.hpp"
#include "Player.hpp"
#include <SFML/Graphics.hpp>
#include <World.hpp>

World::World() : m_world_size(50000, 50000), m_grid_color(220, 220, 220, 255), m_origin(sf::Vector2f(60.f, 60.f)) {
    // Set children
    this->m_children.push_back(&m_player);
    this->m_origin.setOrigin(sf::Vector2f(30.f, 30.f));
    this->m_origin.setFillColor(sf::Color::Red);

    initializeGrid();
};

World::~World() = default;

void World::onUpdate(sf::Time /*delta*/, sf::RenderWindow &/*window*/) {
    m_appleShape.move(sf::Vector2f(1.f, 1.f));
}

void World::onDraw(sf::RenderWindow &target, const sf::Transform &transform) const {
    for (const auto &i: this->m_vertical_grid) {
        target.draw(i, transform);
    }

    for (const auto &i: this->m_horizontal_grid) {
        target.draw(i, transform);
    }


    target.draw(m_origin, transform);
    // target.draw(m_appleShape, transform);
}

void World::initializeGrid() {
    // initialize grid

    // vertical
    for (size_t i = 0; i < 100; i++) {
        this->m_vertical_grid[i].setSize(sf::Vector2f(1.5f, 2000.f));
        this->m_vertical_grid[i].setFillColor(this->m_grid_color);
        this->m_vertical_grid[i].setPosition(sf::Vector2f(m_grid_spacing * i, -500.f));
    }

    // horizontal
    for (size_t i = 0; i < 100; i++) {
        sf::Color color(220, 220, 220, 255);
        this->m_horizontal_grid[i].setSize(sf::Vector2f(1.5f, 2000.f));
        this->m_horizontal_grid[i].setFillColor(this->m_grid_color);
        this->m_horizontal_grid[i].setPosition(sf::Vector2f(1000.f, m_grid_spacing * i));
        this->m_horizontal_grid[i].setRotation(90.f);
    }
}

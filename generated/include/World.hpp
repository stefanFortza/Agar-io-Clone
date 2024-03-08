#ifndef WORLD_HPP
#define WORLD_HPP
#include <SFML/Graphics.hpp>
#include "Node.hpp"
#include "Player.hpp"

class World : public Node {
public:
    World();

    ~World() override;

private:
    Player m_player;
    float m_grid_spacing = 100.f;
    sf::Vector2u m_windowSize;
    sf::Vector2i m_world_size;
    sf::CircleShape m_appleShape;
    sf::RectangleShape m_vertical_grid[100];
    sf::RectangleShape m_horizontal_grid[100];
    sf::Color m_grid_color;
    sf::RectangleShape m_origin;

    void onUpdate(sf::Time delta, sf::RenderWindow &window) override;

    void onDraw(sf::RenderWindow &target, const sf::Transform &transform) const override;

    void initializeGrid();
};

#endif

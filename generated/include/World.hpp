#ifndef WORLD_HPP
#define WORLD_HPP
#include <SFML/Graphics.hpp>
#include "SceneNode.hpp"
#include "Player.hpp"
#include "PlayerCamera.hpp"


class Player;

class World : public SceneNode {
public:
    explicit World(GameContext &context, sf::RenderWindow &window);


    sf::View &getNodeView();

private:
    Player *m_player;
    PlayerCamera *m_player_camera;
    float m_grid_spacing = 100.f;
    sf::Vector2u m_windowSize;
    sf::Vector2i m_world_size;
    sf::CircleShape m_appleShape;
    sf::RectangleShape m_vertical_grid[100];
    sf::RectangleShape m_horizontal_grid[100];
    sf::Color m_grid_color;
    sf::RectangleShape m_origin;

    void updateCurrent(sf::Time delta) override;

    void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const override;


    void initializeGrid();
};

#endif

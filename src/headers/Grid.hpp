//
// Created by stefantacu on 08.03.2024.
//

#ifndef GRID_H
#define GRID_H
#include "SceneNode.hpp"


class Grid : public SceneNode {
private:
    sf::Vector2u m_windowSize;
    sf::RectangleShape m_vertical_grid[10000];
    sf::RectangleShape m_horizontal_grid[10000];
    sf::Color m_grid_color;
    sf::RectangleShape m_origin;
    sf::RectangleShape m_world_outline;

public:
    Grid(GameStateManager *manager, sf::RenderWindow *window, const std::string &name = "Grid");

    static int m_grid_spacing;
    static sf::Vector2i m_world_size;

private:
    void handleEventCurrent(const sf::Event &event) override;

    void updateCurrent(const sf::Time &delta) override;

    void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const override;
};


#endif //GRID_H

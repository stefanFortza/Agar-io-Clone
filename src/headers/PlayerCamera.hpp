#ifndef PLAYERCAMERA_HPP
#define PLAYERCAMERA_HPP

#include "SceneNode.hpp"

class PlayerCamera : public SceneNode {
public:
    PlayerCamera(GameStateManager *manager, sf::RenderWindow *window);

    void setTarget(SceneNode *target);

    sf::View &getView();

private:
    sf::View m_view;
    SceneNode *m_target;

    void handleEventCurrent(const sf::Event &event) override;

    void updateCurrent(const sf::Time &delta) override;

    void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const override;
};

#endif // PLAYERCAMERA_HPP

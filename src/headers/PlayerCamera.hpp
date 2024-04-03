#ifndef PLAYERCAMERA_HPP
#define PLAYERCAMERA_HPP

#include "SceneNode.hpp"
#include "network/OnlinePlayerData.h"

class Player;

class PlayerCamera : public SceneNode {
public:
    PlayerCamera(GameStateManager *manager, sf::RenderWindow *window);

    void setTarget(Player *target);

    sf::View &getView();

private:
    sf::View m_view;
    Player *m_target;

    void handleEventCurrent(const sf::Event &event) override;

    void updateCurrent(const sf::Time &delta) override;

    void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const override;

    void onPlayerSizeChanged(const float &size);
};

#endif // PLAYERCAMERA_HPP

//
// Created by stefantacu on 15.04.2024.
//

#ifndef LOBBYPLAYERLABEL_H
#define LOBBYPLAYERLABEL_H
#include "Label.h"
#include "../SceneNode.hpp"


class LobbyPlayerLabel : public SceneNode {
public:
    LobbyPlayerLabel(GameStateManager *manager, sf::RenderWindow *window, const std::string &name);

private:
    Label m_player_name;
    sf::RectangleShape m_fill;

    void handleEventCurrent(const sf::Event &event) override;

    void updateCurrent(const sf::Time &delta) override;

    void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const override;
};


#endif //LOBBYPLAYERLABEL_H

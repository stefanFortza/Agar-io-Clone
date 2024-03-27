//
// Created by stefantacu on 16.03.2024.
//

#include "../../headers/player/RemotePlayer.h"

#include <iostream>

RemotePlayer::RemotePlayer(GameStateManager *manager,
                           sf::RenderWindow *window,
                           const std::string &name): PlayerBaseClass(manager, window, name) {
}

sf::FloatRect RemotePlayer::getBounds() {
    return m_player_shape.getGlobalBounds();
}

void RemotePlayer::setData(const OnlinePlayerData &player_data) {
    setPosition(player_data.x, player_data.y);
}

void RemotePlayer::handleEventCurrent(const sf::Event &/*event*/) {
}

void RemotePlayer::updateCurrent(const sf::Time &/*delta*/) {
    // std::cout << "DSA\n";
}

void RemotePlayer::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(m_player_shape, states);
}

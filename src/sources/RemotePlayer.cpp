//
// Created by stefantacu on 16.03.2024.
//

#include "../headers/RemotePlayer.h"

#include <iostream>

RemotePlayer::RemotePlayer(GameStateManager *manager,
                           sf::RenderWindow *window,
                           const std::string &name): PlayerBaseClass(manager, window, name) {
}

void RemotePlayer::handleEventCurrent(const sf::Event &/*event*/) {
}

void RemotePlayer::updateCurrent(const sf::Time &/*delta*/) {
    // std::cout << "DSA\n";
}

void RemotePlayer::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(m_player_shape, states);
}

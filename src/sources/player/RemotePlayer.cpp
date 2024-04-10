//
// Created by stefantacu on 16.03.2024.
//

#include "../../headers/player/RemotePlayer.h"

#include <iostream>

RemotePlayer::RemotePlayer(GameStateManager *manager,
                           sf::RenderWindow *window, std::string net_id,
                           const std::string &name): PlayerBaseClass(manager, window, net_id, name) {
}


void RemotePlayer::handleEventCurrent(const sf::Event &/*event*/) {
}

void RemotePlayer::updateCurrent(const sf::Time &delta) {
    PlayerBaseClass::updateCurrent(delta);
    // std::cout << "DSA\n";
}

void RemotePlayer::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(m_player_shape, states);
    target.draw(m_hitbox, states);
    target.draw(m_hit_sprite, states);
}

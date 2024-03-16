//
// Created by stefantacu on 11.03.2024.
//
#include <iostream>
#include "../headers/PlayerCamera.hpp"

#include "../headers/utils/Vector2.h"


PlayerCamera::PlayerCamera(GameStateManager *manager,
                           sf::RenderWindow *window): SceneNode(manager, window),
                                                      m_view(sf::FloatRect(0.f, 0.f, 1280.f, 720.f)),
                                                      m_target(nullptr) {
}

void PlayerCamera::setTarget(SceneNode *target) {
    this->m_target = target;
}

sf::View &PlayerCamera::getView() {
    return m_view;
}

void PlayerCamera::handleEventCurrent(const sf::Event &/*event*/) {
}


void PlayerCamera::updateCurrent(const sf::Time &/*delta*/) {
    auto pos = m_target->getWorldPosition();
    m_view.setCenter(pos);
    // std::cout << pos << '\n';
}

void PlayerCamera::drawCurrent(sf::RenderTarget &/*target*/, sf::RenderStates /*states*/) const {
}

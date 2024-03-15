//
// Created by stefantacu on 11.03.2024.
//
#include <PlayerCamera.hpp>

// PlayerCamera::PlayerCamera(): SceneNode(), m_view(sf::FloatRect(0.f, 0.f, 1280.f, 720.f)) { }

PlayerCamera::PlayerCamera(): m_view(sf::FloatRect(0.f, 0.f, 1280.f, 720.f)), m_target(nullptr) {
}

void PlayerCamera::setTarget(SceneNode *target) {
    this->m_target = target;
}

sf::View &PlayerCamera::getView() {
    return m_view;
}

void PlayerCamera::handleEventCurrent(const sf::Event &event) {
}

void PlayerCamera::updateCurrent(const sf::Time &delta) {
    m_view.setCenter(m_target->getWorldPosition());
    // this->setPosition(m_target->getWorldPosition());
}

void PlayerCamera::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
}

//
// Created by stefantacu on 11.03.2024.
//
#include <iostream>
#include "../headers/PlayerCamera.hpp"

#include "../headers/utils/Utils.h"


PlayerCamera::PlayerCamera(GameStateManager *manager,
                           sf::RenderWindow *window) : SceneNode(manager, window),
                                                       m_view(sf::FloatRect(0.f, 0.f, 1280.f, 720.f)),
                                                       m_target(nullptr) {
}

void PlayerCamera::setTarget(Player *target) {
    this->m_target = target;
    target->onSizeChanged.connect([this](float size) {
        onPlayerSizeChanged(size);
    });
}


sf::View &PlayerCamera::getView() {
    return m_view;
}

void PlayerCamera::handleEventCurrent(const sf::Event &event) {
    switch (event.type) {
        case sf::Event::EventType::MouseWheelScrolled: {
            std::cout << event.mouseWheelScroll.delta << "\n";
            auto delta = event.mouseWheelScroll.delta;
            if (delta > 0) {
                m_view.zoom(0.98);
            } else {
                m_view.zoom(1.02);
            }

            break;
        }
        default: break;;
    }
}

void PlayerCamera::onPlayerSizeChanged(const float &size) {
    std::cout << "size changed\n";
    m_view.zoom(1.02);
}

void PlayerCamera::updateCurrent(const sf::Time &/*delta*/) {
    if (m_target) {
        auto pos = m_target->getWorldPosition();
        m_view.setCenter(pos);
        // std::cout << pos << '\n';
    }
}

void PlayerCamera::drawCurrent(sf::RenderTarget &/*target*/, sf::RenderStates /*states*/) const {
}



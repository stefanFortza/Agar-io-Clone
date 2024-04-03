//
// Created by stefantacu on 16.03.2024.
//

#include "../../headers/player/PlayerBaseClass.h"


PlayerBaseClass::PlayerBaseClass(GameStateManager *manager,
                                 sf::RenderWindow *window, std::string net_id,
                                 const std::string &name) : Entity(manager, window, name),
                                                            m_player_shape(50.f),
                                                            m_hitbox(10.f),
                                                            m_net_id(net_id) {
    // auto center = sf::Vector2f(static_cast<float>(m_window->getSize().x),
    // static_cast<float>(m_window->getSize().y)) / 2.f;
    // m_player_shape.setOrigin(center);
    m_player_shape.setOrigin(sf::Vector2f(50.f, 50.f));
    m_player_shape.setFillColor(sf::Color::Blue);
    m_hitbox.setOrigin(sf::Vector2f(10.f, 10.f));
    m_hitbox.setFillColor(sf::Color::Red);
}

OnlinePlayerData PlayerBaseClass::getData() {
    OnlinePlayerData data;
    data.id = m_net_id;
    data.x = getWorldPosition().x;
    data.y = getWorldPosition().y;
    data.size = m_size;
    return data;
}

void PlayerBaseClass::setData(const OnlinePlayerData &data) {
    setPosition(data.x, data.y);
    setSize(data.size);
}

sf::FloatRect PlayerBaseClass::getBounds() {
    return getWorldTransform().transformRect(m_player_shape.getGlobalBounds());
}

void PlayerBaseClass::eatFood(Food *food) {
    // TODO add food value
    setSize(m_player_shape.getRadius() + 5.f);
}

void PlayerBaseClass::setSize(float size) {
    m_size = size;
    m_player_shape.setRadius(size);
    auto x = m_player_shape.getRadius();
    m_player_shape.setOrigin(sf::Vector2f(x, x));
    onSizeChanged.emit(size);
}


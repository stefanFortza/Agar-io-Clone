//
// Created by stefantacu on 16.03.2024.
//

#include "../../headers/player/PlayerBaseClass.h"


PlayerBaseClass::PlayerBaseClass(GameStateManager *manager,
                                 sf::RenderWindow *window, const std::string &net_id,
                                 const std::string &name) : Entity(manager, window, name),
                                                            m_player_shape(50.f),
                                                            m_hitbox(5.f),
                                                            m_hit_sprite(50.f),
                                                            m_net_id(net_id)
                                                            , m_is_dead(false) {
    // auto center = sf::Vector2f(static_cast<float>(m_window->getSize().x),
    // static_cast<float>(m_window->getSize().y)) / 2.f;
    // m_player_shape.setOrigin(center);
    m_player_shape.setOrigin(sf::Vector2f(50.f, 50.f));
    m_player_shape.setFillColor(sf::Color::Blue);

    m_hit_sprite.setOrigin(sf::Vector2f(50.f, 50.f));
    m_hit_sprite.setFillColor(sf::Color(255, 255, 255, 0));

    m_hitbox.setOrigin(sf::Vector2f(5.f, 5.f));
    m_hitbox.setFillColor(sf::Color::Red);
}

OnlinePlayerData PlayerBaseClass::getData() {
    OnlinePlayerData data;
    data.id = m_net_id;
    data.x = getWorldPosition().x;
    data.y = getWorldPosition().y;
    data.size = m_size;
    data.is_accelerating = m_is_accelerating;
    return data;
}

void PlayerBaseClass::setData(const OnlinePlayerData &data) {
    if (m_is_dead) return;

    setPosition(data.x, data.y);
    setSize(data.size);
    setIsAccelerating(data.is_accelerating);
    // std::cout << data.is_accelerating << '\n';
}

sf::FloatRect PlayerBaseClass::getBounds() {
    return getWorldTransform().transformRect(m_player_shape.getGlobalBounds());
}

sf::FloatRect PlayerBaseClass::getHitboxBounds() {
    return getWorldTransform().transformRect(m_hitbox.getGlobalBounds());
}

void PlayerBaseClass::eatFood(Food *food) {
    // TODO add food value
    setSize(m_player_shape.getRadius() + 5.f);
}

void PlayerBaseClass::setSize(float size) {
    if (m_is_dead) return;;

    m_size = size;
    m_player_shape.setRadius(size);
    m_hit_sprite.setRadius(size);
    auto x = m_player_shape.getRadius();
    m_player_shape.setOrigin(sf::Vector2f(x, x));
    m_hit_sprite.setOrigin(sf::Vector2f(x, x));
    m_hitbox.setRadius(size * 0.1f);
    m_hitbox.setOrigin(sf::Vector2f(size * 0.1f, size * 0.1f));

    onSizeChanged.emit(size);
}

bool PlayerBaseClass::getIsAccelerating() const {
    return m_is_accelerating;
}

void PlayerBaseClass::setIsAccelerating(bool isAccelerating) {
    if (m_is_dead)return;

    if (isAccelerating) {
        if (!m_is_accelerating) {
            m_elapsed = sf::Time::Zero;
            m_shader_is_glowing_up = true;
        }

        m_is_accelerating = true;
        m_speed = 400;
    } else {
        m_is_accelerating = false;
        m_hit_sprite.setFillColor(sf::Color(255, 255, 255, 0));
        m_speed = 20;
    }
}

float PlayerBaseClass::getSize() const {
    return m_size;
}

bool PlayerBaseClass::canEat(const PlayerBaseClass &player) {
    if (this->m_size > 1.2 * player.getSize()) {
        std::cout << this->m_size << ' ' << player.getSize() << " can eat\n";
        return true;
    }
    return false;
}

void PlayerBaseClass::die() {
    m_is_dead = true;
    m_speed = 0.f;
    m_player_shape.setFillColor(sf::Color::Transparent);
    m_player_shape.setRadius(0.f);
    m_hit_sprite.setFillColor(sf::Color::Transparent);
    m_hit_sprite.setRadius(0.f);
    m_hitbox.setFillColor(sf::Color::Transparent);
    m_hitbox.setRadius(0.f);
}

void PlayerBaseClass::eatPlayer(const OnlinePlayerData &player_data) {
    this->setSize(this->getSize() + player_data.size);
}

void PlayerBaseClass::updateCurrent(const sf::Time &delta) {
    if (m_is_dead) return;

    if (this->getIsAccelerating()) {
        // std::cout << this->getIsAccelerating() << '\n';
        if (m_shader_is_glowing_up) m_elapsed += delta;
        else m_elapsed -= delta;

        if (m_elapsed.asSeconds() > 0.5f)
            m_shader_is_glowing_up = false;

        if (m_elapsed.asSeconds() < 0.0f)
            m_shader_is_glowing_up = true;

        auto proportion = std::clamp(m_elapsed.asSeconds() / 0.5f, 0.f, 1.f);
        int alpha = static_cast<int>(255 * (proportion));
        alpha = std::clamp(alpha, 10, 240);
        m_hit_sprite.setFillColor(sf::Color(255, 255, 255, alpha));
    }
}



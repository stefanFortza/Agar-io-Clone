//
// Created by stefantacu on 11.03.2024.
//

#include <utility>

#include "../headers/Entity.hpp"


Entity::Entity(GameStateManager *manager, sf::RenderWindow *window,
               const std::string &name = "Entity"): SceneNode(manager, window, name) {
}

void Entity::setVelocity(const sf::Vector2f velocity) {
 m_velocity = velocity;
}

void Entity::setVelocity(float vx, float vy) {
 m_velocity.x = vx;
 m_velocity.y = vy;
}

sf::Vector2f Entity::getVelocity() const {
 return m_velocity;
}

void Entity::updateCurrentPhysics(sf::Time delta) {
 this->move(m_velocity * delta.asSeconds());
}

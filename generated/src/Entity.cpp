//
// Created by stefantacu on 11.03.2024.
//

#include "../include/Entity.hpp"

Entity::Entity(GameContext &context): SceneNode(context) {
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

void Entity::updateCurrent(sf::Time delta) {
 // this->move(m_velocity * delta.asSeconds());
}

void Entity::updateCurrentPhysics(sf::Time delta) {
 this->move(m_velocity * delta.asSeconds());
}

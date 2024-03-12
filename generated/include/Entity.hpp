//
// Created by stefantacu on 11.03.2024.
//

#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

#include "SceneNode.hpp"


class Entity : public SceneNode {
public:
 explicit Entity(GameContext &context);

 void setVelocity(sf::Vector2f velocity);

 void setVelocity(float vx, float vy);

 sf::Vector2f getVelocity() const;

 void updateCurrentPhysics(sf::Time delta);

private:
 sf::Vector2f m_velocity;

 void updateCurrent(sf::Time delta) override;
};


#endif //ENTITY_H

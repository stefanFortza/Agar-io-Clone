//
// Created by stefantacu on 11.03.2024.
//

#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include "../../headers/SceneNode.hpp"

class SceneNode;

class Entity : public SceneNode {
public:
 Entity(GameStateManager *manager, sf::RenderWindow *window, const std::string &name);

 void setVelocity(sf::Vector2f velocity);

 void setVelocity(float vx, float vy);

 sf::Vector2f getVelocity() const;

private:
 sf::Vector2f m_velocity;

 // void handleEventCurrent(const sf::Event &event) override;
 //
protected:
 void updateCurrent(const sf::Time &delta) override;
};


#endif //ENTITY_H

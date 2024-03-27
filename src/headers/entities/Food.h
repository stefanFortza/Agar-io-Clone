//
// Created by stefantacu on 27.03.2024.
//

#ifndef FOOD_H
#define FOOD_H
#include "Collidable.h"
#include "Entity.hpp"


class GameStateManager;

class Food : public Entity, public Collidable {
private:
    sf::CircleShape m_shape;
    int m_id;

public:
    int getId() const;

    Food(GameStateManager *manager, sf::RenderWindow *window, int id, const std::string &name = "Food");

    sf::FloatRect getBounds() override;

private:
    void handleEventCurrent(const sf::Event &event) override;

    void updateCurrent(const sf::Time &delta) override;

    void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const override;
};


#endif //FOOD_H

//
// Created by stefantacu on 27.03.2024.
//

#ifndef FOODMANAGER_H
#define FOODMANAGER_H
#include "Food.h"
#include "../SceneNode.hpp"
#include "../utils/Signal.h"

static int id_count = 0;

class FoodManager : public SceneNode {
private:
    static int id_count;
    std::map<int, Food *> m_foods;
    sf::Time m_spawn_timer;
    bool m_is_spawning;

public:
    Signal<Food *> onFoodSpawned;

    FoodManager(GameStateManager *manager, sf::RenderWindow *window,
                const std::string &name = "Food Manager");

    void setIsSpawningFood(bool isSpawning);

    void spawn(sf::Vector2f pos);

    void destroyFood(int id);

    void destroyFood(Food *food);

private:
    void handleEventCurrent(const sf::Event &event) override;

    void updateCurrent(const sf::Time &delta) override;

    void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const override;
};


#endif //FOODMANAGER_H

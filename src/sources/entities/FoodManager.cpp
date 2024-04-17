//
// Created by stefantacu on 27.03.2024.
//

#include "../../headers/entities/FoodManager.h"

#include "../../headers/network/ServerManager.h"

static int id_count = 0;

FoodManager::FoodManager(GameStateManager *manager,
                         sf::RenderWindow *window,
                         const std::string &name): SceneNode(manager, window, name) {
}

void FoodManager::setIsSpawningFood(bool isSpawning) {
    m_is_spawning = isSpawning;
}

void FoodManager::handleEventCurrent(const sf::Event &) {
}

void FoodManager::updateCurrent(const sf::Time &delta) {
    if (m_is_spawning) {
        if (m_children.size() > 10000) {
            m_spawn_timer = sf::Time::Zero;
            return;
        }

        m_spawn_timer += delta;
        while (m_spawn_timer.asSeconds() >= 0.01f) {
            // spawn food
            std::unique_ptr<Food> food = std::make_unique<Food>(m_game_state_manager, m_window, ::id_count++);
            onFoodSpawned.emit(food.get());
            m_foods[food->getId()] = food.get();

            auto pos = food->getWorldPosition();
            ServerManager::getInstance().broadCastFoodSpawned(pos);


            this->attachChild(std::move(food));
            // m_spawn_timer -= sf::Time::Zero;
            m_spawn_timer -= sf::seconds(0.1f);
        }
    }
}

void FoodManager::drawCurrent(sf::RenderTarget &, sf::RenderStates) const {
}

void FoodManager::spawn(sf::Vector2f pos) {
    // spawn food
    std::unique_ptr<Food> food = std::make_unique<Food>(m_game_state_manager, m_window, ::id_count++);
    food->setPosition(pos);
    m_foods[food->getId()] = food.get();
    this->attachChild(std::move(food));
}

void FoodManager::destroyFood(int id) {
    if (m_foods.contains(id)) {
        detachChild(*m_foods[id]);
        m_foods.erase(id);
    }
}

void FoodManager::destroyFood(Food *food) {
    if (m_foods.contains(food->getId())) {
        m_foods.erase(food->getId());
        detachChild(*food);
    }
}

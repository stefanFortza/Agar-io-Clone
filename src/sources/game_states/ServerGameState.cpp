//
// Created by stefantacu on 23.03.2024.
//

#include "../../headers/game_states/ServerGameState.h"


ServerGameState::ServerGameState(GameStateManager *manager, sf::RenderWindow *window,
                                 const std::map<std::string, OnlinePlayerData> &players_data): GameState(
    manager, window, players_data) {
    std::cout << "Game state\n";
    m_players_manager = std::make_unique<PlayersManager>(manager,
                                                         window, players_data,
                                                         ServerManager::getInstance().getServerId()
    );

    auto v = m_players_manager->getCollidables();
    m_collidables.insert(m_collidables.end(), v.begin(), v.end());

    m_players_manager->setCamera(m_player_camera);
    m_food_manager.setIsSpawningFood(true);
    m_food_manager.onFoodSpawned.connect([this](Food *food) {
        onFoodSpawned(food);
    });

    ServerManager::getInstance().onPlayerDataReceived.connect([this](const OnlinePlayerData &player_data) {
        handlePlayerDataReceived(player_data);
    });
}

void ServerGameState::handleEvent(const sf::Event &event) {
    m_players_manager->handleEvent(event);
    m_player_camera.handleEvent(event);
    m_food_manager.handleEvent(event);
}

void ServerGameState::render() {
    m_window->setView(m_player_camera.getView());
    m_window->draw(m_grid);
    m_window->draw(m_food_manager);
    m_window->draw(*m_players_manager);

    // draw ui
    m_window->setView(m_window->getDefaultView());
}


void ServerGameState::update(const sf::Time &deltaTime) {
    m_players_manager->update(deltaTime);
    m_player_camera.update(deltaTime);
    m_food_manager.update(deltaTime);


    // check colisions
    checkCollisions();


    // BroadCast local data
    OnlinePlayerData data = m_players_manager->getLocalPlayerData();
    ServerManager::getInstance().broadCastLocalData(data);
}

void ServerGameState::onFoodSpawned(Food *food) {
    m_collidables.push_back(food);
}

void ServerGameState::handlePlayerDataReceived(const OnlinePlayerData &player_data) {
    m_players_manager->handlePlayerDataReceived(player_data);
}

void ServerGameState::checkCollisions() {
    for (int i = 0; i < m_collidables.size(); i++) {
        for (int j = i + 1; j < m_collidables.size(); j++) {
            if (dynamic_cast<PlayerBaseClass *>(m_collidables[i]) && dynamic_cast<Food *>(m_collidables[j])) {
                if (m_collidables[i]->getBounds().intersects(m_collidables[j]->getBounds())) {
                    // std::cout << "Ate food\n";
                    // std::cout << m_collidables[i]->getBounds().getPosition() << '\n';
                    auto player = dynamic_cast<PlayerBaseClass *>(m_collidables[i]);
                    auto food = dynamic_cast<Food *>(m_collidables[j]);

                    player->eatFood(food);
                    ServerManager::getInstance().broadcastFoodEaten(player->getData(), food);
                    m_collidables.erase(m_collidables.begin() + j);
                    m_food_manager.destroyFood(food);
                }
            }
        }
    }
}

void ServerGameState::handlePlayerDisconected(const std::string &id) {
}

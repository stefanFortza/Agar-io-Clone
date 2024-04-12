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
        onPlayerDataReceived(player_data);
    });

    ServerManager::getInstance().onPlayerDisconnected.connect([this](const std::string &id) {
        onPlayerDisconnected(id);
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

void ServerGameState::onPlayerDataReceived(const OnlinePlayerData &player_data) {
    m_players_manager->handlePlayerDataReceived(player_data);
}

void ServerGameState::checkCollisions() {
    for (int i = 0; i < m_collidables.size(); i++) {
        for (int j = i + 1; j < m_collidables.size(); j++) {
            if (dynamic_cast<PlayerBaseClass *>(m_collidables[i]) && dynamic_cast<Food *>(m_collidables[j])) {
                auto player = dynamic_cast<PlayerBaseClass *>(m_collidables[i]);
                auto food = dynamic_cast<Food *>(m_collidables[j]);
                if (player->getBounds().intersects(food->getBounds())) {
                    player->eatFood(food);
                    ServerManager::getInstance().broadcastFoodEaten(player->getData(), food);
                    m_collidables.erase(m_collidables.begin() + j);
                    m_food_manager.destroyFood(food);
                }
            } else if (dynamic_cast<PlayerBaseClass *>(m_collidables[i]) && dynamic_cast<PlayerBaseClass *>(
                           m_collidables[j])) {
                auto player1 = dynamic_cast<PlayerBaseClass *>(m_collidables[i]);
                auto player2 = dynamic_cast<PlayerBaseClass *>(m_collidables[j]);
                if (player1->getBounds().intersects(player2->getHitboxBounds())) {
                    // std::cout << "hitbox collision\n";
                    if (player1->canEat(*player2)) {
                        ServerManager::getInstance().broadCastPlayerEaten(player1->getData(), player2->getData());
                        m_players_manager->playerAtePlayer(player1->getData(), player2->getData());
                        m_collidables.erase(m_collidables.begin() + j);
                    }
                } else if (player2->getBounds().intersects(player1->getHitboxBounds())) {
                    // std::cout << "hitbox collision\n";
                    if (player2->canEat(*player1)) {
                        ServerManager::getInstance().broadCastPlayerEaten(player2->getData(), player1->getData());
                        m_players_manager->playerAtePlayer(player2->getData(), player1->getData());
                        m_collidables.erase(m_collidables.begin() + i);
                    }
                }
            }
        }
    }
}

// void ServerGameState::handlePlayerDisconected(const std::string &id) {
// }

void ServerGameState::onPlayerDisconnected(const std::string &id) {
    for (int i = 0; i < m_collidables.size(); i++) {
        auto player = dynamic_cast<PlayerBaseClass *>(m_collidables[i]);
        if (player && player->getData().id == id) {
            m_collidables.erase(m_collidables.begin() + i);
            break;
        }
    }

    m_players_manager->disconnectPlayer(id);
}

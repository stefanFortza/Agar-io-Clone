//
// Created by stefantacu on 27.03.2024.
//

#ifndef PLAYERSMANAGER_H
#define PLAYERSMANAGER_H
#include "Player.hpp"
#include "RemotePlayer.h"
#include "../SceneNode.hpp"
#include "../PlayerCamera.hpp"
#include <memory>


class Player;
class RemotePlayer;

class PlayersManager : public SceneNode {
private:
    std::unique_ptr<Player> m_player;
    std::map<std::string, RemotePlayer> m_remote_players;

public:
    PlayersManager(GameStateManager *manager, sf::RenderWindow *window,
                   const std::map<std::string, OnlinePlayerData> &players_data, const std::string &local_player_id,
                   const std::string &name = "Player manager");

    void setCamera(PlayerCamera &player_camera);

    void handlePlayerDataReceived(const OnlinePlayerData &player_data);

    std::vector<Collidable *> getCollidables();

    OnlinePlayerData getLocalPlayerData();

    void playerAteFood(const OnlinePlayerData &data);

    void playerAtePlayer(const OnlinePlayerData &player1, const OnlinePlayerData &player2);

    void disconnectPlayer(const std::string &id);

private:
    void handleEventCurrent(const sf::Event &event) override;

    void updateCurrent(const sf::Time &delta) override;


    void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const override;

public:
    // void setPlayers(const std::map<std::string, OnlinePlayerData> &players_data);
};


#endif //PLAYERSMANAGER_H

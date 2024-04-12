//
// Created by stefantacu on 15.03.2024.
//

#ifndef SERVER_H
#define SERVER_H
#include <ostream>

#include "SFML/Network/Packet.hpp"
#include "SFML/Network/UdpSocket.hpp"
#include "../game_states/GameState.h"
#include "NetworkManager.h"
#include <string>
#include "../utils/Signal.h"

enum PacketType:unsigned int {
	HeartBeat,
	ConnectedToLobby,
	PlayerPosition,
	PlayerJoinedLobby,
	OnlinePlayersData,
	PlayerData,
	PlayerDisconected,
	GameStarted,
	FoodSpawned,
	FoodEaten,
	PlayerEaten
};


class ServerManager {
private:
	sf::UdpSocket m_socket;
	std::map<std::string, OnlinePlayerData> m_connected_players;
	sf::Packet m_packet;
	std::string m_server_id;
	bool m_running;

public:
	static ServerManager &getInstance();

	Signal<const OnlinePlayerData &> onPlayerJoinedLobby;
	Signal<std::map<std::string, OnlinePlayerData> &> onGameStarted;
	Signal<const OnlinePlayerData &> onPlayerDataReceived;
	Signal<const std::string &> onPlayerDisconnected;

	const std::map<std::string, OnlinePlayerData> &getConnectedPlayers() const;

	const std::string &getServerId() const;

	void start(std::string &name);

	void handlePlayerJoinedLobby(std::string id, std::string name);

	void handlePlayerData(const OnlinePlayerData &data);

	void receiveData();

	void sendData();

	void broadCastToOnlinePlayersAndServer(sf::Packet &packet);

	void broadCast(sf::Packet &packet, const std::string &id_to_ignore = "");

	void broadCastToOnlinePlayersWithoutServer(sf::Packet &packet);

	void sendPacket(sf::Packet &packet, const std::string &id);

	~ServerManager();

	bool isRunning() const;

	void startGame();

	void broadCastLocalData(const OnlinePlayerData &data);

	void broadCastFoodSpawned(sf::Vector2f pos);

	void broadcastFoodEaten(OnlinePlayerData data, Food *food);

	void broadCastPlayerEaten(const OnlinePlayerData &player1, const OnlinePlayerData &player2);

private:
	explicit ServerManager();
};


#endif //SERVER_H

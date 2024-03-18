//
// Created by stefantacu on 15.03.2024.
//

#ifndef SERVER_H
#define SERVER_H
#include "SFML/Network/Packet.hpp"
#include "SFML/Network/UdpSocket.hpp"
#include "../game_states/GameState.h"
#include "NetworkManager.h"
// #include <memory>

enum PacketType:unsigned int {
	Connected,
	PlayerPosition,
	PlayerJoinedServer,
	OnlinePlayersData
};

class Player;
class GameState;
class Server;

class OnlinePlayerData {
public:
	OnlinePlayerData(sf::IpAddress ip_address, int port, float x = 0, float y = 0) {
		this->ip_address = ip_address;
		this->port = port;
		this->x = x;
		this->y = y;
	}

	std::string getId() {
		std::string id(ip_address.toString());
		id += ":";
		id += std::to_string(port);
		return id;
	}

	sf::Packet getPacket(PacketType type, sf::Packet &packet) {
		switch (type) {
			case Connected:
				// packet << ip_address.toString() << port << x << y;
				packet << getId() << x << y;
				break;
			case PlayerPosition:
				break;
			case PlayerJoinedServer:
				packet << ip_address.toString() << port << x << y;
				break;
			case OnlinePlayersData:
				break;
		}
		return packet;
	}

	// private:
public:
	sf::IpAddress ip_address;
	int port;
	float x, y;
};

class Server {
private:
	static const int MAX_PLAYERS = 2;
	sf::UdpSocket m_socket;
	std::map<std::string, std::unique_ptr<OnlinePlayerData> > m_connected_players;
	sf::Packet m_packet;
	GameState *m_game_state;

public:
	explicit Server(GameState *game_state);

	static std::string getId(sf::IpAddress sender, unsigned short port);

	void start();

	void sendData();

	void broadCastToOnlinePlayers(sf::Packet &packet);

	void setCurrentPlayerData(float x, float y);

	void sendPacket(sf::Packet &packet, std::string &id);


	~Server();

	// private:
	// 	void checkForIncommingConnections();
	//
	// 	void checkForIncommingPackets();
	//
	// 	void processPackets();
};


#endif //SERVER_H

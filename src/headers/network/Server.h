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
// #include <memory>

enum PacketType:unsigned int {
	Connected,
	PlayerPosition,
	PlayerJoinedServer,
	OnlinePlayersData,
	PlayerDisconected
};

class Player;
class GameState;
class Server;

class OnlinePlayerData {
public:
	OnlinePlayerData(sf::IpAddress ip_address, int port, float x = 0, float y = 0) {
		this->m_ip_address = ip_address;
		this->m_port = port;
		this->x = x;
		this->y = y;
	}

	OnlinePlayerData(std::string id, float x = 0, float y = 0) {
		setIdAndPort(id);
		this->x = x;
		this->y = y;
	}

	OnlinePlayerData(const OnlinePlayerData &other)
		: m_ip_address(other.m_ip_address),
		  m_port(other.m_port),
		  x(other.x),
		  y(other.y) {
	}

	std::string getId() {
		std::string id(m_ip_address.toString());
		id += ":";
		id += std::to_string(m_port);
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
				packet << getId() << x << y;
				break;
			case OnlinePlayersData:
				packet << getId() << x << y;
				break;
			case PlayerDisconected:
				packet << getId();
				break;
			default: ;
		}
		return packet;
	}

	friend std::ostream &operator<<(std::ostream &os, const OnlinePlayerData &obj) {
		return os
		       << "ip_address: " << obj.m_ip_address
		       << " port: " << obj.m_port
		       << " x: " << obj.x
		       << " y: " << obj.y;
	}

	OnlinePlayerData &operator=(const OnlinePlayerData &other) {
		if (this == &other)
			return *this;
		m_ip_address = other.m_ip_address;
		m_port = other.m_port;
		x = other.x;
		y = other.y;
		return *this;
	}

	sf::IpAddress &getIpAdress();

	int getPort();

	void setXY(float x, float y);

	void setIdAndPort(std::string id);

	sf::Vector2f getXY();

private:
	sf::IpAddress m_ip_address;
	int m_port;
	float x, y;
};

class Server {
private:
	sf::UdpSocket m_socket;
	std::map<std::string, std::unique_ptr<OnlinePlayerData> > m_connected_players;
	sf::Packet m_packet;
	GameState *m_game_state;
	std::string m_server_id;

public:
	explicit Server(GameState *game_state);

	static std::string getId(sf::IpAddress sender, unsigned short port);

	const std::map<std::string, std::unique_ptr<OnlinePlayerData> > &getConnectedPlayers() const;

	const std::string &getServerId() const;

	void start();

	void sendData();

	void broadCastToOnlinePlayers(sf::Packet &packet);

	void setCurrentServerPlayerData(float x, float y);

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

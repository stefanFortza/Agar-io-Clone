//
// Created by stefantacu on 15.03.2024.
//

#ifndef SERVER_H
#define SERVER_H
#include "SFML/Network/Packet.hpp"
#include "SFML/Network/UdpSocket.hpp"
// #include <memory>


class Player;

class Server {
private:
	static const int MAX_PLAYERS = 2;
	sf::UdpSocket m_socket;
	// std::vector<std::unique_ptr<Player> > sockets;
	sf::Packet m_packet;

public:
	Server();

	void start();

	~Server();

	// private:
	// 	void checkForIncommingConnections();
	//
	// 	void checkForIncommingPackets();
	//
	// 	void processPackets();
};


#endif //SERVER_H

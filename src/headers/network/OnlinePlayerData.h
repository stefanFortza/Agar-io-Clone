//
// Created by stefantacu on 21.03.2024.
//

#ifndef ONLINEPLAYERDATA_H
#define ONLINEPLAYERDATA_H
#include <ostream>
#include <utility>
#include "SFML/Network/Packet.hpp"


struct OnlinePlayerData {
	OnlinePlayerData(std::string id = "", float x = 0, float y = 0)
		: id(std::move(id)),
		  x(x),
		  y(y) {
	}

	// std::string getIpAdress() {
	// 	std::string id(ip_address.toString());
	// 	id += ":";
	// 	id += std::to_string(port);
	// 	return id;
	// }
	// std::string getIpAdress() {
	// 	std::string id(ip_address.toString());
	// 	id += ":";
	// 	id += std::to_string(port);
	// 	return id;
	// }

	friend sf::Packet &operator>>(sf::Packet &packet, OnlinePlayerData &obj) {
		packet >> obj.id >> obj.x >> obj.y;
		return packet;
	}

	friend sf::Packet &operator<<(sf::Packet &packet, const OnlinePlayerData &obj) {
		packet << obj.id << obj.x << obj.y;

		return packet;
	}

	friend std::ostream &operator<<(std::ostream &os, const OnlinePlayerData &obj) {
		return os
		       << " id: " << obj.id
		       << " x: " << obj.x
		       << " y: " << obj.y;
	}

	OnlinePlayerData(const OnlinePlayerData &other)
		: id(other.id),
		  x(other.x),
		  y(other.y) {
	}

	OnlinePlayerData(OnlinePlayerData &&other) noexcept
		: id(std::move(other.id)),
		  x(other.x),
		  y(other.y) {
	}

	OnlinePlayerData &operator=(const OnlinePlayerData &other) {
		if (this == &other)
			return *this;
		id = other.id;
		x = other.x;
		y = other.y;
		return *this;
	}

	OnlinePlayerData &operator=(OnlinePlayerData &&other) noexcept {
		if (this == &other)
			return *this;
		id = std::move(other.id);
		x = other.x;
		y = other.y;
		return *this;
	}


	std::string id;
	float x, y;
};

#endif //ONLINEPLAYERDATA_H

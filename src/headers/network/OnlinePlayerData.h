//
// Created by stefantacu on 21.03.2024.
//

#ifndef ONLINEPLAYERDATA_H
#define ONLINEPLAYERDATA_H
#include <ostream>
#include <utility>
#include "SFML/Network/Packet.hpp"


struct OnlinePlayerData {
	explicit OnlinePlayerData(std::string id = "", float x = 0, float y = 0, float size = 50,
	                          bool is_accelerating = false)
		: id(std::move(id)),
		  x(x),
		  y(y),
		  size(size),
		  is_accelerating(is_accelerating) {
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
		packet >> obj.id >> obj.x >> obj.y >> obj.size >> obj.is_accelerating;
		return packet;
	}

	friend sf::Packet &operator<<(sf::Packet &packet, const OnlinePlayerData &obj) {
		packet << obj.id << obj.x << obj.y << obj.size << obj.is_accelerating;

		return packet;
	}

	friend std::ostream &operator<<(std::ostream &os, const OnlinePlayerData &obj) {
		return os
		       << " id: " << obj.id
		       << " x: " << obj.x
		       << " y: " << obj.y
		       << "size: " << obj.size;
	}

	OnlinePlayerData(const OnlinePlayerData &other)
		: id(other.id),
		  x(other.x),
		  y(other.y),
		  size(other.size),
		  is_accelerating(other.is_accelerating) {
	}

	OnlinePlayerData(OnlinePlayerData &&other) noexcept
		: id(std::move(other.id)),
		  x(other.x),
		  y(other.y),
		  size(other.size),
		  is_accelerating(other.is_accelerating) {
	}

	OnlinePlayerData &operator=(const OnlinePlayerData &other) {
		if (this == &other)
			return *this;
		id = other.id;
		x = other.x;
		y = other.y;
		y = other.y;
		size = other.size;
		is_accelerating = other.is_accelerating;
		return *this;
	}

	OnlinePlayerData &operator=(OnlinePlayerData &&other) noexcept {
		if (this == &other)
			return *this;
		id = std::move(other.id);
		x = other.x;
		y = other.y;
		size = other.size;
		is_accelerating = other.is_accelerating;
		return *this;
	}


	std::string id;
	float x, y;
	float size;
	bool is_accelerating;
};

#endif //ONLINEPLAYERDATA_H

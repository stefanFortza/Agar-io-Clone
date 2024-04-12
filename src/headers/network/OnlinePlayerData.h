//
// Created by stefantacu on 21.03.2024.
//

#ifndef ONLINEPLAYERDATA_H
#define ONLINEPLAYERDATA_H
#include <ostream>
#include <utility>
#include "SFML/Network/Packet.hpp"
// #include "../utils/Utils.h"


inline sf::Packet &operator<<(sf::Packet &packet, const sf::Color &color) {
	packet << color.toInteger();
	return packet;
}

inline sf::Packet &operator>>(sf::Packet &packet, sf::Color &color) {
	sf::Uint32 col;
	packet >> col;
	color = sf::Color(col);
	return packet;
}

struct OnlinePlayerData {
	explicit OnlinePlayerData(std::string id = "", std::string name = "", sf::Color color = sf::Color::Red, float x = 0,
	                          float y = 0, float size = 50,
	                          bool is_accelerating = false)
		: id(std::move(id)),
		  x(x),
		  y(y),
		  size(size),
		  color(color),
		  is_accelerating(is_accelerating),
		  name(name) {
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
		packet >> obj.id >> obj.name >> obj.x >> obj.y >> obj.size >> obj.color >> obj.is_accelerating;
		return packet;
	}

	friend sf::Packet &operator<<(sf::Packet &packet, const OnlinePlayerData &obj) {
		packet << obj.id << obj.name << obj.x << obj.y << obj.size << obj.color << obj.is_accelerating;
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
		  is_accelerating(other.is_accelerating),
		  color(other.color),
		  name(other.name) {
	}

	OnlinePlayerData(OnlinePlayerData &&other) noexcept
		: id(std::move(other.id)),
		  x(other.x),
		  y(other.y),
		  size(other.size),
		  color(other.color),
		  is_accelerating(other.is_accelerating),
		  name(other.name) {
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
		color = other.color;
		name = other.name;
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
		color = other.color;
		name = other.name;
		return *this;
	}


	std::string id;
	std::string name;
	sf::Color color;
	float x, y;
	float size;
	bool is_accelerating;
};

#endif //ONLINEPLAYERDATA_H

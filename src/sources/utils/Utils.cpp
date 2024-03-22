//
// Created by stefantacu on 15.03.2024.
//

#include "../../headers/utils/Utils.h"

std::ostream &operator<<(std::ostream &os, const sf::Vector2f &vector) {
	os << "(" << vector.x << ", " << vector.y << ")";
	return os;
}

std::string NetworkUtils::getIdFromAdressAndPort(sf::IpAddress sender, unsigned short port) {
	std::string id(sender.toString());
	id += ":";
	id += std::to_string(port);
	return id;
}

sf::IpAddress NetworkUtils::getAdressFromId(const std::string &id) {
	std::string delimiter = ":";
	auto adress = id.substr(0, id.find(delimiter));
	return sf::IpAddress(id);
}

sf::Uint32 NetworkUtils::getPortFromId(const std::string &id) {
	std::string delimiter = ":";
	auto adress = id.substr(0, id.find(delimiter));
	auto port_str = id.substr(id.find(delimiter), id.length());
	auto port = std::stoi(port_str);
	return static_cast<sf::Uint32>(port);
}

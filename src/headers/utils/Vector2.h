//
// Created by stefantacu on 15.03.2024.
//
#pragma once
#include <ostream>
#include "SFML/System/Vector2.hpp"

template<class T>
std::ostream &operator<<(std::ostream &os, const sf::Vector2<T> &vector) {
    os << "(" << vector.x << ", " << vector.y << ")";
    return os;
}


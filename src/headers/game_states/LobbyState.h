//
// Created by stefantacu on 20.03.2024.
//

#ifndef LOBBYSTATE_H
#define LOBBYSTATE_H
#include "State.hpp"
#include "../network/NetworkManager.h"


class LobbyState : public State {
public:
    LobbyState(GameStateManager *manager, sf::RenderWindow *window);
};


#endif //LOBBYSTATE_H

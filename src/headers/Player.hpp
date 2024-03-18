#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entity.hpp"
#include "Game.hpp"
#include "PlayerBaseClass.h"

class Player : public PlayerBaseClass {
public:
    explicit Player(GameStateManager *manager,
                    sf::RenderWindow *window,
                    const std::string &name = "Player");

    ~Player();

    // const sf::View &GetView() const;

private:
    void handleEventCurrent(const sf::Event &event) override;

    void updateCurrent(const sf::Time &delta) override;

    void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const override;
};

#endif

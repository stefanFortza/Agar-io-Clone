//
// Created by stefantacu on 16.03.2024.
//

#ifndef REMOTEPLAYER_H
#define REMOTEPLAYER_H
#include "../game_states/GameStateManager.h"
#include "PlayerBaseClass.h"


class RemotePlayer : public PlayerBaseClass {
public:
    explicit RemotePlayer(GameStateManager *manager,
                          sf::RenderWindow *window,
                          const std::string &name = "Remotec");

    sf::FloatRect getBounds() override;

    ~RemotePlayer() = default;

    void setData(const OnlinePlayerData &player_data);

private:
    void handleEventCurrent(const sf::Event &event) override;

    void updateCurrent(const sf::Time &delta) override;

    void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const override;
};


#endif //REMOTEPLAYER_H

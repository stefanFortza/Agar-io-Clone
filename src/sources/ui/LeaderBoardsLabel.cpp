//
// Created by stefantacu on 10.04.2024.
//

#include "../../headers/ui/LeaderBoardsLabel.h"

// LeaderBoardsLabel::LeaderBoardsLabel(): Label() {
// }

void LeaderBoardsLabel::setPlayer(const OnlinePlayerData &player, int i) {
    std::string str = std::to_string(i + 1) + ". " + player.name + ": " + std::to_string(
                          static_cast<unsigned long long>(player.size));
    this->setString(str);
}

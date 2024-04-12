//
// Created by stefantacu on 10.04.2024.
//

#ifndef LEADERBOARDSLABEL_H
#define LEADERBOARDSLABEL_H
#include "Label.h"
#include "../network/OnlinePlayerData.h"


class LeaderBoardsLabel : public Label {
public:
    // LeaderBoardsLabel();
    LeaderBoardsLabel() = default;

    void setPlayer(const OnlinePlayerData &player, int i);
};


#endif //LEADERBOARDSLABEL_H

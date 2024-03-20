//
// Created by stefantacu on 20.03.2024.
//

#include "../headers/Command.h"

Command::Command(CommandType type,
                 std::map<std::string, std::unique_ptr<OnlinePlayerData> > &data): type(type),
    player_data(data) {
}

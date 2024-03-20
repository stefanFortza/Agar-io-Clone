//
// Created by stefantacu on 20.03.2024.
//

#ifndef COMMAND_H
#define COMMAND_H
#include <map>
#include <memory>
#include <string>


class OnlinePlayerData;

enum CommandType {
    CreatePlayer,
    SetCurrnetWorldFromServer
};

struct Command {
    Command(CommandType type, std::map<std::string, std::unique_ptr<OnlinePlayerData> > &data);

    CommandType type;
    std::string player_id;
    std::map<std::string, std::unique_ptr<OnlinePlayerData> > &player_data;
};


#endif //COMMAND_H

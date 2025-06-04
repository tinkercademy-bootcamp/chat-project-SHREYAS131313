#pragma once
#include <string>
#include <unordered_map>
#include "../class/channel_class.h"

class ChannelManager {
public:
    bool createChannel(const std::string& name);
    bool joinChannel(const std::string& channel_name, int client_fd);
    bool leaveChannel(const std::string& channel_name, int client_fd);
    std::unordered_map<std::string, Channel>& getChannels();

private:
    std::unordered_map<std::string, Channel> channels_list;
};

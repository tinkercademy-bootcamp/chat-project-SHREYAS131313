#include "channel_manager.h"

bool ChannelManager::createChannel(const std::string& name) {
    // Check if the channel already exists
    if (channels_list.find(name) != channels_list.end()) {
        return false; // Channel already exists
    }

    // Create a new channel and add it to the map
    channels_list[name] = Channel(name);
    return true;
}

bool ChannelManager::joinChannel(const std::string& channel_name, int client_fd) {
    auto it = channels_list.find(channel_name);
    if (it == channels_list.end()) {
        return false; // Channel doesn't exist
    }

    it->second.addUser(client_fd);
    return true;
}

bool ChannelManager::leaveChannel(const std::string& channel_name, int client_fd) {
    auto it = channels_list.find(channel_name);
    if (it == channels_list.end()) {
        return false; // Channel doesn't exist
    }

    it->second.removeUser(client_fd);
    return true;
}

std::unordered_map<std::string, Channel>& ChannelManager::getChannels() {
    return channels_list;
}

std::string ChannelManager::listChannels() {
    
    if (channels_list.empty()) return "No channels available.\n";

    std::string result = "Available channels:\n";
    for (const auto& [name, _] : channels_list) {
        result += "- " + name + "\n";
    }
    return result;
}

#pragma once
#include <string>
#include <unordered_map>
#include <sys/socket.h>
#include "./channel_manager.h"


struct ClientInfo
{
    std::string username;
    std::string current_channel;
};

class ClientManager
{
public:
    void addClient(int client_fd);
    void removeClient(int client_fd);
    void setUsername(int client_fd, const std::string &username);
    void setChannel(int client_fd, const std::string &channel);
    void handle_client_message(int client_fd, std::string command,std::string recv_msg);
    ClientInfo *getClientInfo(int client_fd);
    ChannelManager channel_manager;

private:
    std::unordered_map<int, ClientInfo> clients_list;
};

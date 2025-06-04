#pragma once
#include <string>
#include <unordered_map>

struct ClientInfo {
    std::string username;
    std::string current_channel;
};

class ClientManager {
public:
    void addClient(int client_fd);
    void removeClient(int client_fd);
    void setUsername(int client_fd, const std::string& username);
    void setChannel(int client_fd, const std::string& channel);

    ClientInfo* getClientInfo(int client_fd);  

private:
    std::unordered_map<int, ClientInfo> clients_list;
};

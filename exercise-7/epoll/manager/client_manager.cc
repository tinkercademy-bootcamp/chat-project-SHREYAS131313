#include "client_manager.h"

void ClientManager::addClient(int client_fd) {
    // Adds a new client with default empty info
    clients_list[client_fd] = ClientInfo();
}

void ClientManager::removeClient(int client_fd) {
    clients_list.erase(client_fd);
}

void ClientManager::setUsername(int client_fd, const std::string& username) {
    auto it = clients_list.find(client_fd);
    if (it != clients_list.end()) {
        it->second.username = username;
    }
}

void ClientManager::setChannel(int client_fd, const std::string& channel) {
    auto it = clients_list.find(client_fd);
    if (it != clients_list.end()) {
        it->second.current_channel = channel;
    }
}

ClientInfo* ClientManager::getClientInfo(int client_fd) {
    auto it = clients_list.find(client_fd);
    if (it != clients_list.end()) {
        return &(it->second);
    }
    return nullptr;
}

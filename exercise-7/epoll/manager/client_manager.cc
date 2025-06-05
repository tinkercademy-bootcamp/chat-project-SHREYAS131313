#include "client_manager.h"

void ClientManager::addClient(int client_fd)
{
    // Adds a new client with default empty info
    clients_list[client_fd] = ClientInfo();
}

void ClientManager::removeClient(int client_fd)
{
    clients_list.erase(client_fd);
}

void ClientManager::setUsername(int client_fd, const std::string &username)
{
    auto it = clients_list.find(client_fd);
    if (it != clients_list.end())
    {
        it->second.username = username;
    }
}

void ClientManager::setChannel(int client_fd, const std::string &channel)
{
    auto it = clients_list.find(client_fd);
    if (it != clients_list.end())
    {
        it->second.joined_channels.insert(channel);
    }
}

ClientInfo *ClientManager::getClientInfo(int client_fd)
{
    auto it = clients_list.find(client_fd);
    if (it != clients_list.end())
    {
        return &(it->second);
    }
    return nullptr;
}

void ClientManager::handle_client_message(int client_fd, std::string command, std::string recv_msg)
{
    std::string channel_name = recv_msg;
    if (command == "/list")
    {
        std::string list = channel_manager.listChannels();
        send(client_fd, list.c_str(), list.size(), 0);
    }
    else if (command == "/join")
    {
        if (channel_manager.joinChannel(channel_name, client_fd))
        {
            setChannel(client_fd, channel_name);
            std::string msg = "Joined channel: " + channel_name + "\n";
            send(client_fd, msg.c_str(), msg.size(), 0);
        }
        else
        {
            std::string msg = "Channel not found: " + channel_name + "\n";
            send(client_fd, msg.c_str(), msg.size(), 0);
        }
    }
    else if (command == "/create")
    {
        if (channel_name.empty())
        {
            send(client_fd, "Channel name cannot be empty.\n", 30, 0);
        }
        else
        {
            bool result = channel_manager.createChannel(channel_name);
            if (result)
            {
                channel_manager.joinChannel(channel_name, client_fd);
                setChannel(client_fd, channel_name);

                std::string msg = "Created and joined channel: " + channel_name + "\n";
                send(client_fd, msg.c_str(), msg.size(), 0);
            }
            else
            {
                std::string msg = "Channel Already exists and joined channel: " + channel_name + "\n";
                send(client_fd, msg.c_str(), msg.size(), 0);
            }
        }
    }
    else if (command == "/quit")
    {
        std::cout << client_fd << " quitting\n";
    }
    else if (command == "/message")
    {
        auto parsed_result = parse_command(recv_msg);
        std::string channel_name = std::string(parsed_result.first);
        std::string message = std::string(parsed_result.second);

        bool channel_exist = channel_manager.check_if_channel_exists(channel_name);
        if (!channel_exist)
        {
            std::string err = "Channel '" + channel_name + "' does not exist.\n";
            send(client_fd, err.c_str(), err.size(), 0);
            return;
        }
        auto *client_info = getClientInfo(client_fd);

        // if(client_info->joined_channels())
        for (auto j : client_info->joined_channels)
        {
            std::cout << j << '\n';
        }

        if (client_info->joined_channels.find(channel_name) == client_info->joined_channels.end())
        {
            std::string err = "You have not joined the channel '" + channel_name + "'.\n";
            send(client_fd, err.c_str(), err.size(), 0);
            return;
        }
        auto &channels = channel_manager.getChannels();
        auto it = channels.find(channel_name);

        const auto &users = it->second.getUsers();
        std::string full_msg = client_info->username + " in [" + channel_name + "]: " + message + "\n";

        for (int user_fd : users)
        {
            if (user_fd != client_fd)
            {
                send(user_fd, full_msg.c_str(), full_msg.size(), 0); // server acts like a sending body of the message
            }
        }
    }
    else{

    }
}

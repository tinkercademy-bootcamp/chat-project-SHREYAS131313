#include "channel_class.h"

Channel::Channel(std::string channel_nm)
    : channel_name(channel_nm)
{}

// Adds a user to the channel
bool Channel::addUser(int client_fd)
{
    if (channel_users.find(client_fd) != channel_users.end()) {
        // User already exists
        return false;
    }
    channel_users.insert(client_fd);
    return true;
}
// Removes a user from the channel
bool Channel::removeUser(int client_fd)
{
    if (channel_users.find(client_fd) == channel_users.end()) {
        // User doesn't exist
        return false;
    }
    channel_users.erase(client_fd);
    return true;
}
// Returns the channel name
std::string Channel::getName() const
{
    return channel_name;
}
// Returns the set of users in the channel
std::unordered_set<int> Channel::getUsers() const
{
    return channel_users;
}

#ifndef CHANNEL_H
#define CHANNEL_H

#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <string>
#include <unordered_set>
#include <vector>
#include "../shared/shared.h"

class Channel{
public:
    Channel()=default;
    explicit Channel(std::string channel_nm);
    bool addUser(int client_fd);
    bool removeUser(int client_fd);
    int getID();
    std::string getName() const;
    std::unordered_set<int> getUsers() const;

private:
    // int channel_id;
    std::string channel_name;
    std::unordered_set<int> channel_users;
};


#endif
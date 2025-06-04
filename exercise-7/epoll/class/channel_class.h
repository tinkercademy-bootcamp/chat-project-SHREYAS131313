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
    explicit Channel(std::string channel_nm);

    void addUser(int client_fd);
    void removeUser(int client_fd);
    int getID();
    std::string getName();
    std::unordered_set<int> getUsers();

private:
    int channel_id;
    std::string channel_name;
    std::unordered_set<int> channel_users;
};


#endif
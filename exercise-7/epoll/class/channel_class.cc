#include "channel_class.h"

Channel::Channel(std::string channel_nm)
{
  channel_name = channel_nm;
}
void Channel::addUser(int client_fd)
{
  auto check_user=(channel_users.find(client_fd)!=(channel_users.end()));
  check_error(check_user,"User Already Exists");
  channel_users.insert(client_fd);
}
void Channel::removeUser(int client_fd)
{
  auto check_user=(channel_users.find(client_fd)==(channel_users.end()));
  check_error(check_user,"User Does Not Exist");
  channel_users.erase(client_fd);
}
int Channel::getID(){
  return channel_id;
}
std::string Channel::getName(){
  return channel_name;
}
std::unordered_set<int> Channel::getUsers(){
  return channel_users;
}

#ifndef SERVER_H
#define SERVER_H

#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string>
#include <unordered_set>
#include <sys/epoll.h>
#include "../shared/shared.h"
#include "../manager/client_manager.h"

#define MAX_EVENTS 5

class Server
{
public:
  Server(int port);
  ~Server();
  void start();
  std::string get_username(int client_fd) const;
  bool is_logged_in(int client_fd) const;
  void add_pending_username(int client_fd);
  void remove_pending_username(int client_fd);
  void set_client_username(int client_fd, const std::string &username);
  void remove_client_username(int client_fd);

private:
  int serv_port;
  int socket_fd;
  sockaddr_in serv_address;
  int epoll_fd;
  int event_count = 0;
  std::unordered_set<int> pending_usernames;
  std::unordered_map<int, std::string> client_usernames;

  ClientManager client_manager;

  struct epoll_event event, events[MAX_EVENTS];
  void e_poll_create();
  void e_poll_register();

  void set_socket_options(int sock, int opt);
  sockaddr_in create_address(int port);
  void bind_address_to_socket(int sock, sockaddr_in &address);
  void listen_on_socket(int sock);
  void start_listening_on_socket(int my_socket, sockaddr_in &address);
  void epoll_create();
  void handle_accept(int sock);
  // std::string_view read_msgs(int sock);
  void handle_connections(int sock, int port);
};

#endif
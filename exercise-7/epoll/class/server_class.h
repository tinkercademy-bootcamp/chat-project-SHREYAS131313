#ifndef SERVER_H
#define SERVER_H

#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <string>
#include <sys/epoll.h>
#include "../shared/shared.h"
#include "../manager/channel_manager.h"
#include "../manager/client_manager.h"

#define MAX_EVENTS 5

class Server
{
public:
  Server(int port);
  ~Server();
  void start();

private:
  int serv_port;
  int socket_fd;
  sockaddr_in serv_address;
  int epoll_fd;
  int event_count = 0;

  ChannelManager channel_manager;

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
  std::string_view read_msgs(int sock);
  void handle_connections(int sock, int port);
};

#endif
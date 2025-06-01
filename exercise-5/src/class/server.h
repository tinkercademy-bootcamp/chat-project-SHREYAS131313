#ifndef SERVER_H
#define SERVER_H

#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <string>
#include "../shared.h"

class Server
{
public:
  Server(int port);
  ~Server();
  void start();

private:
int serv_port;
int serv_socket;
sockaddr_in serv_address;
void set_socket_options(int sock, int opt) ;
sockaddr_in create_address(int port);
void bind_address_to_socket(int sock, sockaddr_in &address);
void listen_on_socket(int sock) ;
void start_listening_on_socket(int my_socket, sockaddr_in &address);
void handle_accept(int sock);
void handle_connections(int sock, int port);
};

#endif

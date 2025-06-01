#ifndef CLIENT_H
#define CLIENT_H

#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <string>
#include "../shared.h"

class Client{
  public:
  Client(int port,const std::string &ip);
  ~Client();
  void start();
  private:
    int cli_port;
  sockaddr_in serv_address;
  std::string serv_ip;
  int socket_fd;
  sockaddr_in create_address(const std::string &server_ip, int port);
  void connect_to_server(int sock, sockaddr_in &server_address);
  void send_and_receive_message(int sock, const std::string &message) ;
  std::string read_args(int argc, char *argv[]);

};

#endif

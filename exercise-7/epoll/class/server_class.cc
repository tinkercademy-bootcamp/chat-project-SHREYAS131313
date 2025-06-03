#include "server_class.h"

Server::Server(int port)
{
  serv_port = port;
  socket_fd = create_socket();
  serv_address = create_address(serv_port);
}
Server::~Server()
{
  close(socket_fd);
}

void Server::start()
{
  int my_socket = socket_fd;
  sockaddr_in address = serv_address;
  start_listening_on_socket(my_socket, address);
  std::cout << "Server listening on port " << serv_port << "\n";
  epoll_fd = epoll_create1(0);
  check_error(epoll_fd == -1, "Failed to create epoll file descriptor\n");
  event.events = EPOLLIN;
  event.data.fd = 0;
  handle_connections(my_socket, serv_port);
}

void Server::set_socket_options(int sock, int opt)
{
  auto err_code = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                             &opt, sizeof(opt));
  check_error(err_code < 0, "setsockopt() error\n");
}

sockaddr_in Server::create_address(int port)
{
  sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(port);
  return address;
}

void Server::bind_address_to_socket(int sock, sockaddr_in &address)
{
  auto err_code = bind(sock, (sockaddr *)&address, sizeof(address));
  check_error(err_code < 0, "bind failed\n");
}

void Server::listen_on_socket(int sock)
{
  auto err_code = listen(sock, 3);
  check_error(err_code < 0, "listen failed\n");
}

void Server::start_listening_on_socket(int my_socket, sockaddr_in &address)
{
  const int kSocketOptions = 1;
  set_socket_options(my_socket, kSocketOptions);

  bind_address_to_socket(my_socket, address);
  listen_on_socket(my_socket);
}
void Server::epoll_create(){
  
}

void Server::handle_accept(int sock)
{
  const int kBufferSize = 1024;
  char buffer[kBufferSize] = {0};
  ssize_t read_size = read(sock, buffer, kBufferSize);

  check_error(read_size < 0,
              "Read error on client socket " + std::to_string(sock));
  if (read_size > 0)
  {
    std::cout << "Received:" << buffer << "\n";
    send(sock, buffer, read_size, 0);
    std::cout << "Echo message sent\n";
  }
  else if (read_size == 0)
  {
    std::cout << "Client disconnected.\n";
  }
  else
  {
    std::cerr << "Read error on client socket " << sock << "\n";
  }
  close(sock);
}

void Server::handle_connections(int sock, int port)
{
  sockaddr_in address = create_address(port);
  socklen_t address_size = sizeof(address);

  while (true)
  {
    int accepted_socket = accept(sock, (sockaddr *)&address, &address_size);
    check_error(accepted_socket < 0, "Accept error n ");
    handle_accept(accepted_socket);
  }
}
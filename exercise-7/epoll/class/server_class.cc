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

void Server::e_poll_register()
{
  check_error(epoll_ctl(epoll_fd, EPOLL_CTL_ADD, socket_fd, &event) == -1, "Failed to add file descriptor to epoll\n");
}
void Server::e_poll_create()
{
  epoll_fd = epoll_create1(0);
  check_error(epoll_fd == -1, "Failed to create epoll file descriptor\n");
  event.events = EPOLLIN;
  event.data.fd = socket_fd;
  e_poll_register();
}

void Server::start()
{
  int my_socket = socket_fd;
  sockaddr_in address = serv_address;
  start_listening_on_socket(my_socket, address);
  std::cout << "Server listening on port " << serv_port << "\n";
  e_poll_create();
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
// std::string_view Server::read_msgs(int sock)
// {
//   const int kBufferSize = 1024;
//   char buffer[kBufferSize] = {0};
//   ssize_t read_size = read(sock, buffer, kBufferSize);

//   check_error(read_size < 0,
//               "Read error on client socket " + std::to_string(sock));

//   if (read_size > 0)
//   {
//     std::string_view msg_recv(buffer, read_size);
//     return msg_recv;
//   }
//   else if (read_size == 0)
//   {
//     return "";
//   }
//   else
//   {
//     std::cerr << "Read error on client socket " << sock << "\n";
//     return "";
//   }
// }

void Server::handle_accept(int client_fd)
{
  const int kBufferSize = 1024;
  char buffer[kBufferSize] = {0};
  ssize_t read_size = read(client_fd, buffer, kBufferSize);

  check_error(read_size < 0,
              "Read error on client socket " + std::to_string(client_fd));
  if (read_size > 0)
  {
    std::cout << "Received:" << buffer << "\n";

    fcntl(client_fd, F_SETFL, O_NONBLOCK);
    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = client_fd;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &ev);

    send(client_fd, "Enter username: ", 16, 0);
    add_pending_username(client_fd);
  }

  else if (read_size == 0)
  {
    std::cout << "Client disconnected.\n";
    close(client_fd);
  }
  else
  {
    std::cerr << "Read error on client socket " << client_fd << "\n";
    close(client_fd);
  }
  // close(sock);
}
std::string Server::get_username(int client_fd) const
{
  auto it = client_usernames.find(client_fd);
  if (it != client_usernames.end())
  {
    return it->second;
  }
  return "";
}
bool Server::is_logged_in(int client_fd) const
{
  return client_usernames.find(client_fd) != client_usernames.end();
}

void Server::add_pending_username(int client_fd)
{
  pending_usernames.insert(client_fd);
}

void Server::remove_pending_username(int client_fd)
{
  pending_usernames.erase(client_fd);
}

void Server::set_client_username(int client_fd, const std::string &username)
{
  client_usernames[client_fd] = username;
}

void Server::remove_client_username(int client_fd)
{
  client_usernames.erase(client_fd);
}

void Server::handle_connections(int sock, int port)
{
  sockaddr_in address = create_address(port);
  socklen_t address_size = sizeof(address);
  while (true)
  {
    event_count = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
    check_error(event_count < 0, "epoll_wait failed");
    for (int i = 0; i < event_count; i++)
    {
      int fd = events[i].data.fd;
      if (fd == sock)
      {
        address_size = sizeof(address); // reset before accept
        int client_fd = accept(sock, (sockaddr *)&address, &address_size);
        std::cout<<"Client fd = "<<client_fd<<'\n';
        check_error(client_fd < 0, "Accept error n ");

        handle_accept(client_fd);
      }
      else
      {
        char buffer[1024] = {0};
        int bytes_read = recv(fd, buffer, sizeof(buffer), 0);

        if (bytes_read <= 0)
        {
          // Client disconnected or error
          close(fd);
          epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, NULL);
          client_manager.removeClient(fd);
          remove_pending_username(fd);
          continue;
        }
        else
        {
          std::string recv_msg(buffer);
          std::cout << fd << " " << recv_msg << '\n';
          if (pending_usernames.count(fd))
          {
            // First message: treat as username
            client_manager.setUsername(fd, recv_msg);
            remove_pending_username(fd);
            send(fd, "Welcome! Use /list /create /join or send a message\n", 52, 0);
          }
          else
          {
            std::cout<<"000"<<'\n';
            // Handle command or message
            // client_manager.handle_client_message(fd, recv_msg);
          }
        }
      }
    }
  }
}
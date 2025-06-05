#include "client_class.h"

Client::Client(int port, const std::string &ip)
{
  cli_port = port;
  serv_ip = ip;
  serv_address = create_address(ip, port);
}
Client::~Client()
{
  close(socket_fd);
}
int Client::start(int argc, char *argv[])
{
  std::string message = read_args(argc, argv);
  int my_socket = create_socket();
  sockaddr_in server_address = create_address(serv_ip, cli_port);
  connect_to_server(my_socket, server_address);
  send_and_receive_message(my_socket, message);

  std::string username;
  std::getline(std::cin, username);
  send(my_socket, username.c_str(), username.size(), 0);
  const int kBufferSize = 1024;
  char buffer[kBufferSize] = {0};
  ssize_t read_size = read(my_socket, buffer, kBufferSize);
  if (read_size > 0)
  {
    std::cout << buffer << std::flush; //  "Welcome! Use /list /create ..."
  }

  // Set up epoll
  int epoll_fd = epoll_create1(0);
  struct epoll_event ev, events[2];

  // Add socket and STDIN_FILENO to epoll , to check if you are taking input or you are receiving one.
  // Add my_socket to epoll
  ev.events = EPOLLIN;
  ev.data.fd = my_socket;
  epoll_ctl(epoll_fd, EPOLL_CTL_ADD, my_socket, &ev);

  // Add STDIN_FILENO to epoll
  ev.events = EPOLLIN;
  ev.data.fd = STDIN_FILENO;
  epoll_ctl(epoll_fd, EPOLL_CTL_ADD, STDIN_FILENO, &ev);

  while (true)
  {

    int event_count = epoll_wait(epoll_fd, events, 2, -1);
    for (int i = 0; i < event_count; ++i)
    {
      int fd = events[i].data.fd;
      if (fd == STDIN_FILENO)
      {
        std::string input;
        std::getline(std::cin, input);
        send_and_receive_message(my_socket, input); // send and receive (acknowledgement from server)
        if (input == "/quit")
        {
          close(epoll_fd);
          close(my_socket);
          return 1;
        }
      }
      else if (fd == my_socket)
      {
        std::memset(buffer, 0, kBufferSize);
        ssize_t recv_size = read(my_socket, buffer, kBufferSize);
        if (recv_size <= 0)
        {
          std::cout << "Server disconnected.\n";
          return 0;
          break;
        }
        std::cout << buffer <<'\n';
      }
    }
  }
  close(epoll_fd);
  close(my_socket);
  return 1;
}

sockaddr_in Client::create_address(const std::string &server_ip, int port)
{
  sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_port = htons(port);

  // Convert the server IP address to a binary format
  auto err_code = inet_pton(AF_INET, server_ip.c_str(), &address.sin_addr);
  check_error(err_code <= 0, "Invalid address/ Address not supported.\n");
  return address;
}

void Client::connect_to_server(int sock, sockaddr_in &server_address)
{
  auto err_code =
      connect(sock, (sockaddr *)&server_address, sizeof(server_address));
  check_error(err_code < 0, "Connection Failed.\n");
}

void Client::send_and_receive_message(int sock, const std::string &message)
{
  const int kBufferSize = 1024;
  char recv_buffer[kBufferSize] = {0};

  // Send the message to the server
  send(sock, message.c_str(), message.size(), 0);
  std::cout << "Sent: " << message << "\n";

  // Receive response from the server
  ssize_t read_size = read(sock, recv_buffer, kBufferSize);
  check_error(read_size < 0, "Read error.\n");
  if (read_size > 0)
  {
    std::cout << "Received: " << recv_buffer << "\n"; // reads Enter username
  }
  else if (read_size == 0)
  {
    std::cout << "Server closed connection.\n";
  }
}

std::string Client::read_args(int argc, char *argv[])
{
  std::string message = "Hello from client";
  if (argc == 1)
  {
    std::cout << "Usage: " << argv[0] << " <message>\n";
    exit(EXIT_FAILURE);
  }
  if (argc > 1)
  {
    message = argv[1];
  }
  return message;
}
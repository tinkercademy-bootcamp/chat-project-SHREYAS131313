#include "client.h"

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
void Client::start(int argc,char *argv[])
{
  std::string message = read_args(argc, argv);
  int my_socket = create_socket();
  sockaddr_in server_address = create_address(serv_ip, cli_port);
  connect_to_server(my_socket, server_address);
  send_and_receive_message(my_socket, message);
  close(my_socket);
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
    std::cout << "Received: " << recv_buffer << "\n";
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
#include "shared.h"

void check_error(bool test, std::string error_message) {
  if (test) {
    std::cerr << error_message << "\n";
    exit(EXIT_FAILURE);
  }
}

int create_socket() {
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  check_error(sock < 0, "Socket creation error\n");
  return sock;
}
std::pair<std::string_view, std::string_view> parse_command(std::string_view input) {
    auto space_pos = input.find(' ');
    if (space_pos == std::string_view::npos) {
        return {input, ""}; // No arguments
    }
    return {input.substr(0, space_pos), input.substr(space_pos + 1)};
}

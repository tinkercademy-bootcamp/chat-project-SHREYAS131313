#ifndef MY_HEADER_H
#define MY_HEADER_H

#include <iostream>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <string>

void check_error(bool test, std::string error_message);
int create_socket();
// sockaddr_in create_address(int port);

#endif
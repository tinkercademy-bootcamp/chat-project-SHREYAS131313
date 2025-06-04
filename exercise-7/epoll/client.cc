#include "class/client_class.h"
// void choose_username(){
//   std::cout<<"Choose Username\n";
//   std::string username;
//   std::cin>>username;
// }

int main(int argc, char *argv[])
{
  const int kPort = 8080;
  const std::string kServerAddress = "127.0.0.1";
  Client Client(kPort,kServerAddress);
 Client.start(argc,argv);
  
  return 0;
}
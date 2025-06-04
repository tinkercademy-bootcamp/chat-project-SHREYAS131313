#include "class/client_class.h"
void choose_username(){
  std::cout<<"Choose Username\n";
  std::string username;
  std::cin>>username;
}

int main(int argc, char *argv[])
{
  const int kPort = 8080;
  const std::string kServerAddress = "127.0.0.1";
  Client Client(kPort,kServerAddress);
  int conn_msg_res=Client.start(argc,argv);
  if(conn_msg_res==1){
    choose_username();
  }
  return 0;
}
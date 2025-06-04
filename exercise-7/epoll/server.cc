#include "class/server_class.h"


int main(){
  int kport=8080;
  Server server(kport);
  server.start();
  return 0;
}
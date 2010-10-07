#include "network/server.h"

int main(int argc, char *argv[]) {
  impdungeon::Server server(60000);
  
  server.Init();
  server.Run();

  return 0;
}

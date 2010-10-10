#include "client/client.h"

int main(int argc, char *argv[]) {
  impdungeon::Client client("127.0.0.1", 50000);
  
  client.Init();
  client.Run();

  return 0;
}

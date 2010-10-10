#include "server/server.h"

#include "logic/network/networkerror.h"

int main(int argc, char *argv[]) {
  impdungeon::Server server(50000);
  
  try {
    server.Init();
    server.Run();
  }
  catch (impdungeon::NetworkError &network_error) {
    std::cout << "Server quit with the following message: "
              << network_error.what() << std::endl;
  }

  return 0;
}

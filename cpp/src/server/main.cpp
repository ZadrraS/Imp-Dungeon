#include "server/world.h"

#include <iostream>

#include "logic/network/networkerror.h"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "USAGE: " << argv[0] << " <port>" << std::endl;
    return 0;
  }
  try {
    int port = atoi(argv[1]);
    if (port < 1 || port > 65535)
      throw impdungeon::NetworkError("Invalid port specified.");

    impdungeon::server::World world(port, "box", "entities.json", "items.json") ;
    world.Init();
    world.Run();
  }
  catch (impdungeon::NetworkError &network_error) {
    std::cout << "Server quit with the following message: "
              << network_error.what() << std::endl;
  }

  return 0;
}

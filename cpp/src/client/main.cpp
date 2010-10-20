#include "client/world.h"

#include <iostream>
#include <exception>

#include "logic/network/networkerror.h"

int main(int argc, char *argv[]) {
  if (argc != 3) {
    std::cout << "USAGE: " << argv[0] << " <ip> <port>" << std::endl;
    return 0;
  }
  try {
    std::string ip = argv[1];
    int port = atoi(argv[2]);
    if (port < 1 || port > 65535)
      throw impdungeon::NetworkError("Invalid port specified.");

    impdungeon::client::World world(ip, port);

    world.Init();
    world.Run();
  }
  catch (impdungeon::NetworkError &network_error) {
    std::cout << "Client quit with the following message: "
              << network_error.what() << std::endl;
  }
  return 0;
}

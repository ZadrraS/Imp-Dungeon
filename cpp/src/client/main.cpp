#include "client/world.h"

#include <iostream>
#include <exception>

#include "logic/network/networkerror.h"

int main(int argc, char *argv[]) {
  try {
    impdungeon::client::World world("127.0.0.1", 50000);

    world.Init();
    world.Run();
  }
  catch (impdungeon::NetworkError &network_error) {
    std::cout << "Client quit with the following message: "
              << network_error.what() << std::endl;
  }
  return 0;
}

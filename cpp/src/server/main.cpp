#include "server/world.h"

#include <iostream>

#include "logic/network/networkerror.h"

int main(int argc, char *argv[]) {
  impdungeon::server::World world("box", "entities.json", "items.json") ;
  
  try {
    world.Init();
    world.Run();
  }
  catch (impdungeon::NetworkError &network_error) {
    std::cout << "Server quit with the following message: "
              << network_error.what() << std::endl;
  }

  return 0;
}

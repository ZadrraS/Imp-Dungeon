#include "client/client.h"

#include <iostream>

#include "logic/network/networkerror.h"

int main(int argc, char *argv[]) {
  try {
    impdungeon::Client client("127.0.0.1", 50000);
    
    client.Init();
    client.Run();
  }
  catch (impdungeon::NetworkError &network_error) {
    std::cout << "Client quit with the following message: "
              << network_error.what() << std::endl;
  }
  return 0;
}

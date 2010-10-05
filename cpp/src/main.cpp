#include "world.h"

int main(int argc, char *argv[]) {
  impdungeon::World world("box", "items.json", "entities.json");
  
  world.Run();

  return 0;
}

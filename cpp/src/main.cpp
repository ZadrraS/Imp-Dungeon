#include "world.h"

int main(int argc, char *argv[]) {
  impdungeon::World world;

  world.Init("box", "entities.json");
  world.Run();

  world.Destroy();

  return 0;
}

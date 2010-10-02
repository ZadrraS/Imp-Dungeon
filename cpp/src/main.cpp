#include "world.h"

int main(int argc, char *argv[]) {
  impdungeon::World world;

  world.Init("box.txt", "entities.json");
  world.Run();

  world.Destroy();

  return 0;
}

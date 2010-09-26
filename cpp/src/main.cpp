#include "world.h"

int main(int argc, char *argv[]) {
    impdungeon::World world;

    world.Init();
    world.Run();

    return 0;
}

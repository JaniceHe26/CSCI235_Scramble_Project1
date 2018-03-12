#include "Game.h"

using namespace std;

int main(int argc, char **argv) {
    srand(time(0));
    Game scramble = Game();

    if (argc > 1) {
        scramble.run(argv[1]);
    } else {
        scramble.run("temp path");
    }

   return 0;
}
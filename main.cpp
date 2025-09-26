#include "game.h"
#include <cassert>
#include <iostream>

int main()
{
    Game game;
    game.SetMaxFps(60);
    game.Start("CeciliaCraftedMine", 1280, 720, false);

    return 0;
}

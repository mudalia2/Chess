//
//  main.cpp
//  Chess
//
//  Created by Vikram Mudaliar on 9/16/17.
//  Copyright © 2017 VR. All rights reserved.
//

#include <iostream>
#include "Game.hpp"


int main(int argc, const char * argv[]) {
    // insert code here...
    
    Game * game = new Game();
    game->game_loop();
    return 0;
}

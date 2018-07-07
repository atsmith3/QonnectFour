#include "game.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

int main() {
    Game g;

    while(1) {
        g.makeMove(rand()%7, RED);
        g.print();
        if(g.complete(RED)) break;
        g.makeMove(rand()%7, YELLOW);
        g.print();
        if(g.complete(YELLOW)) break;
    }
    return 0;
}

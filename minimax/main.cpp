#include "game.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

int main() {
    Game g;
    int red_move, yellow_move;

    while(!g.staleMate()) {
        red_move = g.bestMove(RED,7);
        printf("Best Move RED     = %i\n", red_move);
        g.makeMove(red_move, RED);
        g.print();
        if(g.complete(RED)) { 
            printf("RED WINS!\n");
            break;
        }
        yellow_move = g.bestMove(YELLOW,3);
        printf("Best Move YELLOW  = %i\n", yellow_move);
        g.makeMove(yellow_move, YELLOW);
        g.print();
        if(g.complete(YELLOW)) {
            printf("YELLOW WINS!\n");
            break;
        }
    }
    return 0;
}

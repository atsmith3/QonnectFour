#include "game.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>



int main() {
    int red_move, yellow_move, move;
    int player = 2;
    std::string GameState;
    
    /* TODO: Call Python code to grab the game state */
    
    //printf("Enter 1 to be RED, enter 2 to be YELLOW: "); 
    //scanf("%i\n", &player);

    Game g;
    /*
    //Bottom Row
    g.makeMove(0, YELLOW);
    g.makeMove(1, YELLOW);
    g.makeMove(2, RED);
    g.makeMove(3, YELLOW);
    g.makeMove(4, RED);
    g.makeMove(5, YELLOW);
    g.makeMove(6, RED);
    g.print();

    //Second R row
    g.makeMove(0,RED);
    g.makeMove(1,YELLOW);
    g.makeMove(2,YELLOW);
    g.makeMove(3,RED);
    g.makeMove(4,YELLOW);
    g.makeMove(5,YELLOW);
    
    //Third Row
    g.makeMove(0,YELLOW);
    g.makeMove(1,YELLOW);
    g.makeMove(2,RED);
    g.makeMove(5,RED);
    

    std::cout << "Current Game State: \n";
    g.print();
    yellow_move = g.bestMove(YELLOW, 7);
    std::cout << "Best Move " << yellow_move << "\n";
    g.makeMove(yellow_move, YELLOW);
    g.print();
    */
 
    g.print();
    while(!g.staleMate()) {
        if(player == 1) {
            printf("Enter 0 - 6 to make move: ");
            scanf("%i",&move);
            g.makeMove(move, RED);
        }
        else {
            red_move = g.bestMove(RED,7);
            printf("Best Move RED     = %i\n", red_move);
            g.makeMove(red_move, RED);
        }
        g.print();

        if(g.complete(RED)) { 
            printf("RED WINS!\n");
            break;
        }

        if(player == 2) {
            printf("Enter 0 - 6 to make move: ");
            scanf("%i",&move);
            g.makeMove(move, YELLOW);
        }
        else {
            yellow_move = g.bestMove(YELLOW,7);
            printf("Best Move YELLOW  = %i\n", yellow_move);
            g.makeMove(yellow_move, YELLOW);
        }
        g.print();
        if(g.complete(YELLOW)) {
            printf("YELLOW WINS!\n");
            break;
        }
    }

    /* Uncomment to play a game
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
    } */
    return 0;
}

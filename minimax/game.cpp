#include "game.h"
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <queue>
#include <stdlib.h>
#include <iostream>

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

#define W1IR 1
#define W2IR 10
#define W3IR 100

Game::Game() {
    for(int i = 0; i < HEIGHT*WIDTH; i++) {
        board[i] = EMPTY;
    }
}

Game::Game(const Game& obj) {
    for(int i = 0; i < HEIGHT*WIDTH; i++) {
        board[i] = obj.get(i);
    }
}

Game::~Game() {
    /* Nothing */
}

void Game::print() {
    for(int i = 0; i < HEIGHT; i++) {
        printf("-----------------------------\n");
        for(int j = 0; j < WIDTH; j++) {
            printf("| ");
            if (get(i*WIDTH + j) == EMPTY) {
                printf(" ");
            }
            else if (get(i*WIDTH + j) == RED) {
                printf("%s#", KRED);
            }
            else {
                printf("%s#", KYEL);
            }

            if(j == WIDTH - 1) printf("%s |\n", KNRM);
            else printf("%s ", KNRM);
        }
    }
    printf("-----------------------------\n\n");
}

char Game::get(coord pos) const {
    return board[pos.y*WIDTH + pos.x];
}

char Game::get(int i) const {
    return board[i];
}

void Game::set(coord pos, char value) {
    board[pos.y*WIDTH + pos.x] = value;
}

void Game::set(int i, char value) {
    board[i] = value;
}

bool Game::validMove(int pos, char player) {
    if(board[pos] == EMPTY) return true;
    return false;
}

Game& Game::operator=(const Game& obj) {
    for(int i = 0; i < HEIGHT*WIDTH; i++) {
        board[i] = obj.get(i);
    }
    return *this;
}

bool Game::complete(char player) {
     for(int i = 0; i < HEIGHT - 3; i++) {
         for(int j = 0; j < WIDTH - 3; j++) {
             if(board[(i + 0)*WIDTH + (j + 0)] == player &&
                board[(i + 1)*WIDTH + (j + 1)] == player &&
                board[(i + 2)*WIDTH + (j + 2)] == player &&
                board[(i + 3)*WIDTH + (j + 3)] == player) {
                 return true;
             }
             if(board[(i + 0)*WIDTH + (j + 3)] == player &&
                board[(i + 1)*WIDTH + (j + 2)] == player &&
                board[(i + 2)*WIDTH + (j + 1)] == player &&
                board[(i + 3)*WIDTH + (j + 0)] == player) {
                 return true;
             }
         }
     }
     for(int i = 0; i < HEIGHT; i++) {
         for(int j = 0; j < WIDTH - 3; j++) {
             if(board[(i + 0)*WIDTH + (j + 0)] == player &&
                board[(i + 0)*WIDTH + (j + 1)] == player &&
                board[(i + 0)*WIDTH + (j + 2)] == player &&
                board[(i + 0)*WIDTH + (j + 3)] == player) {
                 return true;
             }
         }
     }
     for(int i = 0; i < HEIGHT - 3; i++) {
         for(int j = 0; j < WIDTH; j++) {
             if(board[(i + 0)*WIDTH + (j + 0)] == player &&
                board[(i + 1)*WIDTH + (j + 0)] == player &&
                board[(i + 2)*WIDTH + (j + 0)] == player &&
                board[(i + 3)*WIDTH + (j + 0)] == player) {
                 return true;
             }
         }
     }
     return false;
}

bool Game::staleMate() {
    for(int i = 0; i < WIDTH; i++) {
        if(validMove(i, RED)) return false;
    }
    return true;
}

void Game::makeMove(int pos, char player) {
    for(int i = HEIGHT - 1; i >= 0; i--) {
        if(board[i*WIDTH + pos] == EMPTY) {
            board[i*WIDTH + pos] = player; 
            return;
        }
    }
}

int Game::evalFunction(char player) {
    int  pattern_class[4] = {0, 0, 0, 0};
    int sum = 0;
    int intermediate;
 
    // Check Diagonal Left for winning window
    for(int j = 0; j < HEIGHT - 3; j++) {
        for(int i = 0; i < WIDTH - 3; i++) {
            if((board[(j + 0)*WIDTH + (i + 0)] == player || board[(j + 0)*HEIGHT + (i + 0)] == EMPTY) &&
               (board[(j + 1)*WIDTH + (i + 1)] == player || board[(j + 1)*HEIGHT + (i + 1)] == EMPTY) && 
               (board[(j + 2)*WIDTH + (i + 2)] == player || board[(j + 2)*HEIGHT + (i + 2)] == EMPTY) && 
               (board[(j + 3)*WIDTH + (i + 3)] == player || board[(j + 3)*HEIGHT + (i + 3)] == EMPTY)) { 
                intermediate = 0;
                for(int k = 0; k < 4; k++) {
                    //Count up the quantity in the window
                    if(board[(j + k)*WIDTH + (i + k)] != EMPTY) intermediate++;
                }
                switch(intermediate) {
                    case 1: {
                        pattern_class[0]++;
                        break;
                    }
                    case 2: {
                        pattern_class[1]++;
                        break;
                    }
                    case 3: {
                        pattern_class[2]++;
                        break;
                    }
                    case 4: {
                        pattern_class[3]++;
                        break;
                    }
                    default: {
                       break;
                    }
                }
            } 
        }
    }
    // Check Diagonal Right
    for(int j = 0; j < HEIGHT - 3; j++) {
        for(int i = 0; i < WIDTH - 3; i++) {
            if((board[(j + 3)*WIDTH + (i + 0)] == player || board[(j + 3)*WIDTH + (i + 0)] == EMPTY) &&
               (board[(j + 2)*WIDTH + (i + 1)] == player || board[(j + 2)*WIDTH + (i + 1)] == EMPTY) && 
               (board[(j + 1)*WIDTH + (i + 2)] == player || board[(j + 1)*WIDTH + (i + 2)] == EMPTY) && 
               (board[(j + 0)*WIDTH + (i + 3)] == player || board[(j + 0)*WIDTH + (i + 3)] == EMPTY)) { 
                intermediate = 0;
                for(int k = 0; k < 4; k++) {
                    //Count up the quantity in the window
                    if(board[(j - k)*WIDTH + (i + k)] != EMPTY) intermediate++;
                }
                switch(intermediate) {
                    case 1: {
                        pattern_class[0]++;
                        break;
                    }
                    case 2: {
                        pattern_class[1]++;
                        break;
                    }
                    case 3: {
                        pattern_class[2]++;
                        break;
                    }
                    case 4: {
                        pattern_class[3]++;
                        break;
                    }
                    default: {
                       break;
                    }
                }
            } 
        }
    }

    // Check Vertical
    for(int j = 0; j < HEIGHT - 3; j++) {
        for(int i = 0; i < WIDTH - 0; i++) {
            if((board[(j + 0)*WIDTH + (i + 0)] == player || board[(j + 0)*WIDTH + (i + 0)] == EMPTY) &&
               (board[(j + 1)*WIDTH + (i + 0)] == player || board[(j + 1)*WIDTH + (i + 0)] == EMPTY) && 
               (board[(j + 2)*WIDTH + (i + 0)] == player || board[(j + 2)*WIDTH + (i + 0)] == EMPTY) && 
               (board[(j + 3)*WIDTH + (i + 0)] == player || board[(j + 3)*WIDTH + (i + 0)] == EMPTY)) { 
                intermediate = 0;
                for(int k = 0; k < 4; k++) {
                    //Count up the quantity in the window
                    if(board[(j + k)*WIDTH + (i + 0)] != EMPTY) intermediate++;
                }
                switch(intermediate) {
                    case 1: {
                        pattern_class[0]++;
                        break;
                    }
                    case 2: {
                        pattern_class[1]++;
                        break;
                    }
                    case 3: {
                        pattern_class[2]++;
                        break;
                    }
                    case 4: {
                        pattern_class[3]++;
                        break;
                    }
                    default: {
                       break;
                    }
                }
            } 
        }
    }

    // Check Horizontal
    for(int j = 0; j < HEIGHT; j++) {
        for(int i = 0; i < WIDTH - 3; i++) {
            if((board[(j + 0)*WIDTH + (i + 0)] == player || board[(j + 0)*WIDTH + (i + 0)] == EMPTY) &&
               (board[(j + 0)*WIDTH + (i + 1)] == player || board[(j + 0)*WIDTH + (i + 1)] == EMPTY) && 
               (board[(j + 0)*WIDTH + (i + 2)] == player || board[(j + 0)*WIDTH + (i + 2)] == EMPTY) && 
               (board[(j + 0)*WIDTH + (i + 3)] == player || board[(j + 0)*WIDTH + (i + 3)] == EMPTY)) { 
                intermediate = 0;
                for(int k = 0; k < 4; k++) {
                    //Count up the quantity in the window
                    if(board[(j + 0)*WIDTH + (i + k)] != EMPTY) intermediate++;
                }
                switch(intermediate) {
                    case 1: {
                        pattern_class[0]++;
                        break;
                    }
                    case 2: {
                        pattern_class[1]++;
                        break;
                    }
                    case 3: {
                        pattern_class[2]++;
                        break;
                    }
                    case 4: {
                        pattern_class[3]++;
                        break;
                    }
                    default: {
                       break;
                    }
                }
            } 
        }
    }


    // Weight the patterns and sum:
    sum = W1IR*pattern_class[0] + W2IR*pattern_class[1] + W3IR*pattern_class[2];

    return sum;
}

/* Returns the best move */
int Game::bestMove(char player, int depth) {
    Game state;
    std::vector<int> val;
    std::vector<int> pos;
    int best_val;
    int best_pos;
    
    /* Max */
    if(player == RED) {
        best_val = -1000000;
        for(int i = 0; i < WIDTH; i++) {
            if(validMove(i, player)) {
                state = *this;
                state.makeMove(i, player);
                val.push_back(miniMax(state, YELLOW, depth - 1));
                pos.push_back(i);
            }
        }
        /* Return the best move */
        for(size_t i = 0; i < val.size(); i++) {
            if(val[i] > best_val) {
                 best_val = val[i];
                 best_pos = pos[i];
            }
        }
//        printf("Best Move RED %i with Value %i\n", best_pos, best_val);
        return best_pos;
    }
    
    /* Min */
    if(player == YELLOW) {
        best_val = 1000000;
        for(int i = 0; i < WIDTH; i++) {
            if(validMove(i, player)) {
                state = *this;
                state.makeMove(i, player);
                val.push_back(miniMax(state, RED, depth - 1));
                pos.push_back(i);
            }
        }
        /* Return the best move */
        for(size_t i = 0; i < val.size(); i++) {
            if(val[i] < best_val) {
                 best_val = val[i];
                 best_pos = pos[i];
            }
        }
//        printf("Best Move YELLOW %i with Value %i\n", best_pos, best_val);
        return best_pos;
    }
    return 0;
}

int Game::miniMax(Game g, char player, int depth) {
    Game state;
    std::vector<int> val;
    std::vector<int> pos;
    int best_val;
    int best_pos;
    
    /* Terminal Node */
    if(g.complete(RED)) {
         return 10000;
    }
    if(g.complete(YELLOW)) {
         return -10000;
    }

    /* Maximum Depth */
    if(depth == 0) {
//         printf("HIT_DEPTH\n");
         if(player == RED) return g.evalFunction(RED);
         else return -g.evalFunction(YELLOW);
    }
    
    /* Max */
    if(player == RED) {
        best_val = -1000000;
        for(int i = 0; i < WIDTH; i++) {
            if(g.validMove(i, player)) {
                state = g;
                state.makeMove(i, player);
                val.push_back(miniMax(state, YELLOW, depth - 1));
                pos.push_back(i);
            }
        }
        /* Return the best move */
        for(size_t i = 0; i < val.size(); i++) {
            if(val[i] > best_val) {
                 best_val = val[i];
                 best_pos = pos[i];
            }
        }
        return best_val;
    }
    
    /* Min */
    if(player == YELLOW) {
        best_val = 1000000;
        for(int i = 0; i < WIDTH; i++) {
            if(g.validMove(i, player)) {
                state = g;
                state.makeMove(i, player);
                val.push_back(miniMax(state, RED, depth - 1));
                pos.push_back(i);
            }
        }
        /* Return the best move */
        for(size_t i = 0; i < val.size(); i++) {
            if(val[i] < best_val) {
                 best_val = val[i];
                 best_pos = pos[i];
            }
        }
        return best_val;
    }
    return 0;
}

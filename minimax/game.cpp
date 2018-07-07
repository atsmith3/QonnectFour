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
            if (get(i*HEIGHT + j) == EMPTY) {
                printf(" ");
            }
            else if (get(i*HEIGHT + j) == RED) {
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
    return board[pos.y*HEIGHT + pos.x];
}

char Game::get(int i) const {
    return board[i];
}

void Game::set(coord pos, char value) {
    board[pos.y*HEIGHT + pos.x] = value;
}

void Game::set(int i, char value) {
    board[i] = value;
}

bool validMove(coord pos, char player) {
    /* TODO Check Horizontal */
    return true;
}

bool complete() {
    /* TODO Check for winning condition */
     return true;
}

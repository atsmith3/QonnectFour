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

bool Game::validMove(int pos, char player) {
    if(board[pos] == EMPTY) return true;
    return false;
}

bool Game::complete(char player) {
     for(int i = 0; i < HEIGHT - 3; i++) {
         for(int j = 0; j < WIDTH - 3; j++) {
             if(board[(i + 0)*HEIGHT + (j + 0)] == player &&
                board[(i + 1)*HEIGHT + (j + 0)] == player &&
                board[(i + 2)*HEIGHT + (j + 0)] == player &&
                board[(i + 3)*HEIGHT + (j + 0)] == player) {
                 return true;
             }
             if(board[(i + 0)*HEIGHT + (j + 0)] == player &&
                board[(i + 0)*HEIGHT + (j + 1)] == player &&
                board[(i + 0)*HEIGHT + (j + 2)] == player &&
                board[(i + 0)*HEIGHT + (j + 3)] == player) {
                 return true;
             }
             if(board[(i + 0)*HEIGHT + (j + 0)] == player &&
                board[(i + 1)*HEIGHT + (j + 1)] == player &&
                board[(i + 2)*HEIGHT + (j + 2)] == player &&
                board[(i + 3)*HEIGHT + (j + 3)] == player) {
                 return true;
             }
             if(board[(i + 0)*HEIGHT + (j + 3)] == player &&
                board[(i + 1)*HEIGHT + (j + 2)] == player &&
                board[(i + 2)*HEIGHT + (j + 1)] == player &&
                board[(i + 3)*HEIGHT + (j + 0)] == player) {
                 return true;
             }
         }
     }
     return false;
}

void Game::makeMove(int pos, char player) {
    for(int i = HEIGHT - 1; i >= 0; i--) {
        if(board[i*HEIGHT + pos] == EMPTY) {
            board[i*HEIGHT + pos] = player; 
            return;
        }
    }
}

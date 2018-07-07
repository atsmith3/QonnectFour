#ifndef GAME_H
#define GAME_H

#define RED     1
#define YELLOW  2
#define EMPTY   3

#define HEIGHT 6
#define WIDTH 7

typedef struct coord_t {
    int x;
    int y;
} coord;

class Game {
  public:
    Game();
    Game(const char* board);
    ~Game();
    Game(const Game& obj);

    /* Methods */
    void print();
    char get(coord pos) const;
    char get(int pos) const;
    void set(coord pos, char value);
    void set(int pos, char value);
    bool validMove(int pos, char player);
    bool complete(char player);
    bool staleMate();
    void makeMove(int pos, char player);
    int  evalFunction(char player);
    int bestMove(char player, int depth);
    Game& operator=(const Game& obj);


  private:
    char board[HEIGHT*WIDTH];
    
    /* Methods */
    int miniMax(Game g, char player, int depth);
};

#endif

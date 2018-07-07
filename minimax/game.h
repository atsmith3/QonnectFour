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
    bool validMove(coord pos, char player);
    bool complete();

  private:
    char board[HEIGHT*WIDTH];
};

#endif

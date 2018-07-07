#include "game.h"
#include <stdio.h>
#include <iostream>

int main() {
    Game g;

    g.set(1, YELLOW);
    g.print();
    g.set(2, RED);
    g.print();
    g.set(3, YELLOW);
    g.print();
    g.set(4, RED);
    g.print();
    g.set(5, YELLOW);
    g.print();

    return 0;
}

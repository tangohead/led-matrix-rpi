#include <stdio.h>

#include <thread>
#include <chrono>

#include "GameOfLife.cpp"

int main(){
    printf("Hello\n");

    GameOfLife g = GameOfLife(10, 10);
    g.print_grid();

    for(int i = 0; i < 10; i++)
    {
        g.iterate();
        printf("------------------\n");
        g.print_grid();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    return 0;
}
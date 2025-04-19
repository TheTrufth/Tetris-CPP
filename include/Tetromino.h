#pragma once
#include <SDL.h>
#include <vector>

class Tetromino
{
public:
    Tetromino();
    void update();
    void draw(SDL_Renderer *renderer);
    void reset();

private:
    int shape[4][4];
    int x, y; // position of the tetromino
};
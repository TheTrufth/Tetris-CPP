#include "Tetromino.h"

Tetromino::Tetromino()
{
    // Initialize the tetromino shape and position
    int tempShape[4][4] = {
        {1, 1, 1, 1}, // I shape
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}};
    std::memcpy(shape, tempShape, sizeof(tempShape));
    reset();
}

void Tetromino::reset()
{
    x = 3;
    y = 0;
}

void Tetromino::update()
{
    // Move the tetromino down
    y++;
    if (y > 16) // Assuming 20 rows in the grid
    {
        reset();
    }
}

void Tetromino::draw(SDL_Renderer *renderer)
{
    // Draw the tetromino
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // red color
    const int BLOCK_SIZE = 30;                        // Assuming each block is 30x30 pixels
    for (int row = 0; row < 4; ++row)
    {
        for (int col = 0; col < 4; ++col)
        {
            if (shape[row][col] != 0)
            {
                int px = (x + col) * BLOCK_SIZE;
                int py = (y + row) * BLOCK_SIZE;
                SDL_Rect block = {px, py, BLOCK_SIZE - 1, BLOCK_SIZE - 1};
                SDL_RenderFillRect(renderer, &block);
            }
        }
    }
}
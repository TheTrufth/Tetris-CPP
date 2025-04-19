#include <SDL.h>
#include <iostream>
#include "Tetromino.h"

const int GRID_WIDTH = 10;
const int GRID_HEIGHT = 20;
const int BLOCK_SIZE = 30;

const int PREVIEW_BOX_WIDTH = 6 * BLOCK_SIZE;                              // Width of the preview box (6x6 blocks)
const int SCREEN_WIDTH = GRID_WIDTH * BLOCK_SIZE + PREVIEW_BOX_WIDTH + 40; // Add padding for the preview box
const int SCREEN_HEIGHT = GRID_HEIGHT * BLOCK_SIZE;
const int FPS = 60;
const int FRAME_DELAY = 1000 / FPS;

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window *win = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                       SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND); // Enable alpha blending.

    if (!win || !renderer)
    {
        std::cerr << "SDL Initialization Failed!" << std::endl;
        SDL_Quit();
        return 1;
    }

    Tetromino tetromino;
    bool running = true;
    SDL_Event event;
    int frameCount = 0;

    while (running)
    {
        Uint32 frameStart = SDL_GetTicks();

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                running = false;
            else
                tetromino.handleInput(event);
        }

        // Logic
        if (frameCount % 30 == 0)
        {
            tetromino.update();
        }

        // Clear the screen first
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
        SDL_RenderClear(renderer);

        // Draw the grid
        SDL_SetRenderDrawColor(renderer, 80, 80, 80, 255); // Light gray grid
        for (int x = 0; x < GRID_WIDTH; ++x)
        {
            for (int y = 0; y < GRID_HEIGHT; ++y)
            {
                SDL_Rect block = {x * BLOCK_SIZE, y * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE};
                SDL_RenderDrawRect(renderer, &block); // Draw the grid cell
            }
        }

        // Draw the active Tetromino
        tetromino.draw(renderer);

        // Draw the next Tetromino preview to the right of the grid
        int previewOffsetX = GRID_WIDTH * BLOCK_SIZE + 20; // Offset to the right of the grid
        int previewOffsetY = 50;                           // Offset from the top
        tetromino.drawNextTetromino(renderer, previewOffsetX, previewOffsetY);

        // Present the renderer to the screen
        SDL_RenderPresent(renderer);

        Uint32 frameTime = SDL_GetTicks() - frameStart;
        if (FRAME_DELAY > frameTime)
            SDL_Delay(FRAME_DELAY - frameTime);

        ++frameCount;
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}

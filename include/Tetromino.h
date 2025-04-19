#ifndef TETROMINO_H
#define TETROMINO_H

#include <SDL.h>

class Tetromino
{
public:
    Tetromino();
    void reset();
    void update();
    void placeTetrominoInGrid();
    void clearCompletedRows();
    void handleInput(SDL_Event &e);
    void rotate();
    void draw(SDL_Renderer *renderer);

    int getMinX() const;
    int getMaxX() const;
    int getHeight() const;
    int getWidth() const;

    bool checkCollision(int newX, int newY);

    // Static functions to set and get the grid
    static const int BLOCK_SIZE = 30;
    static const int GRID_WIDTH = 10;
    static const int GRID_HEIGHT = 20;
    static void setGrid(int grid[GRID_HEIGHT][GRID_WIDTH]);
    static int grid[GRID_HEIGHT][GRID_WIDTH]; // Game grid
    static SDL_Color tetrominoColors[7];

private:
    int x, y;        // Position on the grid
    int shape[4][4]; // Current shape (rotated)

    // Predefined shapes for each tetromino, each with 4 rotations
    static const int shapes[7][4][4][4]; // 7 shapes, each having 4 rotations (4x4 matrices)
    int currentShapeIndex;               // To track which shape is currently being used
    int rotationIndex;                   // Current rotation of the tetromino
    SDL_Color color;

    void setShape(int shapeIndex, int rotationIndex);
    bool checkCollision(int xOffset, int yOffset) const;
};

#endif

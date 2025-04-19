#ifndef TETROMINO_H
#define TETROMINO_H

#include <SDL.h>

class Tetromino
{
public:
    Tetromino();
    void reset();
    void update();
    void handleInput(SDL_Event &e);
    void rotate();
    void draw(SDL_Renderer *renderer);

    int getMinX() const;
    int getMaxX() const;
    int getHeight() const;
    int getWidth() const;

private:
    int x, y;        // position on the grid
    int shape[4][4]; // current shape (rotated)

    static const int BLOCK_SIZE = 30;

    // Predefined shapes for each tetromino, each with 4 rotations
    static const int shapes[7][4][4][4]; // 7 shapes, each having 4 rotations (4x4 matrices)
    int currentShapeIndex;               // to track which shape is currently being used
    int rotationIndex;                   // current rotation of the tetromino

    void setShape(int shapeIndex, int rotationIndex);
};

#endif // TETROMINO_H

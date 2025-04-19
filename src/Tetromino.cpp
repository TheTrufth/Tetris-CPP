#include "Tetromino.h"
#include <cstring>   // for memcpy
#include <algorithm> // for min/max

const int GRID_WIDTH = 10;
const int GRID_HEIGHT = 20;

// Predefined tetromino shapes with 4 possible rotations for each piece
const int Tetromino::shapes[7][4][4][4] = {
    // I shape (4x1)
    {
        {{0, 0, 0, 0},
         {1, 1, 1, 1},
         {0, 0, 0, 0},
         {0, 0, 0, 0}},
        {{0, 1, 0, 0},
         {0, 1, 0, 0},
         {0, 1, 0, 0},
         {0, 1, 0, 0}},
        {{0, 0, 0, 0},
         {1, 1, 1, 1},
         {0, 0, 0, 0},
         {0, 0, 0, 0}},
        {{0, 0, 0, 0},
         {0, 1, 0, 0},
         {0, 1, 0, 0},
         {0, 1, 0, 0}}},
    // O shape (2x2)
    {
        {{1, 1, 0, 0},
         {1, 1, 0, 0},
         {0, 0, 0, 0},
         {0, 0, 0, 0}},
        {{1, 1, 0, 0},
         {1, 1, 0, 0},
         {0, 0, 0, 0},
         {0, 0, 0, 0}},
        {{1, 1, 0, 0},
         {1, 1, 0, 0},
         {0, 0, 0, 0},
         {0, 0, 0, 0}},
        {{1, 1, 0, 0},
         {1, 1, 0, 0},
         {0, 0, 0, 0},
         {0, 0, 0, 0}}},
    // T shape
    {
        {{0, 1, 0, 0},
         {1, 1, 1, 0},
         {0, 0, 0, 0},
         {0, 0, 0, 0}},
        {{0, 1, 0, 0},
         {0, 1, 1, 0},
         {0, 1, 0, 0},
         {0, 0, 0, 0}},
        {{0, 0, 0, 0},
         {1, 1, 1, 0},
         {0, 1, 0, 0},
         {0, 0, 0, 0}},
        {{0, 1, 0, 0},
         {1, 1, 0, 0},
         {0, 1, 0, 0},
         {0, 0, 0, 0}}},
    // L shape
    {
        {{1, 0, 0, 0},
         {1, 1, 1, 0},
         {0, 0, 0, 0},
         {0, 0, 0, 0}},
        {{0, 1, 1, 0},
         {0, 1, 0, 0},
         {0, 1, 0, 0},
         {0, 0, 0, 0}},
        {{0, 0, 0, 0},
         {1, 1, 1, 0},
         {0, 0, 1, 0},
         {0, 0, 0, 0}},
        {{0, 1, 0, 0},
         {0, 1, 0, 0},
         {1, 1, 0, 0},
         {0, 0, 0, 0}}},
    // J shape
    {
        {{0, 0, 1, 0},
         {1, 1, 1, 0},
         {0, 0, 0, 0},
         {0, 0, 0, 0}},
        {{0, 1, 0, 0},
         {0, 1, 0, 0},
         {0, 1, 1, 0},
         {0, 0, 0, 0}},
        {{0, 0, 0, 0},
         {1, 1, 1, 0},
         {1, 0, 0, 0},
         {0, 0, 0, 0}},
        {{1, 1, 0, 0},
         {0, 1, 0, 0},
         {0, 1, 0, 0},
         {0, 0, 0, 0}}},
    // Z shape
    {
        {{1, 1, 0, 0},
         {0, 1, 1, 0},
         {0, 0, 0, 0},
         {0, 0, 0, 0}},
        {{0, 0, 1, 0},
         {0, 1, 1, 0},
         {0, 1, 0, 0},
         {0, 0, 0, 0}},
        {{1, 1, 0, 0},
         {0, 1, 1, 0},
         {0, 0, 0, 0},
         {0, 0, 0, 0}},
        {{0, 0, 1, 0},
         {0, 1, 1, 0},
         {0, 1, 0, 0},
         {0, 0, 0, 0}}},
    // S shape
    {
        {{0, 1, 1, 0},
         {1, 1, 0, 0},
         {0, 0, 0, 0},
         {0, 0, 0, 0}},
        {{0, 1, 0, 0},
         {0, 1, 1, 0},
         {0, 0, 1, 0},
         {0, 0, 0, 0}},
        {{0, 1, 1, 0},
         {1, 1, 0, 0},
         {0, 0, 0, 0},
         {0, 0, 0, 0}},
        {{0, 1, 0, 0},
         {0, 1, 1, 0},
         {0, 0, 1, 0},
         {0, 0, 0, 0}}}};

Tetromino::Tetromino()
    : x(3), y(0), currentShapeIndex(rand() % 7), rotationIndex(0)
{
    setShape(currentShapeIndex, rotationIndex);
}

void Tetromino::reset()
{
    x = 3;
    y = 0;
    currentShapeIndex = rand() % 7; // random piece
    rotationIndex = 0;              // reset rotation
    setShape(currentShapeIndex, rotationIndex);
}

void Tetromino::update()
{
    ++y;
    if (y + getHeight() > GRID_HEIGHT)
    {
        reset();
    }
}

void Tetromino::handleInput(SDL_Event &e)
{
    if (e.type != SDL_KEYDOWN)
        return;

    switch (e.key.keysym.sym)
    {
    case SDLK_LEFT:
        if (x + getMinX() > 0)
            --x;
        break;
    case SDLK_RIGHT:
        if (x + getMaxX() < GRID_WIDTH - 1)
            ++x;
        break;
    case SDLK_DOWN:
        if (y + getHeight() < GRID_HEIGHT)
            ++y;
        break;
    case SDLK_UP:
        rotate();
        break;
    default:
        break;
    }
}

void Tetromino::rotate()
{
    rotationIndex = (rotationIndex + 1) % 4; // Next rotation
    setShape(currentShapeIndex, rotationIndex);

    int minX = getMinX();
    int maxX = getMaxX();

    if (x + minX < 0)
        x -= (x + minX);
    if (x + maxX >= GRID_WIDTH)
        x -= (x + maxX - (GRID_WIDTH - 1));
}

void Tetromino::draw(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);

    for (int row = 0; row < 4; ++row)
    {
        for (int col = 0; col < 4; ++col)
        {
            if (shape[row][col])
            {
                SDL_Rect block = {(x + col) * BLOCK_SIZE, (y + row) * BLOCK_SIZE, BLOCK_SIZE - 1, BLOCK_SIZE - 1};
                SDL_RenderFillRect(renderer, &block);
            }
        }
    }
}

void Tetromino::setShape(int shapeIndex, int rotationIndex)
{
    std::memcpy(shape, shapes[shapeIndex][rotationIndex], sizeof(shape));
}

int Tetromino::getMinX() const
{
    for (int col = 0; col < 4; ++col)
        for (int row = 0; row < 4; ++row)
            if (shape[row][col])
                return col;
    return 0;
}

int Tetromino::getMaxX() const
{
    for (int col = 3; col >= 0; --col)
        for (int row = 0; row < 4; ++row)
            if (shape[row][col])
                return col;
    return 3;
}

int Tetromino::getHeight() const
{
    int minY = 4, maxY = -1;
    for (int row = 0; row < 4; ++row)
    {
        for (int col = 0; col < 4; ++col)
        {
            if (shape[row][col])
            {
                minY = std::min(minY, row);
                maxY = std::max(maxY, row);
            }
        }
    }
    return maxY - minY + 1;
}

int Tetromino::getWidth() const
{
    int minX = 4, maxX = 0;
    for (int col = 0; col < 4; ++col)
    {
        for (int row = 0; row < 4; ++row)
        {
            if (shape[row][col])
            {
                minX = std::min(minX, col);
                maxX = std::max(maxX, col);
            }
        }
    }
    return maxX - minX + 1;
}

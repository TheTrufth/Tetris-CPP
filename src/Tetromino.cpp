#include "Tetromino.h"
#include <cstring>   // for memcpy
#include <algorithm> // for min/max
#include <cstdlib>   // for rand

// Define the grid static member
int Tetromino::grid[GRID_HEIGHT][GRID_WIDTH] = {0}; // All cells initially empty

// Define colors for each Tetromino
SDL_Color Tetromino::tetrominoColors[7] = {
    {0, 255, 255, 255}, // Cyan (I shape)
    {255, 255, 0, 255}, // Yellow (O shape)
    {128, 0, 128, 255}, // Purple (T shape)
    {255, 165, 0, 255}, // Orange (L shape)
    {0, 0, 255, 255},   // Blue (J shape)
    {255, 0, 0, 255},   // Red (Z shape)
    {0, 255, 0, 255}    // Green (S shape)
};

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
    color = tetrominoColors[currentShapeIndex]; // Assign color based on shape index
}

void Tetromino::reset()
{
    x = 3;
    y = 0;
    currentShapeIndex = rand() % 7; // Random piece
    rotationIndex = 0;              // Reset rotation
    setShape(currentShapeIndex, rotationIndex);

    // Assign a random color to the active Tetromino
    color = {static_cast<unsigned char>(rand() % 256), static_cast<unsigned char>(rand() % 256), static_cast<unsigned char>(rand() % 256), 255}; // Random RGB color
}

void Tetromino::update()
{
    ++y; // Move the Tetromino down

    // Check if the Tetromino has collided with the grid or bottom of the screen
    if (checkCollision(x, y))
    {
        --y;                    // Revert the movement
        placeTetrominoInGrid(); // Lock the Tetromino into the grid
        reset();                // Reset the Tetromino to the top
    }
}

void Tetromino::placeTetrominoInGrid()
{
    // Place the Tetromino's blocks into the grid
    for (int row = 0; row < 4; ++row)
    {
        for (int col = 0; col < 4; ++col)
        {
            if (shape[row][col] != 0)
            {
                int gridX = x + col;
                int gridY = y + row;

                // Ensure we don’t go out of bounds
                if (gridY < GRID_HEIGHT)
                {
                    grid[gridY][gridX] = currentShapeIndex + 1; // Mark the grid with the shape index
                }
            }
        }
    }

    // Set the placed blocks to grey
    for (int row = 0; row < GRID_HEIGHT; ++row)
    {
        for (int col = 0; col < GRID_WIDTH; ++col)
        {
            if (grid[row][col] != 0)
            {
                tetrominoColors[grid[row][col] - 1] = {128, 128, 128, 255}; // Grey color
            }
        }
    }

    // Check for completed rows and clear them
    clearCompletedRows();
}

void Tetromino::clearCompletedRows()
{
    for (int row = 0; row < GRID_HEIGHT; ++row)
    {
        bool isRowComplete = true;

        for (int col = 0; col < GRID_WIDTH; ++col)
        {
            if (grid[row][col] == 0)
            {
                isRowComplete = false;
                break;
            }
        }

        if (isRowComplete)
        {
            // Shift all rows above down by one
            for (int r = row; r > 0; --r)
            {
                for (int col = 0; col < GRID_WIDTH; ++col)
                {
                    grid[r][col] = grid[r - 1][col];
                }
            }

            // Clear the top row
            for (int col = 0; col < GRID_WIDTH; ++col)
            {
                grid[0][col] = 0;
            }
        }
    }
}

void Tetromino::handleInput(SDL_Event &e)
{
    if (e.type != SDL_KEYDOWN)
        return;

    int prevX = x, prevY = y;

    switch (e.key.keysym.sym)
    {
    case SDLK_LEFT:
        if (x + getMinX() > 0 && !checkCollision(x - 1, y))
            --x;
        break;
    case SDLK_RIGHT:
        if (x + getMaxX() < GRID_WIDTH - 1 && !checkCollision(x + 1, y))
            ++x;
        break;
    case SDLK_DOWN:
        if (y + getHeight() < GRID_HEIGHT && !checkCollision(x, y + 1))
            ++y;
        break;
    case SDLK_UP:
        rotate(); // Rotation is already handled in the rotate() function
        break;
    case SDLK_g: // Toggle ghost preview
        ghostEnabled = !ghostEnabled;
        break;
    default:
        break;
    }

    // If the Tetromino is moved down, check if it collides
    if (y != prevY)
    {
        if (checkCollision(x, y))
        {
            y = prevY; // Restore the previous y if collision occurs
            reset();   // Reset the Tetromino
        }
    }
}

void Tetromino::rotate()
{
    int newRotationIndex = (rotationIndex + 1) % 4;
    setShape(currentShapeIndex, newRotationIndex);

    int newMinX = getMinX();
    int newMaxX = getMaxX();

    // Check if the rotation causes an out-of-bounds issue or collision
    if (!checkCollision(x, y))
    {
        rotationIndex = newRotationIndex; // Apply the new rotation
    }
    else
    {
        // If collision occurs, adjust the Tetromino position to fit within bounds
        if (x + newMinX < 0)
            x -= (x + newMinX);
        if (x + newMaxX >= GRID_WIDTH)
            x -= (x + newMaxX - (GRID_WIDTH - 1));
    }
}

void Tetromino::draw(SDL_Renderer *renderer)
{
    // Draw the grid first
    for (int row = 0; row < GRID_HEIGHT; ++row)
    {
        for (int col = 0; col < GRID_WIDTH; ++col)
        {
            if (grid[row][col] != 0)
            {
                // The block in the grid is non-empty, so draw it
                SDL_SetRenderDrawColor(renderer, tetrominoColors[grid[row][col] - 1].r,
                                       tetrominoColors[grid[row][col] - 1].g,
                                       tetrominoColors[grid[row][col] - 1].b,
                                       tetrominoColors[grid[row][col] - 1].a);
                int px = col * BLOCK_SIZE;
                int py = row * BLOCK_SIZE;
                SDL_Rect block = {px, py, BLOCK_SIZE - 1, BLOCK_SIZE - 1};
                SDL_RenderFillRect(renderer, &block);
            }
        }
    }

    // Draw the ghost Tetromino if enabled
    if (ghostEnabled)
    {
        int ghostX, ghostY;
        calculateGhostPosition(ghostX, ghostY);

        // Set the ghost Tetromino color to semi-transparent grey
        SDL_SetRenderDrawColor(renderer, 192, 192, 192, 100); // Semi-transparent grey (alpha = 128)
        for (int row = 0; row < 4; ++row)
        {
            for (int col = 0; col < 4; ++col)
            {
                if (shape[row][col] != 0)
                {
                    int px = (ghostX + col) * BLOCK_SIZE;
                    int py = (ghostY + row) * BLOCK_SIZE;
                    SDL_Rect block = {px, py, BLOCK_SIZE - 1, BLOCK_SIZE - 1};
                    SDL_RenderFillRect(renderer, &block);
                }
            }
        }
    }

    // Now, draw the active Tetromino
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
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

bool Tetromino::checkCollision(int newX, int newY)
{
    // Check for each block in the Tetromino
    for (int row = 0; row < 4; ++row)
    {
        for (int col = 0; col < 4; ++col)
        {
            if (shape[row][col] != 0)
            {
                int gridX = newX + col;
                int gridY = newY + row;

                // Check if the block goes outside the grid
                if (gridX < 0 || gridX >= GRID_WIDTH || gridY >= GRID_HEIGHT)
                {
                    return true; // Out of bounds, collision
                }

                // Check if the grid has a block already in the position
                if (grid[gridY][gridX] != 0)
                {
                    return true; // Collision with another block
                }
            }
        }
    }
    return false;
}

void Tetromino::calculateGhostPosition(int &ghostX, int &ghostY)
{
    ghostX = x;
    ghostY = y;

    // Simulate falling until collision
    while (!checkCollision(ghostX, ghostY + 1))
    {
        ++ghostY;
    }
}
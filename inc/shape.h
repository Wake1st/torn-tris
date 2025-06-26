#ifndef SHAPE_H
#define SHAPE_H

#include "stdint.h"
#include "raylib.h"

#include "globals.h"
#include "block.h"

#define BLOCK_COUNT 4

typedef enum Shapes
{
  SHAPE_T,
  SHAPE_L,
  SHAPE_Z,
  SHAPE_S,
  SHAPE_LINE,
  SHAPE_SQUARE,
} Shapes;

typedef struct Shape
{
  Shapes shape;
  uint8_t x, y, up;
  Block *blocks[BLOCK_COUNT];
} Shape;

Shape *InitShape(Shapes shapes, Model model, uint8_t horizontal, uint8_t height);
void updateShape(Shape *shape, Command *command);
void dropShape(Shape *shape);
void drawShape(Shape *shape);
void draw3DShape(Shape *shape);
bool checkFloorShape(Shape *shape);
Block *getBlocks(Shape *shape);

Shape *InitSqShape(Model model, uint8_t horizontal, uint8_t height);
void updateSqShape(Shape *shape, Command *command);
void rotateSqBlocks(Shape *shape);

#endif

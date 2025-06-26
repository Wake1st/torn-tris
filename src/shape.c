#include "../inc/shape.h"

Shape *InitShape(Shapes shapes, Model model, uint8_t horizontal, uint8_t height)
{
  switch (shapes)
  {
  case SHAPE_SQUARE:
  default:
    return InitSqShape(model, horizontal, height);
  }
}

void updateShape(Shape *shape, Command *command)
{
  switch (shape->shape)
  {
  case SHAPE_SQUARE:
  default:
    return updateSqShape(shape, command);
  }
}

void dropShape(Shape *shape)
{
  shape->y--;

  for (int i = 0; i < BLOCK_COUNT; i++)
    shape->blocks[i]->y--;
}

void drawShape(Shape *shape)
{
  DrawText("Shape", 20, 40, 40, BLACK);

  DrawText(TextFormat("X:\t%i", shape->x), 20, 80, 20, DARKPURPLE);
  DrawText(TextFormat("Y:\t%i", shape->y), 20, 100, 20, DARKPURPLE);
  DrawText(TextFormat("UP:\t%i", shape->up), 20, 120, 20, DARKPURPLE);

  DrawText(TextFormat("Angle:\t%f", ANGLE_SIZE), 20, 140, 20, DARKPURPLE);
}

void draw3DShape(Shape *shape)
{
  for (int i = 0; i < BLOCK_COUNT; i++)
    draw3DBlock(*shape->blocks[i]);
}

bool checkFloorShape(Shape *shape)
{
  switch (shape->shape)
  {
  case SHAPE_SQUARE:
  default:
    // first, check for floor
    if (shape->y == 0)
    {
      return true;
    }

    return false;
  }
}

Block *getBlocks(Shape *shape)
{
  return *shape->blocks;
}

Shape *InitSqShape(Model model, uint8_t horizontal, uint8_t height)
{
  Color shapeColor = getRandColor();

  return &(Shape){
      .shape = SHAPE_SQUARE,
      .x = horizontal,
      .y = height,
      .blocks = {
          &(Block){model, shapeColor, (uint8_t)((0 + horizontal) % X_CELLS), (uint8_t)(0 + height)},
          &(Block){model, shapeColor, (uint8_t)((0 + horizontal) % X_CELLS), (uint8_t)(1 + height)},
          &(Block){model, shapeColor, (uint8_t)((1 + horizontal) % X_CELLS), (uint8_t)(1 + height)},
          &(Block){model, shapeColor, (uint8_t)((1 + horizontal) % X_CELLS), (uint8_t)(0 + height)},
      },
  };
}

void updateSqShape(Shape *shape, Command *command)
{
  // spin, slide, or shift down
  switch (*command)
  {
  case COMMAND_RIGHT:
  {

    shape->x = (shape->x + 1) % X_CELLS;

    for (int i = 0; i < BLOCK_COUNT; i++)
    {
      shape->x = (shape->x + 1) % X_CELLS;
    }

    break;
  }
  case COMMAND_LEFT:
  {
    shape->x = (shape->x - 1) % X_CELLS;
    if (shape->x == 255)
    {
      shape->x = 15;
    }

    for (int i = 0; i < BLOCK_COUNT; i++)
    {
      shape->blocks[i]->x = (shape->blocks[i]->x - 1) % X_CELLS;
      if (shape->blocks[i]->x == 255)
      {
        shape->blocks[i]->x = 15;
      }
    }

    break;
  }
  case COMMAND_UP:
  {
    // instantly go down
    return;
  }
  case COMMAND_DOWN:
  {

    shape->y--;

    for (int i = 0; i < BLOCK_COUNT; i++)
    {
      shape->blocks[i]->y--;
    }

    return;
  }
  case COMMAND_CW:
  {
    shape->up = (shape->up + 1) % ANGLES;

    rotateSqBlocks(shape);
    break;
  }
  case COMMAND_CCW:
  {

    shape->up = (shape->up - 1) % ANGLES;
    if (shape->up == 255)
      shape->up = 3;

    rotateSqBlocks(shape);
    break;
  }
  case COMMAND_NONE:
  default:
    return;
  }

  // modify model
  for (int i = 0; i < BLOCK_COUNT; i++)
  {
    updateTransform(*shape->blocks[i]);
  }
}

void rotateSqBlocks(Shape *shape)
{
  // hard coded is the easiest to manage
  switch (shape->up)
  {
  case 0:
    shape->blocks[1]->x = (shape->x + 0) % X_CELLS;
    shape->blocks[1]->y = shape->y + 1;
    shape->blocks[2]->x = (shape->x + 1) % X_CELLS;
    shape->blocks[2]->y = shape->y + 1;
    shape->blocks[3]->x = (shape->x + 1) % X_CELLS;
    shape->blocks[3]->y = shape->y + 0;
    break;
  case 1:
    shape->blocks[1]->x = (shape->x + 1) % X_CELLS;
    shape->blocks[1]->y = shape->y + 0;
    shape->blocks[2]->x = (shape->x + 1) % X_CELLS;
    shape->blocks[2]->y = shape->y - 1;
    shape->blocks[3]->x = (shape->x + 0) % X_CELLS;
    shape->blocks[3]->y = shape->y - 1;
    break;
  case 2:
    shape->blocks[1]->x = (shape->x + 0) % X_CELLS;
    shape->blocks[1]->y = shape->y - 1;
    shape->blocks[2]->x = (shape->x - 1) % X_CELLS;
    shape->blocks[2]->y = shape->y - 1;
    shape->blocks[3]->x = (shape->x - 1) % X_CELLS;
    shape->blocks[3]->y = shape->y + 0;
    break;
  case 3:
    shape->blocks[1]->x = (shape->x - 1) % X_CELLS;
    shape->blocks[1]->y = shape->y + 0;
    shape->blocks[2]->x = (shape->x - 1) % X_CELLS;
    shape->blocks[2]->y = shape->y + 1;
    shape->blocks[3]->x = (shape->x + 0) % X_CELLS;
    shape->blocks[3]->y = shape->y + 1;
    break;
  }

  // ensure no 255
  for (int i = 0; i < BLOCK_COUNT; i++)
    if (shape->blocks[i]->x == 255)
      shape->blocks[i]->x = 15;
}
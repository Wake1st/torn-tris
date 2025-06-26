#ifndef SHAPE_H
#define SHAPE_H

#include "stdint.h"
#include "raylib.h"

#include "globals.h"
#include "block.h"

#define BLOCK_COUNT 4

typedef enum shapes
{
  T,
  L,
  Z,
  S,
  LINE,
  SQUARE,
} Shapes;

typedef struct Shape
{
  Shapes shape;
  uint8_t x, y, up;
  Block *blocks[BLOCK_COUNT];
} Shape;

Shape *InitShape(Shapes shapes, Model model, uint8_t horizontal, uint8_t height)
{
  Color shapeColor = getRandColor();

  switch (shapes)
  {
  case Shapes::SQUARE:
    return InitSqShape(model, horizontal, height);
  }
}

void update(Shape *shape, Command *command)
{
  switch (shape->shape)
  {
  case Shapes::SQUARE:
    return updateSqShape(shape, command);
  }
}

void drop(Shape *shape)
{
  shape->y--;

  for (int i = 0; i < BLOCK_COUNT; i++)
    shape->blocks[i]->y--;
}

void draw(Shape *shape)
{
  DrawText("Shape", 20, 40, 40, BLACK);

  DrawText(TextFormat("X:\t%i", shape->x), 20, 80, 20, DARKPURPLE);
  DrawText(TextFormat("Y:\t%i", shape->y), 20, 100, 20, DARKPURPLE);
  DrawText(TextFormat("UP:\t%i", shape->up), 20, 120, 20, DARKPURPLE);

  DrawText(TextFormat("Angle:\t%f", ANGLE_SIZE), 20, 140, 20, DARKPURPLE);
}

void draw3D(Shape *shape)
{
  for (int i = 0; i < BLOCK_COUNT; i++)
    draw3D(*shape->blocks[i]);
}

bool checkFloor(Shape *shape)
{
  switch (shape->shape)
  {
  case Shapes::SQUARE:
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
  return shape->blocks;
}

Shape *InitSqShape(Model model, uint8_t horizontal, uint8_t height)
{
  Color shapeColor = getRandColor();

  return &(Shape){
      .shape = Shapes::SQUARE,
      .x = horizontal,
      .y = height,
      .blocks = {
          new (Block){model, shapeColor, (uint8_t)((0 + horizontal) % X_CELLS), (uint8_t)(0 + height)},
          new (Block){model, shapeColor, (uint8_t)((0 + horizontal) % X_CELLS), (uint8_t)(1 + height)},
          new (Block){model, shapeColor, (uint8_t)((1 + horizontal) % X_CELLS), (uint8_t)(1 + height)},
          new (Block){model, shapeColor, (uint8_t)((1 + horizontal) % X_CELLS), (uint8_t)(0 + height)},
      },
  };
}

void updateSqShape(Shape *shape, Command *command)
{
  // spin, slide, or shift down
  switch (*command)
  {
  case Command::RIGHT:
  {

    shape->x = (shape->x + 1) % X_CELLS;

    for (int i = 0; i < BLOCK_COUNT; i++)
    {
      shape->x = (shape->x + 1) % X_CELLS;
    }

    break;
  }
  case Command::LEFT:
  {
    shape->x = (shape->x - 1) % X_CELLS;
    if (shape->x == 255)
    {
      shape->x = 15;
    }

    for (int i = 0; i < BLOCK_COUNT; i++)
    {
      block->x = (block->x - 1) % X_CELLS;
      if (block->x == 255)
      {
        block->x = 15;
      }
    }

    break;
  }
  case Command::UP:
  {
    // instantly go down
    return;
  }
  case Command::DOWN:
  {

    shape->y--;

    for (int i = 0; i < BLOCK_COUNT; i++)
    {
      block->y--;
    }

    return;
  }
  case Command::CW:
  {
    shape->up = (shape->up + 1) % ANGLES;

    rotateSqBlocks(shape);
    break;
  }
  case Command::CCW:
  {

    shape->up = (shape->up - 1) % ANGLES;
    if (shape->up == 255)
      shape->up = 3;

    rotateSqBlocks(shape);
    break;
  }
  case Command::NONE:
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

// class HookShape : public Shape
// {
// public:
//   void shape->date(Command *command) override;
//   void draw3D() override;
//   bool checkFloor() override;
// };

// void HookShape::update(Command *command)
// {
// }

// void HookShape::draw3D()
// {
// }

// bool HookShape::checkFloor()
// {
//   return false;
// }

// class TShape : public Shape
// {
// public:
//   void update(Command *command) override;
//   void draw3D() override;
//   bool checkFloor() override;
// };

// void TShape::update(Command *command)
// {
// }

// void TShape::draw3D()
// {
// }

// bool TShape::checkFloor()
// {
//   return false;
// }

// class LineShape : public Shape
// {
// public:
//   void update(Command *command) override;
//   void draw3D() override;
//   bool checkFloor() override;
// };

// void LineShape::update(Command *command)
// {
// }

// void LineShape::draw3D()
// {
// }

// bool LineShape::checkFloor()
// {
//   return false;
// }

// class ZShape : public Shape
// {
// public:
//   void update(Command *command) override;
//   void draw3D() override;
//   bool checkFloor() override;
// };

// void ZShape::update(Command *command)
// {
// }

// void ZShape::draw3D()
// {
// }

// bool ZShape::checkFloor()
// {
//   return false;
// }

// class SShape : public Shape
// {
// public:
//   void update(Command *command) override;
//   void draw3D() override;
//   bool checkFloor() override;
// };

// void SShape::update(Command *command)
// {
// }

// void SShape::draw3D()
// {
// }

// bool SShape::checkFloor()
// {
//   return false;
// }

#endif

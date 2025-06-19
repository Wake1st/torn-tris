#ifndef SHAPE
#define SHAPE

#include <cstdint>
#include <vector>
#include "raylib.h"

#include "globals.h"
#include "block.h"

#define BLOCK_COUNT 4

class Shape
{
public:
  virtual void update(Command *command) = 0;
  virtual void drop() = 0;
  virtual void draw() = 0;
  virtual void draw3D() = 0;
  virtual bool checkFloor() = 0;
  virtual std::vector<Block *> getBlocks() = 0;

protected:
  uint8_t x, y, up = 0;

  std::vector<Block *> blocks;
  virtual void rotateBlocks() = 0;
};

class SqShape : public Shape
{
public:
  SqShape(Model model, uint8_t horizontal, uint8_t height)
  {
    x = horizontal;
    y = height;

    Color shapeColor = getRandColor();

    blocks = {
        new Block(model, shapeColor, (0 + horizontal) % X_CELLS, 0 + height),
        new Block(model, shapeColor, (0 + horizontal) % X_CELLS, 1 + height),
        new Block(model, shapeColor, (1 + horizontal) % X_CELLS, 1 + height),
        new Block(model, shapeColor, (1 + horizontal) % X_CELLS, 0 + height),
    };
  }
  void update(Command *command) override;
  void drop() override;
  void draw() override;
  void draw3D() override;
  bool checkFloor() override;
  std::vector<Block *> getBlocks() override;

private:
  void rotateBlocks() override;
};

void SqShape::update(Command *command)
{
  // spin, slide, or shift down
  switch (*command)
  {
  case Command::RIGHT:
    x = (x + 1) % X_CELLS;

    for (Block *block : blocks)
      block->x = (block->x + 1) % X_CELLS;

    break;
  case Command::LEFT:
    x = (x - 1) % X_CELLS;
    if (x == 255)
      x = 15;

    for (Block *block : blocks)
    {
      block->x = (block->x - 1) % X_CELLS;
      if (block->x == 255)
        block->x = 15;
    }

    break;
  case Command::UP:
    // instantly go down
    return;
  case Command::DOWN:
    y--;

    for (Block *block : blocks)
      block->y--;

    return;
  case Command::CW:
    up = (up + 1) % ANGLES;

    rotateBlocks();
    break;
  case Command::CCW:
    up = (up - 1) % ANGLES;
    if (up == 255)
      up = 3;

    rotateBlocks();
    break;
  case Command::NONE:
  default:
    return;
  }

  // modify model
  for (Block *block : blocks)
    block->updateTransform();
}

void SqShape::drop()
{
  y--;

  for (Block *block : blocks)
    block->y--;
}

void SqShape::draw()
{
  DrawText("SqShape", 20, 40, 40, BLACK);

  DrawText(TextFormat("X:\t%i", x), 20, 80, 20, DARKPURPLE);
  DrawText(TextFormat("Y:\t%i", y), 20, 100, 20, DARKPURPLE);
  DrawText(TextFormat("UP:\t%i", up), 20, 120, 20, DARKPURPLE);

  DrawText(TextFormat("Angle:\t%f", ANGLE_SIZE), 20, 140, 20, DARKPURPLE);
}

void SqShape::draw3D()
{
  for (Block *block : blocks)
    block->draw3D();
}

bool SqShape::checkFloor()
{
  // first, check for floor
  if (y == 0)
  {
    return true;
  }

  return false;
}

std::vector<Block *> SqShape::getBlocks()
{
  return blocks;
}

void SqShape::rotateBlocks()
{
  // hard coded is the easiest to manage
  switch (up)
  {
  case 0:
    blocks[1]->x = (x + 0) % X_CELLS;
    blocks[1]->y = y + 1;
    blocks[2]->x = (x + 1) % X_CELLS;
    blocks[2]->y = y + 1;
    blocks[3]->x = (x + 1) % X_CELLS;
    blocks[3]->y = y + 0;
    break;
  case 1:
    blocks[1]->x = (x + 1) % X_CELLS;
    blocks[1]->y = y + 0;
    blocks[2]->x = (x + 1) % X_CELLS;
    blocks[2]->y = y - 1;
    blocks[3]->x = (x + 0) % X_CELLS;
    blocks[3]->y = y - 1;
    break;
  case 2:
    blocks[1]->x = (x + 0) % X_CELLS;
    blocks[1]->y = y - 1;
    blocks[2]->x = (x - 1) % X_CELLS;
    blocks[2]->y = y - 1;
    blocks[3]->x = (x - 1) % X_CELLS;
    blocks[3]->y = y + 0;
    break;
  case 3:
    blocks[1]->x = (x - 1) % X_CELLS;
    blocks[1]->y = y + 0;
    blocks[2]->x = (x - 1) % X_CELLS;
    blocks[2]->y = y + 1;
    blocks[3]->x = (x + 0) % X_CELLS;
    blocks[3]->y = y + 1;
    break;
  }

  // ensure no 255
  for (Block *block : blocks)
    if (block->x == 255)
      block->x = 15;
}

class HookShape : public Shape
{
public:
  void update(Command *command) override;
  void draw3D() override;
  bool checkFloor() override;
};

void HookShape::update(Command *command)
{
}

void HookShape::draw3D()
{
}

bool HookShape::checkFloor()
{
  return false;
}

class TShape : public Shape
{
public:
  void update(Command *command) override;
  void draw3D() override;
  bool checkFloor() override;
};

void TShape::update(Command *command)
{
}

void TShape::draw3D()
{
}

bool TShape::checkFloor()
{
  return false;
}

class LineShape : public Shape
{
public:
  void update(Command *command) override;
  void draw3D() override;
  bool checkFloor() override;
};

void LineShape::update(Command *command)
{
}

void LineShape::draw3D()
{
}

bool LineShape::checkFloor()
{
  return false;
}

class ZShape : public Shape
{
public:
  void update(Command *command) override;
  void draw3D() override;
  bool checkFloor() override;
};

void ZShape::update(Command *command)
{
}

void ZShape::draw3D()
{
}

bool ZShape::checkFloor()
{
  return false;
}

class SShape : public Shape
{
public:
  void update(Command *command) override;
  void draw3D() override;
  bool checkFloor() override;
};

void SShape::update(Command *command)
{
}

void SShape::draw3D()
{
}

bool SShape::checkFloor()
{
  return false;
}

#endif

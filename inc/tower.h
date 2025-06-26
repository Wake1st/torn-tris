#ifndef TOWER_H
#define TOWER_H

#include "stdint.h"
#include "raylib.h"

#include "globals.h"
#include "shape.h"
#include "actor.h"

#define DROP_TICK 1.2f
#define COLLIDER_COUNT 256
#define SHAPE_COUNT 256

typedef struct Tower
{
  Actor *actor;
  Model baseModel;
  uint8_t spawnHeight;
  Block *colliders[COLLIDER_COUNT];
  Shape *shapes[SHAPE_COUNT];
  Shape *activeShape;
  float timer;
} Tower;

void spawn(Tower *tower)
{
  tower->activeShape = InitShape(Shapes::SQUARE, tower->baseModel, tower->actor->currentCell, tower->spawnHeight);
}

bool update(Tower *tower, Command *command)
{
  // before we go, we must check our sides
  if (*command == Command::LEFT && leftCheck(tower))
  {
    return false;
  }
  else if (*command == Command::RIGHT && rightCheck(tower))
  {
    return false;
  }
  else
  {
    update(tower->activeShape, command);
    return true;
  }
}

bool checkLoose(Tower *tower)
{
  return false;
}

bool checkFullLine(Tower *tower)
{
  return false;
}

bool drop(Tower *tower)
{
  // move shape down
  tower->timer -= GetFrameTime();

  if (tower->timer <= 0.f)
  {
    tower->timer = DROP_TICK;
    drop(tower->activeShape);
  }

  // collision check
  bool hitFloor = checkFloor(tower->activeShape);
  bool collision = fallingCheck(tower);
  if (hitFloor || collision)
  {
    tower->shapes.push_back(tower->activeShape);
    return true;
  }

  return false;
}

void draw(Tower *tower)
{
  draw(tower->activeShape);

  for (Shape *shape : tower->shapes)
  {
    draw(shape);
  }
}

void draw3D(Tower *tower)
{
  draw3D(tower->activeShape);

  for (Shape *shape : tower->shapes)
  {
    draw3D(shape);
  }
}

bool leftCheck(Tower *tower)
{

  for (Block *block : getBlocks(tower->activeShape))
  {
    uint8_t checkLeft = ((uint8_t)block->x - 1) % X_CELLS;
    for (Shape *shape : tower->shapes)
    {
      for (Block *shapeBlock : getBlocks(shape))
      {
        if (block->y == shapeBlock->y && checkLeft == shapeBlock->x)
        {
          return true;
        }
      }
    }
  }

  return false;
}

bool rightCheck(Tower *tower)
{
  for (Block *block : getBlocks(tower->activeShape))
  {
    uint8_t checkRight = ((uint8_t)block->x + 1) % X_CELLS;
    for (Shape *shape : tower->shapes)
    {
      for (Block *shapeBlock : getBlocks(shape))
      {
        if (block->y == shapeBlock->y && checkRight == shapeBlock->x)
        {
          return true;
        }
      }
    }
  }

  return false;
}

bool fallingCheck(Tower *tower)
{
  for (Block *checkBlock : getBlocks(tower->activeShape))
  {
    for (Shape *shape : tower->shapes)
    {
      for (Block *shapeBlock : getBlocks(shape))
      {
        if (checkBlock->x == shapeBlock->x && checkBlock->y == shapeBlock->y + 1)
        {
          return true;
        }
      }
    }
  }

  return false;
}

#endif

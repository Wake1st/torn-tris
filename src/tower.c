#include "../inc/tower.h"

#define DROP_TICK 1.2f
#define COLLIDER_COUNT 256
#define SHAPE_COUNT 256

void spawnShape(Tower *tower)
{
  tower->activeShape = InitShape(SHAPE_SQUARE, tower->baseModel, tower->actor->currentCell, tower->spawnHeight);
}

void mergeActiveShape(Tower *tower)
{
  tower->shapes[tower->shapeIndex++] = tower->activeShape;
}

bool updateTower(Tower *tower, Command *command)
{
  // before we go, we must check our sides
  if (*command == COMMAND_LEFT && leftCheck(tower))
  {
    return false;
  }
  else if (*command == COMMAND_RIGHT && rightCheck(tower))
  {
    return false;
  }
  else
  {
    updateShape(tower->activeShape, command);
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

bool leftCheck(Tower *tower)
{
  Block *blocks = getBlocks(tower->activeShape);
  for (int i = 0; i < BLOCK_COUNT; i++)
  {
    uint8_t checkLeft = ((uint8_t)blocks[i].x - 1) % X_CELLS;
    for (int j = 0; j < tower->shapeIndex; j++)
    {
      Block *shapeBlocks = getBlocks(tower->shapes[j]);
      for (int k = 0; k < BLOCK_COUNT; k++)
      {
        if (blocks[i].y == shapeBlocks[k].y && checkLeft == shapeBlocks[k].x)
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
  Block *blocks = getBlocks(tower->activeShape);
  for (int i = 0; i < BLOCK_COUNT; i++)
  {
    uint8_t checkRight = ((uint8_t)blocks[i].x + 1) % X_CELLS;
    for (int j = 0; j < tower->shapeIndex; j++)
    {
      Block *shapeBlocks = getBlocks(tower->shapes[j]);
      for (int k = 0; k < BLOCK_COUNT; k++)
      {
        if (blocks[i].y == shapeBlocks[k].y && checkRight == shapeBlocks[k].x)
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
  Block *blocks = getBlocks(tower->activeShape);
  for (int i = 0; i < BLOCK_COUNT; i++)
  {
    for (int j = 0; j < tower->shapeIndex; j++)
    {
      Block *shapeBlocks = getBlocks(tower->shapes[j]);
      for (int k = 0; k < BLOCK_COUNT; k++)
      {
        if (blocks[i].x == shapeBlocks[k].x && blocks[i].y == shapeBlocks[j].y + 1)
        {
          return true;
        }
      }
    }
  }

  return false;
}

bool dropTower(Tower *tower)
{
  // move shape down
  tower->timer -= GetFrameTime();

  if (tower->timer <= 0.f)
  {
    tower->timer = DROP_TICK;
    dropShape(tower->activeShape);
  }

  // collision check
  bool hitFloor = checkFloorShape(tower->activeShape);
  bool collision = fallingCheck(tower);
  if (hitFloor || collision)
  {
    mergeActiveShape(tower);
    return true;
  }

  return false;
}

void drawTower(Tower *tower)
{
  drawShape(tower->activeShape);

  for (int i = 0; i < tower->shapeIndex; i++)
  {
    drawShape(tower->shapes[i]);
  }
}

void draw3DTower(Tower *tower)
{
  draw3DShape(tower->activeShape);

  for (int i = 0; i < tower->shapeIndex; i++)
  {
    draw3DShape(tower->shapes[i]);
  }
}

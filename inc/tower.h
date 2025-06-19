#ifndef TOWER
#define TOWER

#include <iostream>
#include <cstdint>
#include <vector>
#include "raylib.h"

#include "globals.h"
#include "shape.h"
#include "actor.h"

#define DROP_TICK 1.2f;

class Tower
{
public:
  Tower(Actor *actor, Model model);
  void spawn();
  bool update(Command *command);
  bool checkLoose();
  bool checkFullLine();
  bool drop();
  void draw();
  void draw3D();

private:
  Actor *actor;
  Model baseModel;
  uint8_t spawnHeight = 8;

  std::vector<Block *> colliders;
  std::vector<Shape *> shapes;
  Shape *activeShape;

  float timer = 0.f;

  bool leftCheck(Shape *checking);
  bool rightCheck(Shape *checking);
  bool fallingCheck(Shape *checking);
};

Tower::Tower(Actor *act, Model model)
{
  actor = act;
  baseModel = model;
  shapes = std::vector<Shape *>();
}

void Tower::spawn()
{
  activeShape = new SqShape(baseModel, actor->getHorizontal(), spawnHeight);
}

bool Tower::update(Command *command)
{
  // before we go, we must check our sides
  if (*command == Command::LEFT && Tower::leftCheck(activeShape))
  {
    return false;
  }
  else if (*command == Command::RIGHT && Tower::rightCheck(activeShape))
  {
    return false;
  }
  else
  {
    activeShape->update(command);
    return true;
  }
}

bool Tower::checkLoose()
{
  return false;
}

bool Tower::checkFullLine()
{
  return false;
}

bool Tower::drop()
{
  // move shape down
  timer -= GetFrameTime();

  if (timer <= 0.f)
  {
    timer = DROP_TICK;
    activeShape->drop();
  }

  // collision check
  bool hitFloor = activeShape->checkFloor();
  bool collision = Tower::fallingCheck(activeShape);
  if (hitFloor || collision)
  {
    shapes.push_back(activeShape);
    return true;
  }

  return false;
}

void Tower::draw()
{
  activeShape->draw();

  for (Shape *shape : shapes)
  {
    shape->draw();
  }
}

void Tower::draw3D()
{
  activeShape->draw3D();

  for (Shape *shape : shapes)
  {
    shape->draw3D();
  }
}

bool Tower::leftCheck(Shape *checking)
{

  for (Block *block : checking->getBlocks())
  {
    uint8_t checkLeft = ((uint8_t)block->x - 1) % X_CELLS;
    for (Shape *shape : shapes)
    {
      for (Block *shapeBlock : shape->getBlocks())
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

bool Tower::rightCheck(Shape *checking)
{
  for (Block *block : checking->getBlocks())
  {
    uint8_t checkRight = ((uint8_t)block->x + 1) % X_CELLS;
    for (Shape *shape : shapes)
    {
      for (Block *shapeBlock : shape->getBlocks())
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

bool Tower::fallingCheck(Shape *checking)
{
  for (Block *checkBlock : checking->getBlocks())
  {
    for (Shape *shape : shapes)
    {
      for (Block *shapeBlock : shape->getBlocks())
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

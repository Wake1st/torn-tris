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
  int shapeIndex;
  Shape *activeShape;
  float timer;
} Tower;

void spawnShape(Tower *tower);
void mergeActiveShape(Tower *tower);
bool updateTower(Tower *tower, Command *command);
bool checkLoose(Tower *tower);
bool checkFullLine(Tower *tower);
bool leftCheck(Tower *tower);
bool rightCheck(Tower *tower);
bool fallingCheck(Tower *tower);
bool dropTower(Tower *tower);
void drawTower(Tower *tower);
void draw3DTower(Tower *tower);

#endif

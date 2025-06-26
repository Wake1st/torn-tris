#ifndef ACTOR_H
#define ACTOR_H

#include "math.h"
#include "stdint.h"
#include "raylib.h"
#include "raymath.h"

#include "globals.h"

#define SPEED 6.4f
#define CLOSENESS 0.01f

#define ANGLE_SIZE (PI * 2.f / (float)X_CELLS)

typedef struct Actor
{
  float currentAngle;
  float targetAngle;
  uint8_t currentCell;
  uint8_t targetCell;
  float angleSize;
  bool rightward;
  bool isMoving;
} Actor;

void setTarget(Actor *actor, Command *command)
{
  switch (*command)
  {
  case Command::RIGHT:
    actor->targetCell = (actor->targetCell + 1) % X_CELLS;
    actor->rightward = true;
    break;
  case Command::LEFT:
    actor->targetCell = (actor->targetCell - 1) % X_CELLS;
    if (actor->targetCell == 255)
      actor->targetCell = 15;

    actor->rightward = false;
    break;
  default:
    return;
  }

  actor->targetAngle = actor->targetCell * actor->angleSize;
  actor->isMoving = true;
}

void move(Actor *actor)
{
  if (actor->isMoving)
  {
    // shift angle
    float deltaAngle = GetFrameTime() * SPEED;
    float distance;
    if (actor->rightward)
    {
      actor->currentAngle += deltaAngle;

      if (actor->targetCell == 0 && actor->currentCell == 15)
        distance = (PI * 2.f) - actor->currentAngle;
      else
        distance = actor->targetAngle - actor->currentAngle;
    }
    else
    {
      actor->currentAngle -= deltaAngle;

      if (actor->targetCell == 15 && actor->currentCell == 0)
        distance = (PI * 2.f) + actor->currentAngle - actor->targetAngle;
      else
        distance = actor->currentAngle - actor->targetAngle;
    }

    // ensure the angle snaps
    if (distance < CLOSENESS)
    {
      actor->currentAngle = actor->targetAngle;
      actor->currentCell = actor->targetCell;
      actor->isMoving = false;
    }
  }
}

void update(Actor *actor, Camera3D *camera)
{
  if (actor->isMoving)
  {
    float x = CAMERA_DIST * sin(actor->currentAngle);
    float y = CAMERA_DIST * cos(actor->currentAngle);
    camera->position = (Vector3){x, CAMERA_HEIGHT, y};
    camera->target = (Vector3){0.f, CAMERA_TARGET, 0.f};
  }
}

void draw(Actor *actor)
{
  DrawText("ACTOR", 20, 40, 40, BLACK);

  DrawText(TextFormat("Current Cell:\t%i", actor->currentCell), 20, 80, 20, DARKPURPLE);
  DrawText(TextFormat("Target Cell:\t%i", actor->targetCell), 20, 100, 20, DARKPURPLE);

  DrawText(TextFormat("Current Angle:\t%f", actor->currentAngle), 20, 120, 20, DARKPURPLE);
  DrawText(TextFormat("Target Angle:\t%f", actor->targetAngle), 20, 140, 20, DARKPURPLE);
}

#endif

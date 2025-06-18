#ifndef ACTOR
#define ACTOR

#include <cstdint>
#include <cmath>
#include "raylib.h"
#include "raymath.h"

#include "globals.h"

#define SPEED 6.4f
#define CLOSENESS 0.01f

class Actor
{
public:
  bool isMoving;

  Actor();
  void setTarget(Command *command);
  void move();
  void update(Camera3D *camera);
  void draw();
  uint8_t getHorizontal()
  {
    return currentCell;
  }

private:
  float currentAngle = 0.f;
  float targetAngle = 0.f;
  uint8_t currentCell = 0;
  uint8_t targetCell = 0;

  float angleSize;
  bool rightward;

  // float distance = 0.f;
};

Actor::Actor()
{
  isMoving = false;
  rightward = false;
  angleSize = PI * 2.f / (float)X_CELLS;
}

void Actor::setTarget(Command *command)
{
  switch (*command)
  {
  case Command::RIGHT:
    targetCell = (targetCell + 1) % X_CELLS;
    rightward = true;
    break;
  case Command::LEFT:
    targetCell = (targetCell - 1) % X_CELLS;
    if (targetCell == 255)
      targetCell = 15;

    rightward = false;
    break;
  default:
    return;
  }

  targetAngle = targetCell * angleSize;
  isMoving = true;
}

void Actor::move()
{
  if (isMoving)
  {
    // shift angle
    float deltaAngle = GetFrameTime() * SPEED;
    float distance;
    if (rightward)
    {
      currentAngle += deltaAngle;

      if (targetCell == 0 && currentCell == 15)
        distance = (PI * 2.f) - currentAngle;
      else
        distance = targetAngle - currentAngle;
    }
    else
    {
      currentAngle -= deltaAngle;

      if (targetCell == 15 && currentCell == 0)
        distance = (PI * 2.f) + currentAngle - targetAngle;
      else
        distance = currentAngle - targetAngle;
    }

    // ensure the angle snaps
    if (distance < CLOSENESS)
    {
      currentAngle = targetAngle;
      currentCell = targetCell;
      isMoving = false;
    }
  }
}

void Actor::update(Camera3D *camera)
{
  if (isMoving)
  {
    float x = CAMERA_DIST * std::sin(currentAngle);
    float y = CAMERA_DIST * std::cos(currentAngle);
    camera->position = (Vector3){x, CAMERA_HEIGHT, y};
    camera->target = (Vector3){0.f, CAMERA_TARGET, 0.f};
  }
}

void Actor::draw()
{
  DrawText("ACTOR", 20, 40, 40, BLACK);

  DrawText(TextFormat("Current Cell:\t%i", currentCell), 20, 80, 20, DARKPURPLE);
  DrawText(TextFormat("Target Cell:\t%i", targetCell), 20, 100, 20, DARKPURPLE);

  DrawText(TextFormat("Current Angle:\t%f", currentAngle), 20, 120, 20, DARKPURPLE);
  DrawText(TextFormat("Target Angle:\t%f", targetAngle), 20, 140, 20, DARKPURPLE);
}

#endif

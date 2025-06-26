#ifndef INPUT_H
#define INPUT_H

#include "raylib.h"

#include "globals.h"

Command handleInput()
{
  if (IsKeyDown(KEY_RIGHT))
    return Command::RIGHT;
  if (IsKeyDown(KEY_LEFT))
    return Command::LEFT;
  if (IsKeyDown(KEY_UP))
    return Command::UP;
  if (IsKeyDown(KEY_DOWN))
    return Command::DOWN;
  if (IsKeyDown(KEY_A))
    return Command::CCW;
  if (IsKeyDown(KEY_D))
    return Command::CW;

  // nothing pressed
  return Command::NONE;
}

#endif

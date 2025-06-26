#ifndef INPUT_H
#define INPUT_H

#include "raylib.h"

#include "globals.h"

Command handleInput()
{
  if (IsKeyDown(KEY_RIGHT))
    return COMMAND_RIGHT;
  if (IsKeyDown(KEY_LEFT))
    return COMMAND_LEFT;
  if (IsKeyDown(KEY_UP))
    return COMMAND_UP;
  if (IsKeyDown(KEY_DOWN))
    return COMMAND_DOWN;
  if (IsKeyDown(KEY_A))
    return COMMAND_CCW;
  if (IsKeyDown(KEY_D))
    return COMMAND_CW;

  // nothing pressed
  return COMMAND_NONE;
}

#endif

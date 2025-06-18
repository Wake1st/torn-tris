#ifndef INPUT
#define INPUT

#include "raylib.h"
#include "globals.h"

class InputHandler
{
public:
  Command handleInput();
};

Command InputHandler::handleInput()
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
    return Command::CW;
  if (IsKeyDown(KEY_D))
    return Command::CCW;

  // nothing pressed
  return Command::NONE;
}

#endif

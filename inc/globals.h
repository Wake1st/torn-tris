#ifndef GLOBALS
#define GLOBALS

#define COOLDOWN 0.12f
#define ANGLE_SIZE PI * 2.f / (float)X_CELLS

#define CELL_SIZE 2.f
#define X_CELLS 16
#define Y_CELLS 255
#define ANGLES 4

#define TOWER_RADIUS 5.1f

#define CAMERA_DIST 18.f
#define CAMERA_HEIGHT 2.f
#define CAMERA_TARGET 10.f

typedef enum Command
{
  NONE,
  LEFT,
  RIGHT,
  UP,
  DOWN,
  CW,
  CCW,
} Command;

Color getRandColor()
{
  int rand = GetRandomValue(0, 21);

  switch (rand)
  {
  case 0:
    return LIGHTGRAY;
  case 1:
    return GRAY;
  case 2:
    return DARKGRAY;
  case 3:
    return YELLOW;
  case 4:
    return GOLD;
  case 5:
    return ORANGE;
  case 6:
    return PINK;
  case 7:
    return RED;
  case 8:
    return MAROON;
  case 9:
    return GREEN;
  case 10:
    return LIME;
  case 11:
    return DARKGREEN;
  case 12:
    return SKYBLUE;
  case 13:
    return BLUE;
  case 14:
    return DARKBLUE;
  case 15:
    return PURPLE;
  case 16:
    return VIOLET;
  case 17:
    return DARKPURPLE;
  case 18:
    return BEIGE;
  case 19:
    return BROWN;
  case 20:
    return DARKBROWN;
  case 21:
    return MAGENTA;
  }
}

#endif

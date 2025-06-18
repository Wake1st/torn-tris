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

#endif

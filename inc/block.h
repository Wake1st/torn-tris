#ifndef BLOCK_H
#define BLOCK_H

#include "math.h"
#include "stdint.h"
#include "raylib.h"

#include "globals.h"

typedef struct Block
{
  Model model;
  Color color;
  uint8_t x, y;
} Block;

void updateTransform(Block block)
{
  block.model.transform = MatrixRotateXYZ((Vector3){0.f, block.x * ANGLE_SIZE, 0.f});
}

void draw3D(Block block)
{
  float angle = block.x * ANGLE_SIZE;
  float baseX = TOWER_RADIUS * sin(angle);
  float baseY = TOWER_RADIUS * cos(angle);
  float height = block.y * CELL_SIZE;
  DrawModel(block.model, (Vector3){baseX, height, baseY}, 1.0, block.color);
}

#endif

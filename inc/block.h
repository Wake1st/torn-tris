#ifndef BLOCK
#define BLOCK

#include <cmath>
#include <cstdint>
#include "raylib.h"

#include "globals.h"

class Block
{
public:
  uint8_t x, y;

  Block(Model baseModel, Color shapeColor, uint8_t x_, uint8_t y_)
  {
    model = baseModel;
    color = shapeColor;
    x = x_;
    y = y_;

    Block::updateTransform();
  }
  void updateTransform();
  void draw3D();

private:
  Model model;
  Color color;
};

void Block::updateTransform()
{
  model.transform = MatrixRotateXYZ((Vector3){0.f, x * ANGLE_SIZE, 0.f});
}

void Block::draw3D()
{
  float angle = x * ANGLE_SIZE;
  float baseX = TOWER_RADIUS * std::sin(angle);
  float baseY = TOWER_RADIUS * std::cos(angle);
  float height = y * CELL_SIZE;
  DrawModel(model, (Vector3){baseX, height, baseY}, 1.0, color);
}

#endif

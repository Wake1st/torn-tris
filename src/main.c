#include "raylib.h"
#include "raymath.h"

#include "globals.h"
#include "input.h"
#include "actor.h"
#include "tower.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
  // Initialization
  //--------------------------------------------------------------------------------------
  const int screenWidth = 1800;
  const int screenHeight = 850;

  InitWindow(screenWidth, screenHeight, "Torn-Tris");
  SetWindowMonitor(0);

  // Define the camera to look into our 3d world
  Camera3D camera = {0};
  camera.position = (Vector3){0.f, CAMERA_HEIGHT, CAMERA_DIST}; // Camera position
  camera.target = (Vector3){0.f, CAMERA_TARGET, 0.f};           // Camera looking at point
  camera.up = (Vector3){0.f, 1.f, 0.f};                         // Camera up vector (rotation towards target)
  camera.fovy = 85.0f;                                          // Camera field-of-view Y
  camera.projection = CAMERA_PERSPECTIVE;                       // Camera mode type

  Model model = LoadModel("resources/block.glb"); // Load model

  SetTargetFPS(60); // Set our game to run at 60 frames-per-second
  //--------------------------------------------------------------------------------------
  const int SPAWN_HEIGHT = 8;
  float timer = 0.f;

  Actor *actor = &(Actor){
      .currentAngle = 0.f,
      .targetAngle = 0.f,
      .currentCell = 0,
      .currentAngle = 0.f,
      .isMoving = false,
      .rightward = false,
  };
  Tower *tower = &(Tower){
      .actor = actor,
      .baseModel = model,
      .spawnHeight = SPAWN_HEIGHT,
      .timer = DROP_TICK,
  };

  // start the game already!
  spawnShape(tower);

  // Main game loop
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    // Update
    //----------------------------------------------------------------------------------
    timer -= GetFrameTime();

    Command cmd = handleInput();
    if (cmd != COMMAND_NONE)
    {
      // check the timer
      if (timer <= 0.f)
      {
        timer = COOLDOWN;

        if (updateTower(tower, &cmd))
        {
          setTarget(actor, &cmd);
        }
      }
    }

    moveActor(actor);
    updateTower(tower, &cmd);

    // passed when hits "floor"
    if (dropTower(tower))
    {
      if (checkLoose(tower))
      {
        // end level
      }
      else if (checkFullLine(tower))
      {
        // remove line!
      }
      else
      {
        // start a new shape
        spawnShape(tower);
      }
    }

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

    ClearBackground(RAYWHITE);

    BeginMode3D(camera);

    draw3DTower(tower);
    DrawGrid(20, 10.0f); // Draw a grid

    EndMode3D();

    DrawText("Its tetris in towers!", screenWidth - 200, screenHeight - 20, 10, GRAY);

    // actor->draw();
    drawTower(tower);
    DrawFPS(10, 10);

    EndDrawing();
    //----------------------------------------------------------------------------------
  }

  // De-Initialization
  //--------------------------------------------------------------------------------------
  UnloadModel(model); // Unload model

  CloseWindow(); // Close window and OpenGL context
  //--------------------------------------------------------------------------------------

  return 0;
}

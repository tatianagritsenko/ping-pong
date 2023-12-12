#include <raylib.h>

#include <iostream>

class Ball {
 public:
  float x, y;
  int speed_x, speed_y;
  int radius;
  Ball(float x, float y, int sx, int sy, int r)
      : x(x), y(y), speed_x(sx), speed_y(sy), radius(r){};
  void Draw() { DrawCircle(x, y, radius, WHITE); }

  void Update() {
    x += speed_x;
    y += speed_y;
    if (y + radius >= GetScreenHeight() || y + radius <= 0) speed_y *= -1;
    if (x + radius >= GetScreenWidth() || x + radius <= 0) speed_x *= -1;
  }
};

class Paddle {
 public:
  float x, y;
  float width, height;
  int speed;
  Paddle(float w, float h, float x, float y, int s)
      : x(x), y(y), width(w), height(h), speed(s){};
  void Draw() { DrawRectangle(x, y, width, height, WHITE); }
  void Update() {
    if (IsKeyDown(KEY_UP)) y -= speed;
    if (IsKeyDown(KEY_DOWN)) y += speed;
    if (y <= 0) y = 0;
    if (y + height >= GetScreenHeight()) y = GetScreenHeight() - height;
  }
};

int main() {
  std::cout << "Starting the game" << std::endl;
  const int screen_width = 1280;
  const int screen_height = 800;
  Ball *ball = new Ball(screen_width / 2, screen_height / 2, 7, 7, 20);
  Paddle *player =
      new Paddle(25, 120, screen_width - 35, screen_height / 2 - 60, 6);
  InitWindow(screen_width, screen_height, "Pong Game!");
  SetTargetFPS(60);

  while (WindowShouldClose() == false) {
    ball->Update();
    player->Update();
    BeginDrawing();
    ClearBackground(BLACK);
    DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);
    ball->Draw();
    DrawRectangle(10, screen_height / 2 - 60, 25, 120, WHITE);
    player->Draw();
    EndDrawing();
  }

  CloseWindow();
  return 0;
}

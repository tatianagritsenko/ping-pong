#include <raylib.h>
#include <iostream>

int player_score = 0;
int cpu_score = 0;

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
    if (x + radius >= GetScreenWidth())
    {
	cpu_score++;
	ResetBall();
    }
    if (x-radius <= 0)
    {
	player_score++;
	ResetBall();
    }
  }

 void ResetBall()
 {
	x = GetScreenWidth() / 2;
	y = GetScreenHeight() / 2;
	int speed_choices[2] = { -1,1 };
	speed_x *= speed_choices[GetRandomValue(0, 1)];
	speed_y *= speed_choices[GetRandomValue(0, 1)];
 }
};

class Paddle {
protected:
	void LimitMovement() {
		if (y <= 0)
		{
			y = 0;
		}
		if (y + height >= GetScreenHeight())
		{
			y = GetScreenHeight() - height;
		}
	}

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
    LimitMovement();
  }
};

class CPUPaddle : public Paddle {
public:

	CPUPaddle(float w, float h, float x, float y, int s) : Paddle(w, h, x, y, s) { }

	void Update(int ball_y)
	{
		if (y + height / 2 > ball_y)
		{
			y = y - speed;
		}
		if (y + height / 2 <= ball_y)
		{
			y = y + speed;
		}
		LimitMovement();
	}
};

int main() {
  std::cout << "Starting the game" << std::endl;
  const int screen_width = 1280;
  const int screen_height = 800;
  Ball *ball = new Ball(screen_width / 2, screen_height / 2, 7, 7, 20);
  Paddle *player =
      new Paddle(25, 120, screen_width - 35, screen_height / 2 - 60, 6);
 CPUPaddle *cpu = new CPUPaddle(25, 120, 10, screen_height / 2 - 60, 6);
  InitWindow(screen_width, screen_height, "Pong Game!");
  SetTargetFPS(60);

  while (WindowShouldClose() == false) {
    ball->Update();
    player->Update();
    cpu->Update(ball->y);
    BeginDrawing();

   // Checking for collisions
    if (CheckCollisionCircleRec(Vector2{ ball->x, ball->y }, ball->radius, Rectangle{ player->x, player->y, player->width, player->height }))
    {
	ball->speed_x *= -1;
    }
    if (CheckCollisionCircleRec(Vector2{ ball->x, ball->y }, ball->radius, Rectangle{ cpu->x, cpu->y, cpu->width, cpu->height }))
    {
	ball->speed_x *= -1;
    }
	  
    ClearBackground(BLACK);
    DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);
    ball->Draw();
    cpu->Draw();
    player->Draw();
    DrawText(TextFormat("%i",cpu_score), screen_width/4 - 20, 20, 80, WHITE);
    DrawText(TextFormat("%i", player_score), 3*screen_width / 4 - 20, 20, 80, WHITE);
	  
    EndDrawing();
  }

  CloseWindow();
  return 0;
}

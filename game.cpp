#include <iostream>
#include <raylib.h>

class Ball {
public:
	float x,y;
	int speed_x, speed_y;
	int radius;
    Ball(float x, float y, int sx, int sy, int r) : x(x), y(y), radius(r), speed_x(sx), speed_y(sy) {};
	void Draw(){
		DrawCircle(x, y, radius, WHITE);
	}

	void Update() {
		x += speed_x;
		y += speed_y;
	}
};

int main() {
	
	std::cout << "Starting the game" << std::endl;
	const int screen_width = 1280;
	const int screen_height = 800;
	Ball *ball = new Ball(screen_width / 2, screen_height / 2, 7, 7, 20);
	InitWindow(screen_width, screen_height, "My Pong Game!");
	SetTargetFPS(60);

	while (WindowShouldClose() == false) {
		ball->Update();
		BeginDrawing();
		ClearBackground(BLACK);
		DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);
		ball->Draw();
		DrawRectangle(10, screen_height / 2 - 60, 25, 120, WHITE);
		DrawRectangle(screen_width-35, screen_height / 2 - 60, 25, 120, WHITE);
		
		EndDrawing();
	}

	CloseWindow();
	return 0;
}

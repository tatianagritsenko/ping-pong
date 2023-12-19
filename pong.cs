using System;
using System.Numerics;
using Raylib_cs;

public class Ball
{
    public float x, y;
    public int speed_x, speed_y;
    public int radius;

    public Ball(float x, float y, int sx, int sy, int r)
    {
        this.x = x;
        this.y = y;
        radius = r;
        speed_x = sx;
        speed_y = sy;
    }

    public void Draw()
    {
        Raylib.DrawCircle((int)x, (int)y, radius, Color.YELLOW);
    }

    public void Update()
    {
        x += speed_x;
        y += speed_y;

        if (y + radius >= Raylib.GetScreenHeight() || y - radius <= 0)
        {
            speed_y *= -1;
        }
        if (x + radius >= Raylib.GetScreenWidth())
        {
            Program.cpu_score++;
            ResetBall();
        }

        if (x - radius <= 0)
        {
            Program.player_score++;
            ResetBall();
        }
    }

    public void ResetBall()
    {
        x = Raylib.GetScreenWidth() / 2;
        y = Raylib.GetScreenHeight() / 2;
        int[] speedChoices = { -1, 1 };
        speed_x *= speedChoices[Raylib.GetRandomValue(0, 1)];
        speed_y *= speedChoices[Raylib.GetRandomValue(0, 1)];
    }
}

public class Paddle
{
    public float x, y;
    public float width, height;
    public int speed;

    public Paddle(float w, float h, float x, float y, int s)
    {
        this.x = x;
        this.y = y;
        width = w;
        height = h;
        speed = s;
    }

    public void Draw()
    {
        Raylib.DrawRectangleRounded(new Rectangle(x, y, width, height), 0.8f, 0, Color.WHITE);
    }

    public void Update()
    {
        if (Raylib.IsKeyDown(KeyboardKey.KEY_UP))
        {
            y -= speed;
        }
        if (Raylib.IsKeyDown(KeyboardKey.KEY_DOWN))
        {
            y += speed;
        }

        LimitMovement();
    }

    protected void LimitMovement()
    {
        if (y <= 0)
        {
            y = 0;
        }
        if (y + height >= Raylib.GetScreenHeight())
        {
            y = Raylib.GetScreenHeight() - height;
        }
    }
}

public class CPUPaddle : Paddle
{
    public CPUPaddle(float w, float h, float x, float y, int s) : base(w, h, x, y, s) { }

    public void Update(int ball_y)
    {
        if (y + height / 2 > ball_y)
        {
            y -= speed;
        }
        if (y + height / 2 <= ball_y)
        {
            y += speed;
        }
        LimitMovement();
    }
}

public class Program
{
    public static int player_score = 0;
    public static int cpu_score = 0;

    public static void Main()
    {
        Console.WriteLine("Starting the game");
        const int screen_width = 1280;
        const int screen_height = 800;
        Raylib.InitWindow(screen_width, screen_height, "My Pong Game!");
        Raylib.SetTargetFPS(60);

        Ball ball = new Ball(screen_width / 2, screen_height / 2, 7, 7, 20);
        Paddle player = new Paddle(25, 120, screen_width - 35, screen_height / 2 - 60, 6);
        CPUPaddle cpu = new CPUPaddle(25, 120, 10, screen_height / 2 - 60, 6);

        while (!Raylib.WindowShouldClose())
        {
            Raylib.BeginDrawing();

            // Updating
            ball.Update();
            player.Update();
            cpu.Update((int)ball.y);

            // Checking for collisions
            if (Raylib.CheckCollisionCircleRec(new Vector2(ball.x, ball.y), ball.radius, new Rectangle(player.x, player.y, player.width, player.height)))
            {
                ball.speed_x *= -1;
            }
            if (Raylib.CheckCollisionCircleRec(new Vector2(ball.x, ball.y), ball.radius, new Rectangle(cpu.x, cpu.y, cpu.width, cpu.height)))
            {
                ball.speed_x *= -1;
            }

            // Drawing
            Raylib.ClearBackground(Color.DARKGREEN);
            Raylib.DrawRectangle(screen_width / 2, 0, screen_width / 2, screen_height, Color.GREEN);
            Raylib.DrawCircle(screen_width / 2, screen_height / 2, 150, Color.LIGHTGRAY);
            Raylib.DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, Color.WHITE);
            ball.Draw();
            cpu.Draw();
            player.Draw();
            Raylib.DrawText(player_score.ToString(), screen_width / 4 - 20, 20, 80, Color.WHITE);
            Raylib.DrawText(cpu_score.ToString(), 3 * screen_width / 4 - 20, 20, 80, Color.WHITE);

            Raylib.EndDrawing();
        }

        Raylib.CloseWindow();
    }
}

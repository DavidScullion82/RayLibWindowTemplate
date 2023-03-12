#include <vector>

#include "raylib.h"

struct Ball {
	Vector2 pos;
	Vector2 speed;
	float radius;
	Color col = RED;
	bool collision = false;
};

typedef struct Timer {
	double startTime;
	double lifeTime;
} Timer;

//void StartTimer(Timer* timer, double lifeTime)
//{
//	timer->startTime = GetTime();
//	timer->lifeTime = lifeTime;
//}
//
//bool TimerDone(Timer timer)
//{
//	return GetTime() - timer.startTime >= timer.lifeTime;
//}
//
//double GetElapsed(Timer timer)
//{
//	return GetTime() - timer.startTime;
//}

void AddBall(Vector2 pos, Vector2 speed, float radius, Color col, std::vector<Ball> &bl)
{
	Ball ball = { pos, speed, radius, col };
	bl.push_back(ball);
	
}

int main(void)
{

	const int screenWidth = 1080;
	const int screenHeight = 720;

	InitWindow(screenWidth, screenHeight, "");

	std::vector<Ball> ballList;
	

	float ballRadius = 50;
	Vector2 ballPosition = { (float)screenWidth / 2, (float)screenHeight / 2 };
	Vector2 ballSpeed = { 5.0f, 5.0f };
	AddBall(ballPosition, ballSpeed, ballRadius, RED, ballList);

	ballPosition = { 700.0f, 600.0f };
	ballSpeed = { 3.0f, 3.0f };
	AddBall(ballPosition, ballSpeed, ballRadius, GREEN, ballList);

	ballPosition = { 200.0f, 400.0f };
	ballSpeed = { 7.0f, 1.0f };
	AddBall(ballPosition, ballSpeed, ballRadius, BLUE, ballList);

	Vector2 playerPos = { 150, 150 };
	Vector2 playerCentre;
	Rectangle spriteBounds;
	Texture2D playerTex = LoadTexture("resources/goomba.png");

	// bool collisionsDetected = false;

	

	SetTargetFPS(100);

	while (!WindowShouldClose())
	{
		// Update
		//----------------------------------------------------------------------------------
		
		playerCentre = { playerPos.x + playerTex.width / 2, playerPos.y + playerTex.height / 2 };
		spriteBounds = { playerPos.x, playerPos.y, (float)playerTex.width, (float)playerTex.height };

		for (auto& b : ballList) 
		{

			b.pos.x += b.speed.x;
			b.pos.y += b.speed.y;

			if ((b.pos.x >= (GetScreenWidth() - b.radius)) || (b.pos.x <= b.radius)) b.speed.x *= -1.0f;
			if ((b.pos.y >= (GetScreenHeight() - b.radius)) || (b.pos.y <= b.radius)) b.speed.y *= -1.0f;

			if (CheckCollisionCircleRec(b.pos, b.radius, spriteBounds))
			{
				b.collision = true;
			}
			else
			{
				b.collision = false;
			}
		}

		if (IsKeyDown(KEY_D)) playerPos.x += 5.0f;
		if (IsKeyDown(KEY_A)) playerPos.x -= 5.0f;
		if (IsKeyDown(KEY_S)) playerPos.y += 5.0f;
		if (IsKeyDown(KEY_W)) playerPos.y -= 5.0f;

		if (playerPos.x >= (GetScreenWidth() - playerTex.width)) playerPos.x = (float)GetScreenWidth() - playerTex.width;
		if (playerPos.x <= 0) playerPos.x = 0;
		if (playerPos.y >= (GetScreenHeight() - playerTex.height)) playerPos.y = (float)GetScreenHeight() - playerTex.height;
		if (playerPos.y <= 0) playerPos.y = 0;


		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();
			
			ClearBackground(DARKGRAY);

			for (auto& b : ballList) 
			{
				DrawCircleV(b.pos, b.radius, b.col);
				if (b.collision) DrawText("Collision", 10, 300, 20, RAYWHITE);
			}

			DrawTexture(playerTex, (int)playerPos.x, (int)playerPos.y, WHITE);

			DrawText(TextFormat("playerPos.x = %i ", (int)playerPos.x), 10, 50, 20, RAYWHITE);
			DrawText(TextFormat("playerPos.y = %i ", (int)playerPos.y), 10, 100, 20, RAYWHITE);
			DrawText(TextFormat("Centre X, Y = %i, %i", (int)playerCentre.x, (int)playerCentre.y), 10, 150, 20, RAYWHITE);
			DrawText(TextFormat("ballList Lenght = %i", (int)ballList.size()), 10, 200, 20, RAYWHITE);
			DrawRectangleLines((int)spriteBounds.x, (int)spriteBounds.y, (int)spriteBounds.width, (int)spriteBounds.height, YELLOW);
			// DrawCircleV(playerCentre, 7.5f, BLUE);
			DrawText(TextFormat("Time: %i ", (int)GetTime()), 10, 250, 20, RAYWHITE);
			DrawFPS(10, 10);

			

			SetWindowTitle(TextFormat("%i", (int)playerPos.x));
			
		
		EndDrawing();
		
	}
	// De-Initialization
	//--------------------------------------------------------------------------------------
	CloseWindow();        // Close window and OpenGL context
	UnloadTexture(playerTex);
	//--------------------------------------------------------------------------------------

	return 0;
}
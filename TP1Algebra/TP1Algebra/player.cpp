#include "player.h"
#include "main.h"

extern const int SCREEN_WIDHT;
extern const int SCREEN_HEIGHT;

void playerInit(Player& player)
{
	player.position = { (float)WindowsVars::SCREEN_WIDTH / 2, (float)WindowsVars::SCREEN_HEIGHT / 2 };
	player.size = 10.0f;
}

void playerMove(Player& player)
{
	if (IsKeyDown(KEY_RIGHT)) player.position.x += 3.0f;
	if (IsKeyDown(KEY_LEFT)) player.position.x -= 3.0f;
	if (IsKeyDown(KEY_UP)) player.position.y -= 3.0f;
	if (IsKeyDown(KEY_DOWN)) player.position.y += 3.0f;
}
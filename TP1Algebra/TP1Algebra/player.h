#pragma once

#include "raylib.h"

//STRUCTS
struct Player
{
	Vector2 position = {};
	float size = 0;
};

//FUNCTIONS
void playerInit(Player& player);
void playerMove(Player& player);
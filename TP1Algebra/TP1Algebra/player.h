#pragma once

#include "raylib.h"

//STRUCTS
struct Player
{
	Vector2 position = {};
	float size = 0;
};

//FUNCTIONS
// Hace que el jugador empiece en el punto (0;0)
void playerInit(Player& player);
void playerMove(Player& player);
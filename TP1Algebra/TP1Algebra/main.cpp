#include "raylib.h"
#include "player.h" 
#include <vector>
#include "main.h"
#include "stdc++.h"
#include <iostream>

using namespace std;

//Chequea si dos lineas se estan tocando
bool LineToLineCollision(Vector2 playerPos, Vector2 endlinePlayer, Vector2 startLine, Vector2 endLine);
// chequea la direccion a la que esta una linea de un punto, izquierda, derecha o si esta encima.
int direction(Vector2 a, Vector2 b, Vector2 c);
bool onLine(Vector2 startLine, Vector2 endLine, Vector2 point);
// chequea si colisiona
bool isInside(Vector2 player);

namespace WindowsVars
{
	extern const int SCREEN_WIDTH = 800;
	extern const int SCREEN_HEIGHT = 600;
}

vector<Vector2> puntos; // Vector para almacenar las posiciones de los clics, funciona como un array de vector2, para la creacion de la figura
Player player; // Creacion del jugador, es la pelota que se mueve

void main()
{
	InitWindow(WindowsVars::SCREEN_WIDTH, WindowsVars::SCREEN_HEIGHT, "Generador de Figuras");
	SetTargetFPS(60);

	bool changingFigure = true; // esta variable hace que cuando se apreta enter se deje de dibujar.
	bool isCollide = false; // checkea si colisiona la pelota con la figura, para cambiar su color


	playerInit(player);
	do
	{
		//UPDATE

		playerMove(player);

		if (changingFigure)
		{
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				// Obtén la posición del clic del mouse
				Vector2 mousePosition = GetMousePosition();
				puntos.push_back(mousePosition); // Agrega la posición al vector   // push_back es un sistema dentro de la clase vector que funciona como un almacenamiento de datos, en este caso Vector2
			}
			if (IsKeyPressed(KEY_ENTER))
			{
				changingFigure = false;
			}
		}

		if (isInside(player.position))
		{
			isCollide = true;
		}
		else
		{
			isCollide = false;
		}

		//DRAW

		BeginDrawing();
		ClearBackground(RAYWHITE);

		if (isCollide)
		{
			DrawCircleV(player.position, player.size, GREEN);
		}
		else
		{
			DrawCircleV(player.position, player.size, BLACK);
		}


		// Dibuja líneas entre los puntos almacenados
		if (puntos.size() > 1)
		{
			for (int i = 0; i < puntos.size() - 1; i++)
			{
				DrawLineEx(puntos[i], puntos[i + 1], 2, RED);
			}
		}

		EndDrawing();
	} while (!WindowShouldClose());

	CloseWindow();
}

bool LineToLineCollision(Vector2 playerPos, Vector2 endlinePlayer, Vector2 startLine, Vector2 endLine)
{
	int dir1 = direction(playerPos, endlinePlayer, startLine); // se utiliza para conseguir el valor numerico entre la direccion de el punto inicial del jugador (centro de la pelota), la linea imaginaria y el inicio del vector.
	int dir2 = direction(playerPos, endlinePlayer, endLine);// se utiliza para conseguir el valor numerico entre la direccion de el punto inicial del jugador (centro de la pelota), la linea imaginaria y el final del vector.
	int dir3 = direction(startLine, endLine, playerPos); // se utiliza para conseguir el valor numerico entre la direccion de el punto inicial del vector, el punto final del vector(la linea) y la posicion del jugador (inicio del a linea imaginaria).
	int dir4 = direction(startLine, endLine, endlinePlayer);// se utiliza para conseguir el valor numerico entre la direccion de el punto inicial del vector, el punto final del vector(la linea) y el final de la linea imaginaria.

	if (dir1 != dir2 && dir3 != dir4)
		return true;

	// Cuando p2 de la línea 2 está en la línea 1
	if (dir1 == 0 && onLine(playerPos, endlinePlayer, startLine))
		return true;

	// Cuando p1 de la línea 2 está en la línea 1
	if (dir2 == 0 && onLine(playerPos, endlinePlayer, endLine))
		return true;

	// Cuando p2 de la línea 1 está en la línea 2
	if (dir3 == 0 && onLine(startLine, endLine, playerPos))
		return true;

	// Cuando p1 de la línea 1 está en la línea 2
	if (dir4 == 0 && onLine(startLine, endLine, endlinePlayer))
		return true;

	return false;
}

int direction(Vector2 a, Vector2 b, Vector2 c)
{
	int val = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y); // esto es un producto cruz

	if (val == 0)
		return 0;  // Colineales
	else if (val < 0)
		return 2;  // Dirección antihoraria
	return 1;      // Dirección horaria
}

bool onLine(Vector2 startLine, Vector2 endLine, Vector2 player)
{
	// Comprueba si el punto p está en la línea l1
	if (player.x <= max(startLine.x, endLine.x)
		&& player.x >= min(startLine.x, endLine.x)
		&& (player.y <= max(startLine.y, endLine.y)
			&& player.y >= min(startLine.y, endLine.y)))
		return true;

	return false;
}

bool isInside(Vector2 point)
{
	Vector2 startLine = { player.position.x, player.position.y };
	Vector2 endLine = { 9999, player.position.y }; // crea una linea imaginaria desde la posicion del jugador hasta la posicion 9999 del eje x, para chequear cuantas lineas del poligono tiene por delante

	int counter = 0; // este contador es la cantidad de lineas por las que pasa la linea imaginaria

	for (int i = 1; i < puntos.size(); i++)
	{
		Vector2 startLinePolygon = { puntos[i - 1].x , puntos[i - 1].y }; // estas variables son el comienzo y el final de los vectores del poligono
		Vector2 endLinePolygon = { puntos[i].x , puntos[i].y };

		if (LineToLineCollision(startLinePolygon, endLinePolygon, startLine, endLine))
		{
			if (direction(startLinePolygon, point, endLinePolygon) == 0)
			{
				return onLine(startLinePolygon, endLinePolygon, point);
			}

			counter++;
		}

	}

	return counter % 2; //retorna resto de la division entre contador y 2, chequeando si es par o impar.
}

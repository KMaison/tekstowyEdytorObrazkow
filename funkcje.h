#pragma once
#include "conio2.h"
#include <stdio.h>
#include<math.h>

//-------------STRZALKI-------------------
#define UP			72
#define DOWN		80
#define LEFT		75
#define RIGHT		77

#define UP_CTRL		141
#define DOWN_CTRL	145
#define LEFT_CTRL	115
#define RIGHT_CTRL	116

//----------------------------------------

#define ENTER 13
#define ESC 27
#define BACKSPACE 8


//------------ROZMIAR RAMKI-------------
#define ROZMIAR_RAMKI_X 54
#define ROZMIAR_RAMKI_Y 22

//-----------ROZMIAR OBRAZKA-----------
#define ROZMIAR_OBRAZKA_X ROZMIAR_RAMKI_X-4
#define ROZMIAR_OBRAZKA_Y ROZMIAR_RAMKI_Y-2

//------------MIEJSCE RAMKI-------------
#define MIEJSCE_X 60
#define MIEJSCE_Y 5

//-----MIEJSCE RYSOWANIA TABLICY--------
#define MIEJSCE_RYSOWANIA_X MIEJSCE_X+2
#define MIEJSCE_RYSOWANIA_Y MIEJSCE_Y+1

//
#define STRINGSIZE 250

//--------------Menu------------------
#define MENUX 3
#define MENUY 3

//-----------------------------------
#define DOL	ROZMIAR_RAMKI_X - 2
#define PRAWO ROZMIAR_RAMKI_Y - 2	

typedef struct Pozycja
{
	int x, y;

}Rozmiar;


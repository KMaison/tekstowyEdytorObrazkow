#pragma once
#include "Funkcje.h"
struct Cursor
{
	Pozycja pozycja;
	Rozmiar* rozmiar_tablicy;
	void inicjalizuj(Rozmiar* rozmiar_tablicy2);
	void ruch(int znak);
	void rysuj_kursor();
	void menu_rysowania(char *nazwa);

};


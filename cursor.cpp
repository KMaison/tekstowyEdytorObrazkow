#include "Cursor.h"
#include <stdlib.h>
#include "Tablica.h"

void Cursor::inicjalizuj(Rozmiar* rozmiar_tablicy2)
{
	rozmiar_tablicy = rozmiar_tablicy2;
}

void Cursor::ruch(int znak)
{
	int size_x = (*rozmiar_tablicy).x, size_y = (*rozmiar_tablicy).y;

	if (size_x > ROZMIAR_OBRAZKA_X) size_x = ROZMIAR_OBRAZKA_X;
	if (size_y > ROZMIAR_OBRAZKA_Y) size_y = ROZMIAR_OBRAZKA_Y;

	if (znak == UP && pozycja.y > 0)
	{
		pozycja.y--;
	}
	if (znak == DOWN && pozycja.y<size_y - 1)
	{
		pozycja.y++;
	}
	if (znak == LEFT && pozycja.x>0)
	{
		pozycja.x--;
	}
	if (znak == RIGHT && pozycja.x < size_x - 1)
	{
		pozycja.x++;
	}
}

void Cursor::rysuj_kursor()
{
	textcolor(WHITE);
	gotoxy(pozycja.x - 1 +MIEJSCE_RYSOWANIA_X, pozycja.y+MIEJSCE_RYSOWANIA_Y); 
	putch('[');
	gotoxy(pozycja.x + 1+MIEJSCE_RYSOWANIA_X, pozycja.y+MIEJSCE_RYSOWANIA_Y);
	putch(']');

}

void Cursor::menu_rysowania(char *nazwa)
{
	gotoxy(MENUX, MENUY);
	cputs("STRZALKI - poruszanie");
	gotoxy(MENUX, MENUY+1);
	cputs("CTRL+STRZALKI - przewijanie obrazka");
	gotoxy(MENUX, MENUY+2);
	cputs("K - rysowanie prostokata");
	gotoxy(MENUX, MENUY+3);
	cputs("O - wczytanie z pliku");
	gotoxy(MENUX, MENUY+4);
	cputs("S - zapisanie do pliku");
	gotoxy(MENUX, MENUY+5);
	cputs("I - wczytanie domyslnego obrazka");
	gotoxy(MENUX, MENUY+6);
	cputs("N - powrot do menu glownego");
	gotoxy(MENUX, MENUY +7);
	cputs("F- kolorowanie");
	gotoxy(MENUX, MENUY + 8);
	cputs("X - zapis w formacie XPM2");
	gotoxy(MENUX, MENUY + 9);
	cputs("Z - odczyt w formacie XPM2");
	gotoxy(MENUX, MENUY+10);
	cputs("[0 - 9, q - y] - zmiana koloru");

	gotoxy(MENUX, MENUY + 15);
	cputs("Nazwa: ");
	if (nazwa[0] == '\0')
	{
		cputs("plik nie ma nazwy ");
	}
	else
		cputs(nazwa);

}
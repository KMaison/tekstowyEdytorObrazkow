#include<stdlib.h>
#include"conio2.h"
#include "Cursor.h"
#include"Funkcje.h"
#include "Tablica.h"
#include "Suwaki.h"

int main(int argc, char *argv[]) {
	int zn;
	Tablica tablica;
	Suwaki suwaki;
	tablica.kursor.pozycja.x = 0;
	tablica.kursor.pozycja.y = 0;
	tablica.nazwa_pliku[0] = '\0';
	tablica.czy_zaalokowano = false;
	

	_setcursortype(_NOCURSOR);
	settitle("Karolina Maison 165609");

	if (!((argc > 1) && tablica.odczyt_obrazka(argv[1])))
	{
		tablica.nowy_obrazek();
	}
	tablica.kursor.inicjalizuj(&tablica.rozmiar);
	tablica.inicjalizuj();
	suwaki.inicjalizowanie_suwakow(&tablica.rozmiar, &tablica.pozycja_rysowania);
	do {
		clrscr();

		tablica.rysuj_ramke();
		suwaki.rysowanie_ramek_suwakow();
		suwaki.rysowanie_suwakow();
		tablica.rysuj_tablice();
		tablica.kursor.rysuj_kursor();
		tablica.kursor.menu_rysowania(tablica.nazwa_pliku);

		//wyswietlanie kursora
		gotoxy(MENUX+2, MENUY+20);
		cputs("Pozycja kursora:");
		gotoxy(MENUX+2, MENUY+21);
		char pozycjax[5], pozycjay[5];
		int pozycja_rysowania_x_int = tablica.kursor.pozycja.x + tablica.pozycja_rysowania.x;
		int pozycja_rysowania_y_int = tablica.kursor.pozycja.y + tablica.pozycja_rysowania.y;
		itoa(pozycja_rysowania_x_int + 1, pozycjax, 10);
		cputs(pozycjax);
		itoa(pozycja_rysowania_y_int + 1, pozycjay, 10);
		cputs(" . ");
		cputs(pozycjay);
		 
		//wyswietlanie koloru

		gotoxy(MENUX + 2, MENUY + 25);
		cputs("Wybrany kolor:  ");
		textcolor(tablica.kolor);
		cputs("***");
		textcolor(WHITE);

		//pobranie znaku
		zn = getch();
		if (zn == 0) {
			zn = getch();

			tablica.kursor.ruch(zn);
			tablica.przesuwaj(zn);
		}
		else if (zn == 's' || zn == 'S')
		{
			clrscr();
			tablica.rysuj_ramke();
			tablica.rysuj_tablice();
			suwaki.rysowanie_ramek_suwakow();
			suwaki.rysowanie_suwakow();
			tablica.kursor.rysuj_kursor();
			tablica.zapis_wlasny();

		}
		else if (zn == 'k' || zn == 'K')
		{
			tablica.prostokat(suwaki);
		}
		else if (zn == 'n' || zn == 'N')
		{
			tablica.zwolnij();
			tablica.nowy_obrazek();

		}
		else if (zn == 'o' || zn == 'O')
		{
			clrscr();
			tablica.odczyt_obrazka();	
		}

		else if (zn == 'i' || zn == 'I')
		{
			tablica.odczyt_obrazka("przyklad.txt");
			tablica.kursor.menu_rysowania(tablica.nazwa_pliku);
		}
		else if (zn == 'f' || zn == 'F')
		{
			tablica.wypelnianie_pola(tablica.tablica[tablica.kursor.pozycja.y + tablica.pozycja_rysowania.y][tablica.kursor.pozycja.x + tablica.pozycja_rysowania.x], tablica.kolor, tablica.kursor.pozycja.x+tablica.pozycja_rysowania.x, tablica.kursor.pozycja.y+tablica.pozycja_rysowania.y);
		}
		else if (zn == 'x' || zn == 'X')
		{
			tablica.zapis_obrazka_xpm2();
		}
		else if (zn == 'z' || zn == 'Z')
		{
			clrscr();
			tablica.odczyt_obrazka_xpm2();
		}
		else tablica.zmien_kolor(zn);
		} while (zn != ESC);
	tablica.zwolnij();
	return 0;
}

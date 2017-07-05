#include "Tablica.h"
#include "Cursor.h"
#include "conio2.h"
#include <stdlib.h>

void Tablica::inicjalizuj()
{
	kolor = LIGHTRED;
	pozycja_rysowania.x = 0;
	pozycja_rysowania.y = 0;
}

void Tablica::zmien_kolor(int znak)
{
	if (znak >= '0' && znak <= '9' || znak == 'q' ||
		znak == 'w' || znak == 'e' || znak == 'r' ||
		znak == 't' || znak == 'y')
	{
		switch (znak)
		{
		case 'q': znak = 10; break;
		case 'w': znak = 11; break;
		case 'e': znak = 12; break;
		case 'r': znak = 13; break;
		case 't': znak = 14; break;
		case 'y': znak = 15; break;
		default: znak -= '0'; break;
		}
		kolor = znak;
	}
}

void Tablica::zaalokuj_tablice() {

	if (!czy_zaalokowano) {
		tablica = (int**)malloc(rozmiar.y * sizeof(int*));
		for (int i = 0; i < rozmiar.y; i++)
		{
			tablica[i] = (int*)malloc(rozmiar.x * sizeof(int));
		}

		for (int i = 0; i < rozmiar.y; i++)
		{
			for (int j = 0; j < rozmiar.x; j++)
			{
				tablica[i][j] = LIGHTBLUE;
			}
		}
		czy_zaalokowano = true;
	}
}

void Tablica::nowy_obrazek()
{
	kursor.pozycja.x = 0;
	kursor.pozycja.y = 0;
	pozycja_rysowania.x = 0;
	pozycja_rysowania.y = 0;
	bool panel_startowy = true;
	int menu = 0;
	czy_zaalokowano = false;
	nazwa_pliku[0] = '\0';

	while (panel_startowy) {   //panel startowy
		clrscr();
		gotoxy(MENUX, MENUY);
		cputs("Wybierz co chcesz zrobic:\n");
		gotoxy(MENUX, MENUY + 1);
		cputs("1 - nowy obrazek");
		gotoxy(MENUX, MENUY + 2);
		cputs("2 - wczytaj obrazek");
		gotoxy(MENUX, MENUY + 3);
		cputs("3 - wczytaj obrazek domyslny");
		gotoxy(MENUX, MENUY + 4);
		cputs("Esc - zakoncz");
		gotoxy(MENUX, MENUY + 5);
		menu = getch();
		switch (menu) {
		case '1':  panel_startowy = false;
			do {
				clrscr();
				gotoxy(MENUX, MENUY);
				cputs("Podaj rozmiary obrazka X Y :\n");
				gotoxy(MENUX, MENUY + 1);
				rozmiar.x = Int();
				gotoxy(MENUX, MENUY + 2);
				rozmiar.y = Int();
			} while (rozmiar.x == 0 || rozmiar.y == 0);
			zaalokuj_tablice();
			break;
		case '2': clrscr();  odczyt_obrazka();  panel_startowy = false;  break;
		case '3': clrscr();  odczyt_obrazka("przyklad.txt");  panel_startowy = false;  break;
		case ESC: zwolnij();  exit(0);
		}
	}
}

void Tablica::zwolnij()
{
	if (czy_zaalokowano)
	{
		rozmiar.x = 0;
		rozmiar.y = 0;

		for (int i = 0; i < rozmiar.y; i++)
		{
			free(tablica[i]);
		}
		free(tablica);
		czy_zaalokowano = false;
	}
}

void Tablica::rysuj_ramke()
{
	textcolor(WHITE);
	for (int i = 0; i < ROZMIAR_RAMKI_Y; i++)
	{
		for (int j = 0; j < ROZMIAR_RAMKI_X; j++)
		{
			if (j == 0 || j == ROZMIAR_RAMKI_X - 1 || i == 0 || i == ROZMIAR_RAMKI_Y - 1)
			{
				gotoxy(MIEJSCE_X + j, MIEJSCE_Y + i);
				putch('x');
			}
		}
	}
}

void Tablica::rysuj_tablice()
{
	int kolor_do_rysowania;
	int size_x = rozmiar.x, size_y = rozmiar.y;

	if (size_x > ROZMIAR_OBRAZKA_X) size_x = ROZMIAR_OBRAZKA_X;
	if (size_y > ROZMIAR_OBRAZKA_Y) size_y = ROZMIAR_OBRAZKA_Y;

	for (int i = 0; i < size_y; i++)
	{
		for (int j = 0; j < size_x; j++)
		{
			kolor_do_rysowania = tablica[i + pozycja_rysowania.y][j + pozycja_rysowania.x];
			textcolor(kolor_do_rysowania);
			gotoxy(MIEJSCE_RYSOWANIA_X + j, MIEJSCE_RYSOWANIA_Y + i);
			putch('*');
		}
	}
}

bool Tablica::odczyt_obrazka(char* nazwa)
{
	FILE* plik;
	char* nazwa2;			//tablica typu char ktora bedzie przechowywala
						//wpisana nazwe pliku
	int znak=0;
	if (nazwa) plik = fopen(nazwa, "rb");
	else {
		gotoxy(1, 1);
		cputs("Podaj nazwe pliku do odczytania: ");
		gotoxy(1, 2);

		nazwa2 = String();					 //uzycie funkcji ktora pozwala wpisac nazwe z klawiatury
		if (!nazwa2) {
			nowy_obrazek();
		return false;
		}
		plik = fopen(nazwa2, "rb");			//otworzenie pliku
	}
	if (!plik) {		//jezeli plik nie istnieje
		cputs("Plik nie istnieje!! \n press enter to continue");
		znak = getch();
		if (znak) {
			clrscr();
			odczyt_obrazka();
		}
		return false;
	}
	else {								 //jezeli otworzono plik
		if (nazwa) {
			int i = 0;
			while (nazwa[i] != '\0') {
				nazwa_pliku[i] = nazwa[i];
				i++;
			}
			nazwa_pliku[i] = '\0';
		}
		else
			for (int i = 0; i < STRINGSIZE; i++)
				nazwa_pliku[i] = nazwa2[i];
	}
	zwolnij();
	//wczytywanie pliku
	fscanf(plik, "%d\n%d\n", &rozmiar.x, &rozmiar.y);
	zaalokuj_tablice();						//utworzenie tablicy o wymiarach pobranych z pliku
	char kolor_pobrany;
	for (int i = 0; i < rozmiar.y; i++)
	{
		for (int j = 0; j < rozmiar.x; j++)
		{
			fscanf(plik, "%c", &kolor_pobrany);
			switch (kolor_pobrany)
			{
			case 'a': kolor_pobrany = 10; break;
			case 'b': kolor_pobrany = 11; break;
			case 'c': kolor_pobrany = 12; break;
			case 'd': kolor_pobrany = 13; break;
			case 'e': kolor_pobrany = 14; break;
			case 'f': kolor_pobrany = 15; break;
			default: kolor_pobrany -= '0'; break;
			}
			tablica[i][j] = kolor_pobrany;

		}
		fscanf(plik, "\n");
	}
	fclose(plik);

	
	kursor.pozycja.x = 0;
	kursor.pozycja.y =0;
	pozycja_rysowania.x = 0;
	pozycja_rysowania.y = 0;
	return true;
}

bool Tablica::zapis_wlasny()
{
	FILE* plik;
	char* nazwa;
	gotoxy(1, 1);
	cputs("Podaj nazwe pliku do zapisania: ");
	gotoxy(1, 2);
	nazwa = String();
	if (!nazwa)  //anulowanie zapisywania podczas zapisywania
	{
		cputs("Anulowano");
		return false;
	}
	plik = fopen(nazwa, "wb");
	if (!plik)  //nie wpisales nazwy
	{
		cputs("Nie wpisales poprawnej nazwy");
		return false;
	}
	fprintf(plik, "%d\n%d\n", rozmiar.x, rozmiar.y);
	int kolor_pobrany;
	for (int i = 0; i < rozmiar.y; i++)
	{
		for (int j = 0; j < rozmiar.x; j++)
		{
			kolor_pobrany = tablica[i][j];
			switch (kolor_pobrany)
			{
			case 10: kolor_pobrany = 'a'; break;
			case 11: kolor_pobrany = 'b'; break;
			case 12: kolor_pobrany = 'c'; break;
			case 13: kolor_pobrany = 'd'; break;
			case 14: kolor_pobrany = 'e'; break;
			case 15: kolor_pobrany = 'f'; break;
			default: kolor_pobrany += '0'; break;
			}
			fprintf(plik, "%c", kolor_pobrany);
		}

		fprintf(plik, "\n");
	}

	for (int i = 0; i < STRINGSIZE; i++)
		nazwa_pliku[i] = nazwa[i];

	fclose(plik);
	return true;
}

void Tablica::przesuwaj(int znak)
{

	if (znak == UP_CTRL && pozycja_rysowania.y > 0)
	{
		pozycja_rysowania.y--;
	}
	else if (znak == DOWN_CTRL && pozycja_rysowania.y < rozmiar.y - (ROZMIAR_OBRAZKA_Y))
	{
		pozycja_rysowania.y++;
	}
	else if (znak == LEFT_CTRL && pozycja_rysowania.x > 0)
	{
		pozycja_rysowania.x--;
	}
	else if (znak == RIGHT_CTRL && pozycja_rysowania.x < rozmiar.x - (ROZMIAR_OBRAZKA_X))
	{
		pozycja_rysowania.x++;
	}
}

void Tablica::prostokat(Suwaki suwaki)
{
	Pozycja pozycja_poczatkowa;
	pozycja_poczatkowa = kursor.pozycja;
	
	int zn;
	do {
		clrscr();
		rysuj_ramke();
		suwaki.rysowanie_ramek_suwakow();
		suwaki.rysowanie_suwakow();
		rysuj_tablice();
		kursor.rysuj_kursor();
		

		gotoxy(MENUX, MENUY);
		cputs("TRYB RYSOWANIA PROSTOKATA");
		gotoxy(MENUX, MENUY + 5);
		cputs("Aby zatwierdzic protokat nacisnij ponownie - k");
		gotoxy(MENUX, MENUY + 6);
		cputs("Aby wyjsc z trybu rysowania prostokata nacisnij ESC");
		gotoxy(MENUX+2, MENUY+25);
		cputs("Wybrany kolor:  ");
		textcolor(kolor);
		cputs("***");
		textcolor(WHITE);
		zn = getch();
		if (zn == 0) {
			zn = getch();
			kursor.ruch(zn);
			przesuwaj(zn);
		}

		zmien_kolor(zn);

		if (zn == 'k')
		{
			if (pozycja_poczatkowa.x <= kursor.pozycja.x && pozycja_poczatkowa.y < kursor.pozycja.y) //jesli rysujemy na dol w prawo
			{
				for (int i = pozycja_poczatkowa.y; i <= kursor.pozycja.y; i++)
				{
					for (int j = pozycja_poczatkowa.x; j <= kursor.pozycja.x; j++)
					{
						if (i == pozycja_poczatkowa.y || j == pozycja_poczatkowa.x ||
							i == kursor.pozycja.y || j == kursor.pozycja.x)
							tablica[i + pozycja_rysowania.y][j + pozycja_rysowania.x] = kolor;
					}
				}
			}
			if (pozycja_poczatkowa.x >= pozycja_rysowania.x && pozycja_poczatkowa.y > pozycja_rysowania.y) //rysujemy do gory w lewo
			{

				for (int i = pozycja_poczatkowa.y; i >= kursor.pozycja.y; i--)
				{
					for (int j = pozycja_poczatkowa.x; j >= kursor.pozycja.x; j--)
					{
						if (i == pozycja_poczatkowa.y || j == pozycja_poczatkowa.x ||
							i == kursor.pozycja.y || j == kursor.pozycja.x)
							tablica[i + pozycja_rysowania.y][j + pozycja_rysowania.x] = kolor;
					}
				}
			}
			if (pozycja_poczatkowa.y <= kursor.pozycja.y && pozycja_poczatkowa.x >= kursor.pozycja.x)  //rysujemy w dol w lewo
			{

				for (int i = pozycja_poczatkowa.y; i <= kursor.pozycja.y; i++)
				{
					for (int j = pozycja_poczatkowa.x; j >= kursor.pozycja.x; j--)
					{
						if (i == pozycja_poczatkowa.y || j == pozycja_poczatkowa.x ||
							i == kursor.pozycja.y || j == kursor.pozycja.x)
							tablica[i + pozycja_rysowania.y][j + pozycja_rysowania.x] = kolor;
					}
				}
			}
			if (pozycja_poczatkowa.y >= kursor.pozycja.y && pozycja_poczatkowa.x <= kursor.pozycja.x)  //rysujemy do gory w prawo
			{
				for (int i = pozycja_poczatkowa.y; i >= kursor.pozycja.y; i--)
				{
					for (int j = pozycja_poczatkowa.x; j <= kursor.pozycja.x; j++)
					{
						if (i == pozycja_poczatkowa.y || j == pozycja_poczatkowa.x ||
							i == kursor.pozycja.y || j == kursor.pozycja.x)
							tablica[i + pozycja_rysowania.y][j + pozycja_rysowania.x] = kolor;
					}
				}
			}
			return;
		}
	} while (zn != ESC);

}

void Tablica::wypelnianie_pola(int kolor_poczatkowy, int kolor_wybrany, int x, int y)
{
	if (kolor_poczatkowy != kolor_wybrany)
	{
		if (tablica[y][x] == kolor_poczatkowy)
		{
			tablica[y][x] = kolor_wybrany;

			if (x < rozmiar.x - 1) wypelnianie_pola(kolor_poczatkowy, kolor_wybrany, x + 1, y);
			if (y < rozmiar.y - 1) wypelnianie_pola(kolor_poczatkowy, kolor_wybrany, x, y + 1);
			if (x > 0) wypelnianie_pola(kolor_poczatkowy, kolor_wybrany, x - 1, y);
			if (y > 0) wypelnianie_pola(kolor_poczatkowy, kolor_wybrany, x, y - 1);
		}
	}
}

bool Tablica::zapis_obrazka_xpm2()
{
	FILE* plik;
	char* nazwa;
	gotoxy(1, 1);
	cputs("Podaj nazwe pliku do zapisania w formacie xpm2: ");
	gotoxy(1, 2);
	nazwa = String();
	if (!nazwa)  //anulowanie zapisywania podczas zapisywania
	{
		cputs("Anulowano");
		return false;
	}
	plik = fopen(nazwa, "wb");
	if (!plik)  //nie wpisales nazwy
	{
		cputs("Nie wpisales poprawnej nazwy");
		return false;
	}
	fprintf(plik, "%s\n", "!XPM2");
	fprintf(plik, "%d %d", rozmiar.x, rozmiar.y);
	fprintf(plik, " 16 1\na c #000000\nb c #0000AA\nc c #00AA00\nd c #00AAAA\ne c #AA0000\nf c #AA00AA\ng c #AA5500\nh c #AAAAAA\ni c #555555\nj c #5555FF\nk c #55FF55\nl c #55FFFF\nm c #FF5555\nn c #FF55FF\no c #FFFF55\np c #FFFFFF\n");
	int kolor_pobrany;
	for (int i = 0; i < rozmiar.y; i++)
	{
		for (int j = 0; j < rozmiar.x; j++)
		{
			kolor_pobrany = tablica[i][j];
			kolor_pobrany += 'a';
			fprintf(plik, "%c", kolor_pobrany);
		}

		fprintf(plik, "\n");
	}

	for (int i = 0; i < STRINGSIZE; i++)
		nazwa_pliku[i] = nazwa[i];

	fclose(plik);
	return 0;
}

bool Tablica::odczyt_obrazka_xpm2(char* nazwa)
{
	FILE* plik;
	char* nazwa2;			//tablica typu char ktora bedzie przechowywala
							//wpisana nazwe pliku
	int znak = 0;
	if (nazwa) plik = fopen(nazwa, "rb");
	else {
		gotoxy(1, 1);
		cputs("Podaj nazwe pliku do odczytania: ");
		gotoxy(1, 2);

		nazwa2 = String();					 //uzycie funkcji ktora pozwala wpisac nazwe z klawiatury
		if (!nazwa2) {
			nowy_obrazek();
			return false;
		}
		plik = fopen(nazwa2, "rb");			//otworzenie pliku
	}
	if (!plik) {		//jezeli plik nie istnieje
		cputs("Plik nie istnieje!! \n press enter to continue");
		znak = getch();
		if (znak) {
			clrscr();
		//	odczyt_obrazka_xpm2();
		}
		return false;
	}
	else {								 //jezeli otworzono plik
		if (nazwa) {
			int i = 0;
			while (nazwa[i] != '\0') {
				nazwa_pliku[i] = nazwa[i];
				i++;
			}
			nazwa_pliku[i] = '\0';
		}
		else
			for (int i = 0; i < STRINGSIZE; i++)
				nazwa_pliku[i] = nazwa2[i];
	}
	zwolnij();
	char a;
	//wczytywanie pliku
	fscanf(plik, "%c%c%c%c%c\n",&a,&a,&a,&a,&a);
	fscanf(plik, "%d %d %d %d\n", &rozmiar.x, &rozmiar.y);
	for (int i=0;i<16;i++)
		fscanf(plik, "%c %c %c%c%c%c%c%c%c\n", &a, &a, &a, &a, &a,&a,&a,&a,&a);
	zaalokuj_tablice();						//utworzenie tablicy o wymiarach pobranych z pliku
	char kolor_pobrany;
	for (int i = 0; i < rozmiar.y; i++)
	{
		for (int j = 0; j < rozmiar.x; j++)
		{
			fscanf(plik, "%c", &kolor_pobrany);
			switch (kolor_pobrany)
			{
			case 'k': kolor_pobrany = 10; break;
			case 'l': kolor_pobrany = 11; break;
			case 'm': kolor_pobrany = 12; break;
			case 'n': kolor_pobrany = 13; break;
			case 'o': kolor_pobrany = 14; break;
			case 'p': kolor_pobrany = 15; break;
			default: kolor_pobrany -= 49; break; 
	}
			tablica[i][j] = kolor_pobrany;

		}
		fscanf(plik, "\n");
	}
	fclose(plik);

	kursor.pozycja.x = 0;
	kursor.pozycja.y = 0;
	pozycja_rysowania.x = 0;
	pozycja_rysowania.y = 0;
	return true;
}

char* Tablica::String()
{
	static char string[STRINGSIZE];

	for (int i = 0; i < STRINGSIZE; i++)
		string[i] = '\0';

	int litera_cyfra = 0, i = 0;

	while (litera_cyfra != ENTER) {
		litera_cyfra = getche();
		string[i] = litera_cyfra;

		if (litera_cyfra == BACKSPACE && i > 0) {
			clreol();
			string[--i] = '\0';
			continue;
		}
		if (litera_cyfra == ESC)
			return nullptr;

		i++;
	}
	string[--i] = '\0';
	return string;
}

int Tablica::Int() {
	int i = 0;
	int znak = 0;
	int liczba = 0;

	while (true) {
		znak = getche();
		if ((znak >= '0' && znak <= '9') || znak == ENTER || znak == BACKSPACE) {
			if (znak == ENTER) {
				putch('\n');
				break;
			}
			if (znak == BACKSPACE) {
				if (i > 0)
					i--;
				liczba /= 10;
				clreol();
			}
			else {
				liczba *= 10;
				liczba += znak - 48;
				i++;
			}
		}
		else { //jesli ktos wpisze cos co nie jest liczba program to cofnie
			putch(BACKSPACE);
			clreol();
		}
	}


	return  liczba;
}
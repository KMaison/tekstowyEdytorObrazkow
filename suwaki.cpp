#include"Suwaki.h"

void Suwaki::inicjalizowanie_suwakow(Rozmiar* rozmiartablicy, Pozycja* punkt){
	{
		rozmiar = rozmiartablicy;
		punkt_rysowania = punkt;
	}
}

void Suwaki::rysowanie_ramek_suwakow()
{
	textcolor(WHITE);
	//rysowanie dolnego suwaka
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < ROZMIAR_RAMKI_X; j++) {
			if (i == 0 || i == 2 || j == 0 || j == ROZMIAR_RAMKI_X - 1)
			{
				gotoxy(MIEJSCE_X + j, MIEJSCE_Y + ROZMIAR_RAMKI_Y + i);
				cputs("x");
			}
		}
	}

	//rysowanie gornego suwaka
	for (int i = 0; i < ROZMIAR_RAMKI_Y; i++) {
		for (int j = 0; j < 3; j++) {
			if (i == 0 || i == ROZMIAR_RAMKI_Y - 1 || j == 0 || j == 2)
			{
				gotoxy(MIEJSCE_X + ROZMIAR_RAMKI_X + j, MIEJSCE_Y + i);
				cputs("x");
			}
		}
	}
}

void Suwaki::dzialanie_suwakow() {

	float x = (*rozmiar).x; //rozmiar tablicy x i y
	float y = (*rozmiar).y;
	float rx = ROZMIAR_OBRAZKA_X; //rozmiar czesci do rysowania
	float ry = ROZMIAR_OBRAZKA_Y;


	float X = x / rx; //stosunek wymiarow rzeczywistych tablicy do rozmiaru czesci rysowalnej
	float Y = y / ry;

	int rozmiardol = round((DOL) / X);					//zaokraglony stosunek miejsca na suwak do X
	int rozmiarprawo = round((PRAWO) / Y);

	if (rozmiardol > DOL) rozmiardol = DOL;				//aby suwak nie byl wiekszy niz ramka na niego
	if (rozmiarprawo > PRAWO) rozmiarprawo = PRAWO;

	float px = (float)(*punkt_rysowania).x / (float)(*rozmiar).x;		// okresla przesuniecie x,y w
	float py = (float)(*punkt_rysowania).y / (float)(*rozmiar).y;		// % / 100 wyswietlania obrazka

	int ruchx = px*(DOL);
	int ruchy = py*(PRAWO);

	for (int i = 0; i < DOL; i++) {
		if (i >= ruchx && i <= rozmiardol + ruchx) //uzupelnia tablice dol tak aby mozna bylo narysowac
			dol[i] = true;							//na podstawie tego suwak
		else
			dol[i] = false;
	}
	for (int i = 0; i < PRAWO; i++) {
		if (i >= ruchy && i <= rozmiarprawo + ruchy)
			prawo[i] = true;
		else
			prawo[i] = false;
	}
}

void Suwaki::rysowanie_suwakow() {

	dzialanie_suwakow();
	textcolor(LIGHTBLUE);
	for (int i = 0; i < DOL; i++) {
		gotoxy(MIEJSCE_X + i + 1, MIEJSCE_Y + ROZMIAR_RAMKI_Y + 1);
		if (dol[i])
		{
			//miejsce_x = miejsce ramki
			cputs("x");
		}
		else
		{
			//gotoxy(MIEJSCE_X + i + 1, MIEJSCE_Y + ROZMIAR_OBRAZKA_Y + 1);
			cputs(" ");
		}
	}
	for (int i = 0; i < PRAWO; i++) {
		if (prawo[i])
		{
			gotoxy(MIEJSCE_X + ROZMIAR_RAMKI_X + 1, MIEJSCE_Y + i + 1);
			cputs("x");
		}
		else {
			gotoxy(MIEJSCE_X + ROZMIAR_RAMKI_X + 1, MIEJSCE_Y + i + 1);
			cputs(" ");
		}
	}
	textcolor(WHITE);
}
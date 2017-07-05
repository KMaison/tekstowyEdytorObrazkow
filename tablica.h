#pragma once
#include "Funkcje.h"
#include "Cursor.h"
#include "Suwaki.h"
struct Tablica
{
	Rozmiar rozmiar;
	int **tablica;
	int kolor;
	char nazwa_pliku[STRINGSIZE];
	Pozycja pozycja_rysowania;
	Pozycja sprawdzany_punkt;
	Cursor kursor;
	Suwaki suwaki;
	bool czy_zaalokowano;
	void inicjalizuj();
	void nowy_obrazek();
	void zmien_kolor(int znak);
	void zaalokuj_tablice();
	void zwolnij();
	void rysuj_ramke();
	void rysuj_tablice();
	bool odczyt_obrazka(char* nazwa = nullptr);
	bool zapis_wlasny();
	void przesuwaj(int znak);
	void prostokat(Suwaki suwaki);
	void wypelnianie_pola(int kolor_poczatkowy, int kolor_wybrany, int x,int y);
	bool zapis_obrazka_xpm2();
	bool odczyt_obrazka_xpm2(char* nazwa = nullptr);
	char* String();//wczyta tablice char z klawiatury
	int Int();
};



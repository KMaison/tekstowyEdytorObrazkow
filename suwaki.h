#pragma once
#include"Funkcje.h"

struct Suwaki {

	Rozmiar* rozmiar;
	Pozycja *punkt_rysowania;

	bool dol[DOL];
	bool prawo[PRAWO];

	void inicjalizowanie_suwakow(Rozmiar* rozmiartablicy, Pozycja* punkt);

	void rysowanie_ramek_suwakow();
	void dzialanie_suwakow();		//przelicza rysowanie scrollbarow
	void rysowanie_suwakow();

};
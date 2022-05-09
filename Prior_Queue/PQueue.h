#pragma once

#include "global.h"

#include<stdlib.h>
#include<stdio.h>
#include<memory.h>
#include<cstdlib>

#define PRIOR_ERROR INT_MIN 
#define POS_ERROR -1

typedef struct { // zachowac oryginalne nazwy!!!!!!

	 PQINFO* info; // Ptr to user info
	 int nPrior; // prior value (int) for the user info

} PQItem; // type of the queue item


typedef struct { // zachowac oryginalne nazwy!!!!!!

	PQItem** pPQueue; // kolejka realizowana w postaci stogu (dynamiczna tablica)
	int nPQSize; // rozmiar calkowity kolejki priorytetowej
	int nPQCurrSize; // ilosc elelemntow w kolejce (jednoczensie indeks pierwszego wolnego miejsc w kolejce

} PQueue;


PQueue* PQInit( int nSize ); // kreuje kolejke o zadanym rozmiarze i zwraca wskaznik do niej lub NULL gdy blad
int PQisEmpty( PQueue* q ); // zwraca 0 lub 1 - kolejka pusta/nie pusta
int PQSize( PQueue* q ); // zwraca ilosc elementow w kolejce
int PGMaxPrior( PQueue* q ); // zwraca najwiekszy priorytet w kolejce (z zerowej pozycji) lub PRIOR_ERROR
int PQEnqueue( PQueue* q, int nPrior, PQINFO* info ); // wstawia do kolejki informacje o zadanym priorytecie, zwraca 0 (niepowodzenie)lub 1 (powodzenie)
PQINFO* PQDequeue( PQueue* q ); // zwraca informacje o najwyzszym priorytecie lub NULL gdy niepowodzenie
void PQClear( PQueue* q, void( __cdecl* )(const void*) ); // czysci cala kolejke zwalniajac pamiec alokowana przez uzytkownika (na info), nie znana struktura do zwolnienia dlatego przekazac trzeba funkcje uzytkownika do zwolnienia pamieci przez parametr
void PQRelease( PQueue** q, void( __cdecl* )(const void*) ); // zwraca w parametrze we-wy NULL (kolejka) usuwaj¹c wszyskto wczesniej (czyszczenie kolejki)
void PQPrint( PQueue* q, int IndekStartowy, void( __cdecl* )(const void*) ); // drukuje w porzadku preorder (rekurencyjnie) od zadanej pozycji, aby wydrukowaæ info uzytkownika przekazac trzeba funkcje drukujaca ta informacje. Dodatkowo, drukuje priorytet w okraglych nawiasach oraz pozycje w kolejce w kwadratowych nawiasach
int PQSetPrior( PQueue* q, PQINFO* Infoinfo, int NewPrior, int( __cdecl* compareInfo )(const void*, const void*) ); // ustawia nowy priorytet dla zadanej informacji uzytkownika, nie znana struktura informacji, która trzeba wyszukac dlatego nalezy przekazac funkcje porownujaca informacje uzytkownika. Funkcja zwraca poprzedni priorytet lub PRIOR_ERROR
int PQsetPrior( PQueue* q, int IndeksTablicy, int NewPrior ); // ustawia nowy priorytet dla informacji uzytkownika bedacej na zadanej pozycji w kolejce( indeks w tablicy ), Funkcja zwraca poprzedni priorytet. W przypadku bledu zwraca PRIOR_ERROR
int PQGetPrior( PQueue* q, PQINFO* Infoinfo, int( __cdecl* compareInfo )(const void*, const void*) ); // zwraca priorytet informacji uzytkownika w kolejce lub PRIOR_ERROR, nieznana struktura informacji, która trzeba wyszukac dlatego nalezy przekazac funkcje porownujaca informacje uzytkownika
int PQgetPrior( PQueue* q, int tablica ); // zwraca priorytet informacji uzytkownika z zadanej pozycji w kolejce lub PRIOR_ERROR
int PQFind( PQueue* q, PQINFO* Infoinfo, int( __cdecl* compareInfo )(const void*, const void*) ); // zwraca indeks wyszukiwanej informacji uzytkownika, nie znana struktura informacji uzytkownika dlatego przekazac trzeba funkjce porownujaca informacje uzytkownika. Zwaraca POS_ERROR jesli nie ma info w kolejce
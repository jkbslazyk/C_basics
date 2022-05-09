#include "global.h"

#include<stdlib.h>
#include<stdio.h>
#include<memory.h>
#include <cstdlib>

typedef struct {

    QFItem** pFQItems; // dynamiczna tablica wskaznikow do informacji
    int nHead; // indeks pierwszego elementu w kolejce
    int pTail; // indeks pierwszego wolnego miejsca w kolejce( po ostatnim zajetym )
    int nNoElem; // ilosc elementow kolejki
    int nMaxElem; // rozmiar kolejki( rozmiar tablicy pFQItems )
}QFIFO;

QFIFO* QFCreate( int nSize );
int QFEmpty( QFIFO* q );
int QFEnqueue( QFIFO* q, QFItem* pItem );
QFItem* QFDequeue( QFIFO* q );
void QFClear( QFIFO* q, void( __cdecl* )(const void*) );
void QFRemove( QFIFO** q, void( __cdecl* )(const void*) );
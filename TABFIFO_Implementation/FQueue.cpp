#include "FQueue.h"
#include <stdlib.h>

void QDel( QFIFO* q );

QFIFO* QFCreate( int nSize ) {

    if ( nSize < 1 )
        printf( "Zly(za maly) rozmiar tablicy" );

    QFIFO* TabFIFO = (QFIFO*)calloc( 1, sizeof( QFIFO ) );

    if ( !TabFIFO ) {

        perror( "Blad kreowania kolejki" );
        return NULL;
    }

    TabFIFO->pFQItems = (QFItem**)calloc( nSize, sizeof( QFItem* ) );

    if ( !TabFIFO->pFQItems ) {

        perror( "Blad kreowania tablicy zawierajacej informacje" );
        return NULL;
    }


    TabFIFO->nMaxElem = nSize;


    return TabFIFO;

}

int QFEmpty( QFIFO* q ) {

    return ( !q || !q->nNoElem );

}

int QFEnqueue( QFIFO* q, QFItem* pItem ) {

    if ( !q ) {
        perror( "Error: Blad przy alokowaniu pamieci dla kolejki, nie mozna dodac elementu" );
        return 0;
    }

    if ( q->nMaxElem == q->nNoElem ) {
        perror( "Kolejka przepelniona, nie mozna dodac elementu" );
        return NULL;
    }

    q->pFQItems[q->pTail] = pItem;

    q->pTail = (q->pTail + 1) % q->nMaxElem;

    q->nNoElem++;

    return 1;

}


void QDel( QFIFO* q ) {

    if ( !q ) {
        perror( "Error: blad przy alokowaniu pamieci dla kolejki" );
        return;

    }

    if ( QFEmpty( q ) ) {
        perror( "Error: QDel" );
        return;
    }

    q->pFQItems[q->nHead] = NULL;


    q->nHead = (q->nHead + 1) % q->nMaxElem;

    q->nNoElem--;

}

QFItem* QFDequeue( QFIFO* q ) {

    if ( !q ) {
        perror( "Error: Blad przy alokowaniu pamieci dla kolejki, nie mozna usunac elementu" );
        return NULL;
    }

    if ( QFEmpty( q ) ) {

        perror( "Nie mozna usunac elementu, poniewaz kolejka jest pusta" );
        //return NULL;
    }

    QFItem* Element = q->pFQItems[q->nHead];

    QDel( q );

    return Element;

}

void QFClear( QFIFO* q, void( __cdecl* freeInfo )(const void*) ) {

    if ( !q ) {
        perror( "Error: QFClear" );
        return;
    }

    while ( !QFEmpty( q ) )
        freeInfo( QFDequeue( q ) );

    q->nHead = q->pTail = 0;
}

void QFRemove( QFIFO** q, void( __cdecl* freeInfo )(const void*) ) {

    if ( !q || !(*q) )
        perror( "Eror: QFRemove" );


    QFClear( *q, freeInfo );
    free( (*q)->pFQItems );
    free( *q );
    *q = NULL;

}
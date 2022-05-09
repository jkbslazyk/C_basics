#include"FQueue.h"

void  QFDel( QFIFO* q );


QFIFO* QFCreate() {

    QFIFO* p = (QFIFO*)calloc( 1, sizeof( QFIFO ) );
    if ( !p ) {
        perror( "Blad alokacji" );
    }

    return p;
}

int QFEmpty( QFIFO* q ) {

    return  !q || !q->pHead;
}

int QFEnqueue( QFIFO* q, QInfo* pInformation ) {

    if ( !q ) {
        perror( "Error: Blad przy alokowaniu pamieci dla kolejki, nie mozna dodac elementu" );
        return 0;
    }

    QFItem* pItem = (QFItem*)calloc( 1, sizeof( QFItem ) );//alokuje pamiec dla nowego elementu listy
    if ( !pItem ) {
        perror( "Blad alokacji pamieci podczas dodawania nowego elementu" );
        return 0;
    }

    pItem->pInfo = pInformation;

    if ( QFEmpty( q ) )
        q->pHead = pItem;

    else q->pTail->pNext = pItem;


    q->pTail = pItem; //powiazanie ogona z dodanym elementem

    return 1;
}

QInfo* QFDequeue( QFIFO* q ) {

    if ( !q ) {
        perror( "Error: Blad przy alokowaniu pamieci dla kolejki, nie mozna usunac elementu" );
        return NULL;
    }

    if ( !QFEmpty( q ) ) {
        QInfo* ptr = q->pHead->pInfo;
        QFDel( q );

        return ptr;
    }

    perror( "Nie mozna usunac elementu z pustej kolejki" );
    return NULL;
}

void  QFClear( QFIFO* q ) {

    if ( !q ) {
        printf( "Error: QFClear" );
        return;
    }

    while ( !QFEmpty( q ) )
        free( QFDequeue( q ) );

}

void QFRemove( QFIFO** q ) {

    if ( !q || !*q )
        printf( "Error: QFRemove" );

    QFClear( *q );
    free( *q );//tutaj blad
    *q = NULL;

}


void QFDel( QFIFO* q ){

    if ( !q ) {
        perror( "Error: blad przy alokowaniu pamieci dla kolejki" );
        //return;

    }

    if ( !QFEmpty( q ) ){

        QFItem* remover = q->pHead; // podczepiamy pierwszy element kolejki
        q->pHead = q->pHead->pNext; // przesuwamy wska�nik pHead na kolejny element kolejki
        free( remover );
    }

    if ( QFEmpty( q ) ) {
        perror( "Error: kolejka jest pusta (QFDel)" );
        q->pTail = NULL;
        return;
    }
}


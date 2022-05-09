#include"FQueue.h"

QFIFO* QFCreate() {

    QFIFO* p = (QFIFO*)calloc( 1, sizeof( QFIFO ) );
    if ( !p ) {
        perror( "Blad alokacji" );
        return 0;
    }

    QFItem* SentinelNode = (QFItem*)calloc( 1, sizeof( QFItem ) );
    if ( !SentinelNode ) {
        perror( "SentinalNode" );
        return 0;
    }

    p->pHead = p->pTail = SentinelNode;
    return p;
}

int QFEmpty( QFIFO* q ) {

    return ( !q || !q->pHead->pNext );

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


    q->pTail->pNext = pItem;//podczepiam na koniec nowy element
    q->pTail = pItem; //powiazanie ogona z dodanym elementems

    return 1;
}

QInfo* QFDequeue( QFIFO* q ) {

    if ( !q ) {
        perror( "Error: Blad przy alokowaniu pamieci dla kolejki, nie mozna usunac elementu" );
        return NULL;
    }

    if ( !QFEmpty( q ) ) {
        QInfo* ptr = q->pHead->pNext->pInfo;//wskaznik na pierwszy element
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

void  QFRemove( QFIFO** q ) {

    if ( !q || !(*q) )
        printf( "Error: QFRemove" );

    QFClear( *q );
    free( (*q)->pHead );
    free( *q );
    *q = NULL;
}

void QFDel( QFIFO* q ) {

    if ( !q ) {
        perror( "Error: blad przy alokowaniu pamieci dla kolejki" );
        return;

    }

    if ( !QFEmpty( q ) ) {

        QFItem* remover = q->pHead->pNext; // podczepiamy pierwszy element kolejki
        q->pHead->pNext = remover->pNext; // przesuwamy wska�nik pHead na kolejny element kolejki
        free( remover );
    }

    if ( QFEmpty( q ) ) {
        q->pTail = q->pHead;
        return;
    }

}
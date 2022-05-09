#include "FQueue.h"

void freeInfo( const void* );

int main() {


    QFIFO* Fifo = QFCreate( 4 );

    for ( int i = 0; i < 4; i++ ) {
        QFItem* pInfofo = (QFItem*)calloc( 1, sizeof( QFItem ) );
        int* infotab = (int*)calloc( 2, sizeof( int ) );
        pInfofo->pTab = infotab;
        pInfofo->n_Key = pInfofo->pTab[0] = 2 * i + 4;
        QFEnqueue( Fifo, pInfofo );
    }//dodaj 4 elementy

    for ( int i = 0; i < 3; i++ ) {
        QFItem* d = QFDequeue( Fifo );
        printf( "%d ", d->n_Key );
    }//usun 3 elementy

    for ( int i = 0; i < 2; i++ ) {
        QFItem* pInfofo = (QFItem*)calloc( 1, sizeof( QFItem ) );
        int* infotab = (int*)calloc( 2, sizeof( int ) );
        pInfofo->pTab = infotab;
        pInfofo->n_Key = pInfofo->pTab[0] = 2 * i + 14;
        QFEnqueue( Fifo, pInfofo );
    }//dodaj 2 elementy

    QFClear( Fifo, freeInfo );// wyczysc kolejke

    for ( int i = 0; i < 3; i++ ) {
        QFItem* pInfofo = (QFItem*)calloc( 1, sizeof( QFItem ) );
        int* infotab = (int*)calloc( 2, sizeof( int ) );
        pInfofo->pTab = infotab;
        pInfofo->n_Key = pInfofo->pTab[0] = 2 * i + 24;
        QFEnqueue( Fifo, pInfofo );
    }//dodaj 3 elementy

    QFItem* d = QFDequeue( Fifo );
    printf( "%d ", d->n_Key );//usun jeden element


    QFRemove( &Fifo, freeInfo );//usun cala kolejke

    return 0;
}

void freeInfo( const void* xyz ) {

    free( ((QFItem*)xyz)->pTab );
    free( (QFItem*)xyz );

}


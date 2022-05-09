#include"FQueue.h"


int main() {

    QFIFO* Fifo = QFCreate();

    for ( int i = 0; i < 4; i++ ) {
        QInfo* pInfofo = (QInfo*)calloc( 1, sizeof( QInfo ) );
        QFEnqueue( Fifo, pInfofo );
        pInfofo->n_Key = 2 * i + 4;
    }

    for ( int i = 0; i < 3; i++ ) {
        printf( "%d ", QFDequeue( Fifo )->n_Key );
    }

    for ( int i = 0; i < 2; i++ ) {
        QInfo* pInfofo = (QInfo*)calloc( 1, sizeof( QInfo ) );
        QFEnqueue( Fifo, pInfofo );
        pInfofo->n_Key = 2 * i + 14;

    }

    QFClear( Fifo );

    for ( int i = 0; i < 2; i++ ) {
        QInfo* pInfofo = (QInfo*)calloc( 1, sizeof( QInfo ) );
        QFEnqueue( Fifo, pInfofo );
        pInfofo->n_Key = 2 * i + 24;

    }

    printf( "%d ", QFDequeue( Fifo )->n_Key );

    QFRemove( &Fifo );

    return 0;

}
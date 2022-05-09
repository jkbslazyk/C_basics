#include <stdio.h>
#include "SortAlg.h"
#include <stdlib.h>
#include <time.h>
#include <memory.h>

#define SIZE 50
#define CONST 10
#define DEBUG

typedef void (*Sorts)( int*, int );

int CreateTab( int** tab, int nSize ); 
void PrintTab( int* tab, int nSize );
void InitTab( int* tab, int nSize );

int main(int argc, char* argv[]) {

    if ( argc != 2 ) {
       printf( "Usage: %s tab_size\n", argv[1] );
       return 1;
    }

    int TABSIZE = atoi( argv[1] );

    int* OrgTab = NULL;
    int* NorgTab = NULL;

    if ( !(CreateTab( &OrgTab, TABSIZE ) && CreateTab( &NorgTab, TABSIZE )) ) {
        perror( "Blad alokacji pamieci przy pierwszej probie" );
        return 1;
    }

	Sorts pSortTab[] = { SelectionSort, InsertSort, BubbleSort, MixedSort, HeapSort, HalfSort, QuickSort };
	const char* SortName[] = { "Sortowanie przez wybieranie", "Sortowanie przez wstawianie", "Sortowanie babelkowe", "Sortowanie mieszane(bablkowe)", "Sortowanie stogowe", "Sortowanie polowkowe", "Sortowanie szybkie" };
   
    InitTab( OrgTab, TABSIZE );

    int size = sizeof( pSortTab ) / sizeof( Sorts );

    for ( int i = 0; i < size; i++ ) {
        memcpy( NorgTab, OrgTab, sizeof( int ) * TABSIZE );
        time_t start = clock();//moment od ktorego liczy czas;
        pSortTab[i]( NorgTab, TABSIZE );
        time_t end = clock();
        double time = (double)(end - start) / CLOCKS_PER_SEC;
        printf( "%s: %f\n", SortName[i], time );

#ifdef DEBUG
        printf( "\n" );
        PrintTab( NorgTab, (TABSIZE < SIZE) ? TABSIZE : SIZE );
        printf( "\n\n" );
#endif

    }

	return 0;
}


int CreateTab( int** tab, int nSize ) {
    *tab = (int*)malloc( nSize * sizeof( int ) );
    if ( !tab ) 
        return 0;
   
    memset( *tab, 0, nSize*sizeof(int) );
    return 1;
}

void PrintTab( int* tab, int nSize ) {

    for ( int i = 0; i < nSize; i++ ) {
        printf( "%d ", *tab++ );
        if ( !((i + 1) % CONST) )
            printf( "\n" );
    }
}//do testowania sortowan

void InitTab( int* tab, int nSize ) {

    srand( (unsigned int)time( NULL ) );
    for ( int i = 0; i < nSize; i++ ) 
        *tab++ = rand() % nSize;
    
}
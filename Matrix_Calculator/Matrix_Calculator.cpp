#include "MatrixFun.h"
#include"VectorFun.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <math.h>



void readData( FILE* fin, double** pMatrix, double* bTab, int nDim );

int main( int argc, char** argv )
{
	if ( argc != 2 ) {
		printf( "Usage: %s", argv[0] );
		return 1;
	}

	FILE* fin;
	if ( (fin = fopen( argv[1], "r" )) == NULL ) {
		printf( "Error open file %s :(\n", argv[1] );
		return 2;
	}
	int nDim;
	fscanf( fin, "%d", &nDim );
	double** pTab = NULL;
	double* bTab = NULL;

	if ( !createMatrix( &pTab, nDim ) || !createVec( &bTab, nDim ) ) {
		perror( "Error 2: Nie udalo sie utworzyc macierzy i/lub wektora!" );
		return 3;
	}
	
	readData( fin, pTab, bTab, nDim );

	if ( fclose( fin ) != 0 ) {
		perror( "Error: Nie udalo sie zamknac pliku" );
		return 4;
	}

	double det = determinant( pTab, nDim );
	if ( fabs( det ) < 1.e-16 ) {
		perror( "Macierz osobliwa" );
		return 5;
	}
	double** inv = NULL;

	if ( !createMatrix( &inv, nDim ) ) {
		perror( "Error 3: Nie udalo sie utworzyc macierzy odwrotnej (blad allokacji) " );
		return 6;
	}
	
	InverseMatrix( inv, pTab, nDim, det );
	
	double* pRes = NULL;
	if ( !createVec( &pRes, nDim ) ) {
		perror( "Blad alokacji pamieci dla tablicy wynikow" );
		return 7;
	}
	
	
	layoutEquation( inv, bTab, pRes, nDim );

	printf( "Macierz wejsciowa:\n" );
	printMatrix( pTab, nDim );
	printf( "\nWejsciowy wektor:\n" );
	printVec( bTab, nDim );
	printf( "\n\nMacierz odwrotna\n" );
	printMatrix( inv, nDim );
	printf( "\nRozwiazanie:\n" );
	printVec( pRes, nDim );

	deleteMatrix( &pTab, nDim );  
	deleteMatrix( &inv, nDim );
	deleteVec( &bTab, nDim );
	deleteVec( &pRes, nDim );
	printf( "\n\nProgram wykonal sie pomyslnie, gratulacje mlody programisto!(0)\n" );
	return 0;
}

void readData( FILE* fin, double** pMatrix, double* bTab, int nDim ) {

	for ( int i = 0; i < nDim; i++ ) {
		double* ptr = *pMatrix++;
		for ( int j = 0; j < nDim; j++ )
			fscanf( fin, "%lf", ptr++ );

		fscanf( fin, "%lf", bTab++ );
	}


}

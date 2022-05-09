#include"ShipsFun.h"
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>


int move( int** pDepthTab, int nRow, int nCol, int nDepth, int move, int x, int y, int* px, int* py, int** pRoot ) {

	switch( move ) {
	case UP: *px=x-1; *py = y; break;
	case RIGHT: *px = x; *py=y+1; break;
	case DOWN: *px=x+1; *py = y; break;
	case LEFT: *px = x; *py=y-1; break;
	default: perror( "Wrong direction" ); return 0;
	}

	if( *px >= 0 && *px < nRow && *py >= 0 && *py < nCol ) {
		if( pDepthTab[*px][*py] > nDepth && pRoot[*px][*py] == 0 )
			return 1;
	}
	return 0;
}


int root( int** pDepthTab, int nRow, int nCol, int nDepth, int x, int y, int** pRoot, int x_dest, int y_dest ) {

	static int stepNumber = 1;
	pRoot[x][y] = stepNumber++;
	if ( x == x_dest && y == y_dest )
		return 1;


	int tempx = 0;
	int tempy = 0;
	for( int i = UP; i <= LEFT; i++ ) {
		if( move( pDepthTab, nRow, nCol, nDepth, i, x, y, &tempx, &tempy, pRoot ) )
			if( root( pDepthTab, nRow, nCol, nDepth, tempx, tempy, pRoot, x_dest, y_dest ) )
				return 1;
	}
	stepNumber--;
	pRoot[x][y] = 0;

	return 0;
}

int readDepthTab( char* sFile, int** pTab, int nRow, int nCol ) {

	FILE* fin = NULL;
	fin = fopen( sFile, "r" );
	if( !fin ) {
		perror( "ERROR 1: Opening file impossible" );
		return 0;
	}
	
	for( int i = 0; i < nRow; i++ ) {
		int* ptr = *pTab++;
		for( int j = 0; j < nCol; j++ )
			fscanf( fin, "%d", ptr++ );
	}

	fclose( fin );
	
	return 1;
}



int** CreateTab( int nRow, int nCol ) {

	int* Tab = (int*)malloc( sizeof( int ) * nRow * nCol );
	int** ptrTab = (int**)malloc(sizeof( int* ) * nRow);
	if( !(Tab || ptrTab) ) 
		return 0;

	memset( Tab, 0, nCol * nRow * sizeof( int ) );
	int** PtrTemp = ptrTab;
	for( int i = 0; i < nRow; i++ ) {
		*PtrTemp++ = Tab;
		Tab += nCol;
    }

	return ptrTab;
}


void PrintTab( int** pRoot, int nRow, int nCol ) {
	for( int i = 0; i < nRow; i++, pRoot++ ) {
		int* ptr = *pRoot;
		for( int j = 0; j < nCol; j++ ) {
			if ( *ptr >= 0 && *ptr <= 9 )//czesciowo wyrownuje tablice, bardziej czytelne i estetyczne
				printf( " " );
			printf( "%d ", *ptr++ );
			
		}
		printf( "\n" );
	}
}

void freeTab( int*** pTab) {
	
	free( **pTab );
	free( *pTab );
	*pTab = NULL;
}
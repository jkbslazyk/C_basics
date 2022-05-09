#include "ShipsFun.h"
#include <stdio.h>

#define FERRYDEPTH 4
#define COL 8
#define ROW 8

int main( int argc, char** argv ) {

	if( argc != 2 ) {
		printf( "Usage: %s", argv[0] );
		return 1;
	}

	int** ControlTab = NULL;
	int** MoveTab = NULL;

	ControlTab = CreateTab( ROW, COL );
	MoveTab = CreateTab( ROW, COL );

	if( !(ControlTab || MoveTab) ){
		perror( "Blad alokacji pamieci" );
		return 1;
	}

	if( readDepthTab( argv[1], ControlTab, ROW, COL ) ) {


		if( root( ControlTab, ROW, COL, FERRYDEPTH, 0, 0, MoveTab, ROW - 1, COL - 1 ) ) {
			printf( "Nawigacja: \n" );
			PrintTab( MoveTab, ROW, COL );
		}

		else
			printf( "Nie ma mozliwosci doplynac do portu!!\n\n" );
	}

	freeTab( &ControlTab );
	freeTab( &MoveTab );
	return 0;
}
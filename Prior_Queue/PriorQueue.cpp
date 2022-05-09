#include "PQueue.h"

int main() {

	PQueue* PriorQ = PQInit( 20 );
	for ( int j = 0; j < 6; j++ ) {
		PQINFO* Informacja = (PQINFO*)calloc( 1, sizeof( PQINFO ) );
		int* infotab = (int*)calloc( 2, sizeof( int ) );
		Informacja->pTab = infotab;
		Informacja->nKey = Informacja->pTab[0] = j % 2 * j + j;
		PQEnqueue( PriorQ, j, Informacja );
	}

	PQPrint( PriorQ, 0, printInfo );

	printf( "\n" );

	printf( "%d ", PQDequeue( PriorQ )->nKey );

	printf( "\n" );

	for ( int j = 0; j < 2; j++ ) {
		PQINFO* Informacja = (PQINFO*)calloc( 1, sizeof( PQINFO ) );
		int* infotab = (int*)calloc( 2, sizeof( int ) );
		Informacja->pTab = infotab;
		Informacja->nKey = Informacja->pTab[0] = 100 * j;
		PQEnqueue( PriorQ, j, Informacja );
	}

	printf( "\n" );

	PQPrint( PriorQ, 0, printInfo );

	printf( "\n" );

	PQINFO* NoweInfo = (PQINFO*)calloc( 1, sizeof( PQINFO ) );
	NoweInfo->nKey = 2;

	printf( "Poszukiwany element znaleziono na pozycji: %d", PQFind( PriorQ, NoweInfo, compareInfo ) );

	printf( "\n" );

	PQSetPrior( PriorQ, NoweInfo, 22, compareInfo );

	PQPrint( PriorQ, 0, printInfo );

	printf( "\n" );

	printf("%d", PQsetPrior( PriorQ, 3, -1 ));

	PQRelease( &PriorQ, freeInfo );

	return 0;
}


void freeInfo( const void* RandomName ) {

	free( ((PQINFO*)RandomName)->pTab );
	free( (PQINFO*)RandomName );

}

void printInfo( const void* RandomName2 ) {

	printf( "%d", ((PQINFO*)RandomName2)->nKey );

}

int compareInfo( const void* Random1, const void* Random2 ) {

	if ( Random1 == NULL && Random2 == NULL )
		return 0; 

	if ( Random1 == NULL )
		return -1;

	if ( Random2 == NULL )
		return 1;

	if ( ((PQINFO*)Random1)->nKey > ((PQINFO*)Random2)->nKey )
		return 1;

	if ( ((PQINFO*)Random1)->nKey < ((PQINFO*)Random2)->nKey )
		return -1;

	return 0;
}
#include "List.h"
#include <ctime>

void PrintList( ListItem* pList );

int main(){

	srand( time( NULL ) );

	ListItem* LastProject = CreateList();

	for ( int i = 0; i < 20; i++ ) {

		LISTINFO* Random2 = (LISTINFO*)calloc( 1, sizeof( ListItem ) );
		InsertFront( LastProject, Random2 );
		int* tablica = (int*)calloc( 2, sizeof( int ) );
		tablica[0] = i;
		Random2->p = tablica;
		if ( i == 9 )
			Random2->nKey = 2000;
		else
			Random2->nKey = rand() % 50;

	}

	printf( "Elementy dodane poczatkowo:\n" );
	PrintList( LastProject );

	SortList( LastProject, compareInfo );

	printf( "Elementy posortowane/n" );
	PrintList( LastProject );

	ListItem* pPpPrev;

	LISTINFO* element = (LISTINFO*)calloc( 1, sizeof( LISTINFO ) );
	element->nKey = 2000;
	Find( LastProject, element, &pPpPrev, compareInfo );

	LISTINFO* element1 = (LISTINFO*)calloc( 1, sizeof( LISTINFO ) );
	element1->nKey = 3000;
	Insert( pPpPrev, element1 );

	printf( "Po wyszukaniu info i dodaniu elementu:\n" );
	PrintList( LastProject );

	Remove( pPpPrev->pNext );

	printf( "Po usunieciu elementu z kluczem 2000:\n" );
	PrintList( LastProject );

	ClearList( LastProject, freeInfo );

	printf( "Po usunieciu wszystkiego:\n" );
	PrintList( LastProject );

	for ( int i = 0; i < 2; i++ ) {

		LISTINFO* Random2 = (LISTINFO*)calloc( 1, sizeof( ListItem ) );
		InsertFront( LastProject, Random2 );
		int* tablica = (int*)calloc( 2, sizeof( int ) );
		tablica[0] = i;
		Random2->p = tablica;
		Random2->nKey = rand() % 50;

	}

	printf( "Po dodaniu dwoch elementow: \n" );
	PrintList( LastProject );

	RemoveList( &LastProject, freeInfo );

	return 0;

}

void PrintList( ListItem* pList ) {

	ListItem* temp_helper = pList->pNext;
	int LastIntiger = 1;

	while ( temp_helper ) {

		printf( "Element numer: %d, wartosc: %d\n", LastIntiger, temp_helper->pInfo->nKey);
		LastIntiger++;
		temp_helper = temp_helper->pNext;
	}

	printf( "\n\n" );
}

void freeInfo( const void* RandomName ) {

	free( (LISTINFO*)RandomName );

}

int compareInfo( const void* Random1, const void* Random2 ) {

	if ( Random1 == NULL && Random2 == NULL )
		return 0;

	if ( !Random1 )
		return -1;

	if ( !Random2 )
		return 1;

	if ( ((LISTINFO*)Random1)->nKey > ((LISTINFO*)Random2)->nKey )
		return 1;

	if ( ((LISTINFO*)Random1)->nKey < ((LISTINFO*)Random2)->nKey )
		return -1;

	return 0;
}
#include "List.h"

ListItem* CreateList() {

	ListItem* ListaProsta = (ListItem*)calloc(1, sizeof(ListItem) );

	return ListaProsta;

}

int InsertFront( ListItem* pList, LISTINFO* pInfo ){

	return Insert( pList, pInfo );

}

int Insert( ListItem* pAfter, LISTINFO* Info ) {

	if ( !pAfter )
		return 0;

	ListItem* Item = (ListItem*)calloc( 1, sizeof( ListItem ) ); 
	if ( !Item )
		return 0;
	
	Item->pInfo = Info; 
	Item->pNext = pAfter->pNext; 
	pAfter->pNext = Item; 

	return 1;
}

LISTINFO* RemoveFront( ListItem* pList ){

	return Remove( pList );
}

LISTINFO* Remove( ListItem* pAfter ){

	if ( !pAfter || IsEmpty( pAfter ) )
		return NULL;

	ListItem* Helper = pAfter->pNext;
	LISTINFO* InfoInfo = Helper->pInfo;
	pAfter->pNext = Helper->pNext;
	free( Helper  );
	return InfoInfo;
}

LISTINFO* Front( ListItem* pList ){

	if ( !pList || IsEmpty( pList ) )
		return NULL;
	
	return pList->pNext->pInfo;
}

int IsEmpty( ListItem* pList ){

	return !pList || !(pList->pNext);

}

void ClearList( ListItem* pList, void( __cdecl* )(const void*) ) {


	if ( !pList || !freeInfo ) {
		perror( "Error: Blad przy alokowaniu pamiecie dla listy - nie mozna wyczyscic listy (ClearList)" );
		return;
	}

	while ( !IsEmpty( pList ) )
		freeInfo( RemoveFront( pList ) );

}

void RemoveList( ListItem** pList, void( __cdecl* )(const void*) ) {

	if ( !pList || !*pList ) {

		perror( "Error: Blad przy alokowaniu pamiecie dla listy - nie mozna wyczyscic listy(RemoveList)" );
		return;
	}

	ClearList( *pList, freeInfo );
	free( *pList );
	*pList = NULL;

}

void SortList( ListItem* pList, int( __cdecl* compareInfo )(const void*, const void*) ){

	if ( !pList || !compareInfo ) {

		perror( "Error-SortList" );
		return;

	}

	ListItem* pFirst = pList;

	while ( pFirst->pNext ){

		ListItem* pMin = pFirst;
		ListItem* pCurr = pMin->pNext;

		while ( pCurr->pNext ){// przemieszczamy sie i szuakmy minimalnego

			if ( compareInfo( pMin->pNext->pInfo, pCurr->pNext->pInfo ) == 1 )
				pMin = pCurr; 
			pCurr = pCurr->pNext;	

		}

		if ( pFirst!= pMin ) { //podmieniamy jedynie gdy rozne

			pCurr = pMin->pNext->pNext;
			pMin->pNext->pNext = pFirst->pNext;
			pFirst->pNext = pMin->pNext;
			pMin->pNext = pCurr;

		}
		pFirst = pFirst->pNext; 
	}
}

ListItem* Find( ListItem* pList, LISTINFO* Info, ListItem** pPrev, int( __cdecl* compareInfo )(const void*, const void*) ) {

	if ( !pList || !compareInfo )
		return NULL;

	*pPrev = pList;

	while ( (*pPrev)->pNext ){

		if ( compareInfo( (*pPrev)->pNext->pInfo, Info ) == 0 )
			return (*pPrev)->pNext; 

		*pPrev = (*pPrev)->pNext; 
	 
	}

	return *pPrev = NULL;

}
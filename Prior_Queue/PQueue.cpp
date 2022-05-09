#include "PQueue.h"

void UpdateDown( PQItem** pPQueue, int left, int right ); // update heap down between index l and p <--- modified Update() from HeapSort
void UpdateUp( PQItem** pPQueue, int left, int right); // update heap up between index l and p

PQueue* PQInit( int nSize ) {

	if ( nSize <= 0 ) {
		perror( "Error: Podany rozmiar tablicy jest za maly (PQInit)" );
		return NULL;
	}

	PQueue* QueuePrior = (PQueue*)calloc( 1, sizeof( PQueue ) );

	if ( !QueuePrior ) {
		perror( "Error: Nie udalo sie zaalokowac pamieci dla QueuePrior (PQInit)" );
		return NULL;
	}


	QueuePrior->pPQueue = (PQItem**)calloc( nSize, sizeof( PQINFO ) );

	if ( !QueuePrior->pPQueue ) {
		perror( "Error: Nie udalo sie zaalokowac pamieci dla struktury pPQueue, zawierajacej wartosc priorytetu oraz informacje (PQInit)" );
		return NULL;
	}

	QueuePrior->nPQSize = nSize;

	return QueuePrior;

}

int PQisEmpty( PQueue* q ) {

	return !q || !q->nPQCurrSize;

}

int PQSize( PQueue* q ) {

	return (q) ? q->nPQCurrSize : PRIOR_ERROR;
}

int PGMaxPrior( PQueue* q ) {

	return (q && !PQisEmpty( q )) ? q->pPQueue[0]->nPrior : PRIOR_ERROR;
	
}

int PQEnqueue( PQueue* q, int Priority, PQINFO* information ) {

	if ( !q ) 

		return 0;

	int ix = PQSize( q );

	if ( ix == q->nPQSize )

		return 0;

	q->pPQueue[ix] = (PQItem*)calloc( 1, sizeof( PQItem ) );

	if ( !q->pPQueue[ix] )
		return 0;

	q->pPQueue[ix]->nPrior = Priority;
	q->pPQueue[ix]->info = information;
	q->nPQCurrSize++;
	
	if ( ix > 0 )
		UpdateUp( q->pPQueue, 0, ix );

	return 1;
}

PQINFO* PQDequeue( PQueue* q ) {

	if ( !q || PQisEmpty( q ) )
		
		return 0;
	

	int ix = --q->nPQCurrSize;

	PQInfo* d = q->pPQueue[0]->info;

	free( q->pPQueue[0] );

	if ( ix != 0 )
		q->pPQueue[0] = q->pPQueue[ix];

	if ( ix > 1 )
		UpdateDown( q->pPQueue, 0, ix-1 );

	return d;

}

void PQClear( PQueue* q, void(  __cdecl* freeInfo )(const void*)) {

	
		if ( !q || !freeInfo ) {
			perror( "Error: Blad przy alokowaniu pamiecie dla kolejki - nie mozna wyczyscic kolejki (PQClear)" );
			return;
		}

		while ( !PQisEmpty( q ) )
			freeInfo( PQDequeue( q ) );

}

void PQRelease( PQueue** q, void( __cdecl* freeInfo )(const void*) ) {

	if ( !q || !*q ) {
		perror( "Error: Blad przy alokowaniu pamiecie dla kolejki - nie mozna wyczyscic kolejki (PQRelease)" );
		return;
	}

	PQClear( *q, freeInfo );
	free( (*q)->pPQueue );
	free( *q );
	*q = NULL;

}

void PQPrint( PQueue* q, int IndekStartowy, void( __cdecl* printInfo )(const void*) ) {
	 
	if ( !q && IndekStartowy < 0 ) {
		perror( "PQPrint Error" );
		return;
	}

	if ( !PQSize( q ) ) {
		perror( "PQPrint Error(wrong size)" );
		return;
	}

	if ( IndekStartowy < PQSize( q ) ) {

		printf( "Element o priorytecie (%d) zajmuje indeks [%d] w tablicy i informacje: ", q->pPQueue[IndekStartowy]->nPrior, IndekStartowy );
		if ( printInfo )
			printInfo( q->pPQueue[IndekStartowy]->info );

		printf( "\n" );


		PQPrint( q, 2 * IndekStartowy + 1, printInfo );
		PQPrint( q, 2 * IndekStartowy + 2, printInfo );

	}
}

int PQSetPrior( PQueue* q, PQINFO* Infoinfo, int NewPrior, int( __cdecl* compareInfo )(const void*, const void*) ){

	return PQsetPrior( q, PQFind( q, Infoinfo, compareInfo ), NewPrior );
}

int PQsetPrior( PQueue* q, int IndeksTablicy, int NewPrior ) {

	int return_ = PQgetPrior( q, IndeksTablicy );

	if ( return_ != PRIOR_ERROR && return_ != POS_ERROR ) {
		
		q->pPQueue[IndeksTablicy]->nPrior = NewPrior;

		if ( NewPrior > return_ )
			UpdateUp( q->pPQueue, 0, IndeksTablicy );
		else UpdateDown( q->pPQueue, IndeksTablicy, q->nPQCurrSize - 1 );

		
	}

	return return_;

}

int PQGetPrior( PQueue* q, PQINFO* Infoinfo, int( __cdecl* compareInfo )(const void*, const void*) ) {

	return PQgetPrior( q, PQFind( q, Infoinfo, compareInfo ) );

}

int PQgetPrior( PQueue* q, int tablica ) {
	
	if ( !q || PQisEmpty( q ) ) 
		return PRIOR_ERROR;

	if ( tablica < 0 || tablica>q->nPQCurrSize - 1 )
		return POS_ERROR;
	
	return q->pPQueue[tablica]->nPrior;

}

int PQFind( PQueue* q, PQINFO* Infoinfo, int( __cdecl* compareInfo )(const void*, const void*) ) {

	if ( !q || !compareInfo )
		return NULL;


	for ( int i = 0; i < q->nPQCurrSize; i++ )

		if ( !compareInfo( q->pPQueue[i]->info, Infoinfo ) )

			return i;

	return PRIOR_ERROR;

}


void UpdateUp( PQItem** pPQueue, int left, int right ) {

	if ( left >= right ) {
		//perror( "Error: UpdateUp" );
		return;
	}


	int i = right;
	PQItem* prio = pPQueue[i];
	int j = (i - 1) / 2;
	while ( j >=left && pPQueue[j]->nPrior < prio->nPrior ) {

		pPQueue[i] = pPQueue[j];
		i = j;
		j = (i + 1) / 2 - 1;

	}

	pPQueue[i] = prio;

}

void UpdateDown( PQItem** pPQueue, int left, int right ) {

	if ( left >= right ) {
		//perror( "Error: UpdateDown" );
		return;
	}

	PQItem* LastPrio = pPQueue[left];
	int i = left;//korzen
	int j = 2 * i + 1;//lewe dziecko

	while ( j <= right ) {

		if ( pPQueue[j + 1]->nPrior > pPQueue[j]->nPrior )
			j++;

		if ( LastPrio->nPrior >= pPQueue[j]->nPrior ) break;

		pPQueue[i] = pPQueue[j];
		i = j;
		j = 2 * i + 1;
	}

	pPQueue[i] = LastPrio;

}
#include <stdlib.h>
#include <memory.h>
#include "MatrixFun.h"
#include <iostream>

void ComplMatrix( double** ptabD, double** pTab, int nDim );
void complement( double** pTabO, double** pTabT, int nRow, int nCol, int nDim );

int createMatrix( double*** pTab, int nDim ) {
	*pTab = (double**)malloc( sizeof( double* ) * nDim );
	if ( !pTab )
		return 0;

	memset( *pTab, 0, sizeof( double* ) * nDim );
	double** p = *pTab;
	for ( int i = 0; i < nDim; i++, p++ ) {
		*p = (double*)malloc( sizeof( double ) * nDim );
		if ( !*pTab )
			return 0;
		memset( *p, 0, sizeof( double ) * nDim );
	}
	return 1;
}


void deleteMatrix( double*** pTab, int nDim ) {
	double** v = *pTab;
	for ( int i = 0; i < nDim; i++ )
		free( *v++ );
	free( *pTab );
	*pTab = NULL;
}


void InverseMatrix( double** pInv, double** pTab, int nDim, double det )
{
	transposeMatrix( pTab, nDim );
	ComplMatrix( pInv, pTab, nDim );
	for ( int i = 0; i < nDim; i++, pInv++ ) {
		double* pointer2 = *pInv;
		for ( int j = 0; j < nDim; j++ ) {
			*pointer2++ /= det;
		}
	}
}

double determinant( double** pTab, int nDim ) {

	if ( nDim == 1 )
		return **pTab;
	if ( nDim == 2 )
		return **pTab * pTab[1][1] - pTab[0][1] * pTab[1][0];

	double** pPomocnicza = NULL;

	if ( !createMatrix( &pPomocnicza, nDim - 1 ) ) {
		perror( "ERROR 4: nie udalo sie zaalokowac pamieci w trakcie liczenia wyznacznika rekurencyjnie(double dterminant)\n" );
		return DBL_MIN;
	}
	double det = 0;
	double sign = 1;
	double* ptr = *pTab;

	for ( int i = 0; i < nDim; i++ ) {
		complement( pPomocnicza, pTab, 0, i, nDim );
		det += *ptr++ * determinant( pPomocnicza, nDim - 1 ) * sign;
		sign = -sign;
	}
	deleteMatrix( &pPomocnicza, nDim-1);
	return det;
}

void layoutEquation( double** pInv, double* pB, double* pRes, int nDim ) {

	for ( int i = 0; i < nDim; i++, pRes++, pInv++ ) {
		double* ptr3 = pB;
		double* ptr2 = *pInv;
		for ( int j = 0; j < nDim; j++ ) {
			*pRes += *ptr2++ * *ptr3++;
		}
	}
}

void printMatrix( double** pTab, int nDim ) {
	for ( int i = 0; i < nDim; i++, pTab++ ) {
		double* ptr = *pTab;
		for ( int j = 0; j < nDim; j++ )
			printf( "%lf ", *ptr++ );
		printf( "\n" );
	}
}


void transposeMatrix( double** pTab, int nDim ) {
	double** pointer1 = pTab;
	for ( int i = 0; i < nDim; i++, pointer1++ ) {
		double* pointer2 = *pointer1 + i+1;
		for ( int j = i+1; j < nDim ; j++, pointer2++ ) {
			double temp = *pointer2;
			*pointer2 = pTab[j][i];
			pTab[j][i] = temp;
			 
		}
	}
}

void ComplMatrix( double** pTabO, double** pTabI, int nDim ) 
{ 
	double** pPomocnicza = NULL; 
	if ( !createMatrix( &pPomocnicza, nDim - 1 ) ) {
		perror( "Blad alokacji pamieci(void ComplMaatrix)" );
		return;
	}
	

	for ( int i = 0; i < nDim; i++){

		double* D = *pTabO++;

		double sign = (i % 2) ? -1 : 1;
		for ( int j = 0; j < nDim; j++ )
		{
			complement( pPomocnicza, pTabI, i, j, nDim ); 
			*D++ = sign * determinant( pPomocnicza, nDim - 1 ); 
			sign = -sign;
		}

	}
	deleteMatrix( &pPomocnicza, nDim - 1 ); 
}

void complement( double** pTabO, double** pTabT, int nRow, int nCol, int nDim ) {

	for ( int i = 0; i < nDim; i++){

		double* pT = *pTabT++;
		if ( i == nRow )
			continue;
		double* pO = *pTabO++;
		
		for ( int j = 0; j < nDim; j++, pT++ ) {
			if ( j == nCol )
				continue;
			*pO++ = *pT;
		}  
	}
}

#include<stdlib.h>
#include<memory.h>
#include<iostream>
#include"VectorFun.h"

int createVec( double** vec, int nDim ) {
	*vec = (double*)malloc( nDim * sizeof( double ) );
	if ( *vec == 0 )
		return 0;
	memset( *vec, 0, nDim * sizeof( double ) );
	return 1;
}

void printVec( double* vec, int nDim ) {
	double* p = vec;
	for ( int i = 0; i < nDim; i++ ) {
		printf( "%lf\n", *p++ );
	}
}

void deleteVec( double** vec, int nDim ) {
	free( *vec );
	*vec = NULL;
}
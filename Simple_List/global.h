#pragma once

#include <cstdlib>

typedef struct {

	int nKey;
	int* p;
} ListInfo;

#define LISTINFO ListInfo

void freeInfo( const void* );
int compareInfo( const void*, const void* );


#pragma once

typedef struct
{
	int nKey;
	int* pTab; // moze byc dwuelementowa tablica
} PQInfo; // PQINFO - the user identyfier


void freeInfo( const void* );
void printInfo( const void* );
int compareInfo( const void*, const void* );

#define PQINFO PQInfo // nazwy PQINFO - uzywac WSZEDZIE - NAWET W PROGRAMIE TESTUJACYM!
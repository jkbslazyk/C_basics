#pragma once

#include"global.h"

#include<stdlib.h>
#include<stdio.h>
#include<memory.h>
#include<cstdlib>

typedef struct tagListItem {
	LISTINFO* pInfo;
    tagListItem* pNext;

} ListItem;

ListItem* CreateList( );
int InsertFront( ListItem* pList, LISTINFO* Info );
int Insert( ListItem* pAfter, LISTINFO* Info );
LISTINFO* RemoveFront( ListItem* pList);
LISTINFO* Remove( ListItem* pAfter );
LISTINFO* Front( ListItem* pList );
int IsEmpty( ListItem* pList );
void ClearList( ListItem* pList, void( __cdecl* )(const void*) );
void RemoveList( ListItem** pList, void( __cdecl* )(const void*) );
void SortList( ListItem* pList, int( __cdecl* compareInfo )(const void*, const void*) );
ListItem* Find( ListItem* pList, LISTINFO* Info, ListItem** pPrev, int( __cdecl* compareInfo )(const void*, const void*) );
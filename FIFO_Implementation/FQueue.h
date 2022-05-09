#ifndef fifo
#define fifo


#include<stdlib.h>
#include<stdio.h>
#include<memory.h>
#include <cstdlib>

typedef struct tagQInfo {

    int n_Key;

}QInfo;

typedef struct tagFIFOItem {

    QInfo* pInfo;
    tagFIFOItem* pNext;

}QFItem;

typedef struct {

    QFItem* pHead;
    QFItem* pTail;

}QFIFO;


QFIFO* QFCreate();
int QFEmpty( QFIFO* q );
int QFEnqueue( QFIFO* q, QInfo* pInfoo );
QInfo* QFDequeue( QFIFO* q );
void  QFClear( QFIFO* q );
void  QFRemove( QFIFO** q );

#endif

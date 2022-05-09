#ifndef GLOBAL_H
#define GLOBAL_H

typedef struct
{
    int* pTab;
    int n_Key;

} QInfo;

#define QFItem QInfo

void freeInfo( const void* );
#endif

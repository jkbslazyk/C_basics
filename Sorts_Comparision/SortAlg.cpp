#include <stdlib.h>
#include "SortAlg.h"

void Update( int* tab, int left, int right );
void Podzial( int* tab, int left, int right );

void InsertSort( int* tab, int nSize )
{
    for ( int i = 1; i < nSize; i++ )
    {
        int x = tab[i];
        int j = i - 1;
        while ( j >= 0 && tab[j] > x )
        {
            tab[j+1] = tab[j--];
        }
        tab[j+1] = x;
    }
}

void BubbleSort( int* tab, int nSize ) {

    for ( int j = 0; j < nSize - 1; j++ ) {
        for ( int i = nSize - 1; i > j; i-- ) {
            if ( tab[i] < tab[i - 1] ) {
                int temp = tab[i];
                tab[i] = tab[i - 1];
                tab[i - 1] = temp;
            }
        }
    }
}

void SelectionSort( int* tab, int nSize ) {

    for ( int i = 0; i < nSize - 1; i++ ) {

        int k = i;
        int min = tab[i];
        for ( int j = i + 1; j < nSize; j++ ) {
            if ( tab[j] < min ) {

                min = tab[j];
                k = j;
            }

        }
        tab[k] = tab[i];
        tab[i] = min;
    }
}

void MixedSort( int* tab, int nSize ) {
    int p = nSize - 1;
    int l = 1;
    int k = nSize - 1;

    do {
        for ( int j = p; j >= l; j-- ) {
            if ( tab[j - 1] > tab[j] ) {
                int temp = tab[j - 1];
                tab[j - 1] = tab[j];
                tab[j] = temp;
                k = j;
            }
        }
        l = k + 1;

        for ( int j = l; j <= p; j++ ) {
            if ( tab[j - 1] > tab[j] ) {
                int temp = tab[j - 1];
                tab[j - 1] = tab[j];
                tab[j] = temp;
                k = j;
            }
        }
        p = k - 1;
    } while ( l <= p );
}

void Update( int* tab, int left, int right ) {

    if ( left >= right )
        return;

    int i = left;
    int j = 2 * i + 1;
    int x = tab[i];
    while ( j <= right ) {

        if ( j < right )
            if ( tab[j] < tab[j + 1] )
                j++;

        if ( x > tab[j] ) break;

        tab[i] = tab[j];
        i = j;
        j = 2 * i+1;
    }
    tab[i] = x;
}

void HeapSort( int* tab, int nSize ) {

    int p = nSize - 1;
    for ( int j = (nSize / 2); j >= 0; j-- ) {
        Update( tab, j, p );
    }
    for ( int j = nSize - 1; j > 0; j-- ) {
        int x = tab[0];
        tab[0] = tab[j];
        tab[j] = x;
        Update( tab, 0, j - 1 );
    }
}

void HalfSort( int* tab, int nSize ) {

    for ( int i = 1; i < nSize; i++ ) {
        int x = tab[i];
        int l = 0;
        int p = i - 1;
        while ( l <= p ) {
            int m = (l + p) / 2;
            if ( x < tab[m] )
                p = m - 1;
            else
                l = m + 1;
        }

        for ( int j = i - 1; j >= l; j-- )
            tab[j + 1] = tab[j];

        tab[l] = x;

    }
}

void Podzial( int* tab, int left, int right ) {

    int i = left;
    int j = right;
    int x = tab[(left + right) / 2];

    while ( i < j ) {
        while ( tab[i] < x )
            i++;
        while ( x < tab[j] )
            j--;
        if ( i <= j ) {
            int w = tab[i];
            tab[i] = tab[j];
            tab[j] = w;
            i++;
            j--;
        }
    }

    if ( left < j )
        Podzial( tab, left, j );
    if ( i < right )
        Podzial( tab, i, right );
}

void QuickSort( int* tab, int nSize ) {
    Podzial( tab, 0, nSize - 1 );
}
#ifndef STATKOWEFUNKCJE
#define STATKOWEFUNCKJE

typedef enum CompassCard {
	UP = 1,
	RIGHT,
	DOWN,
	LEFT
} CompassCard;

int move( int** pDepthTab, int nRow, int nCol, int nDepth, int move, int x, int y, int* px, int* py, int** pRoot );
int root( int** pDepthTab, int nRow, int nCol, int nDepth, int x, int y, int** pRoot, int x_dest, int y_dest );
int readDepthTab( char* sFile, int** pTab, int nRow, int nCol );
int** CreateTab( int nRow, int nCol );
void PrintTab( int** pRoot, int nRow, int nCol );
void freeTab( int*** pTab );

#endif
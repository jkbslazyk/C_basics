#ifndef FUNCTIONSMATRIX
#define FUNCTIONSMATRIX

int createMatrix( double*** pTab, int nSize );
void deleteMatrix( double*** pTab, int nSize );
void InverseMatrix( double** pInv, double** pTab, int nSize, double det );
void transposeMatrix( double** pTab, int nDim );
double determinant( double** pTab, int nSize );
void printMatrix( double** pTab, int nSize );
void layoutEquation( double** pInv, double* pB, double* pRes, int nSize );

#endif 


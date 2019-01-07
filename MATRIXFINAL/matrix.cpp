#include "stdafx.h"

#define _DEBUG_

void Complement( double**, double**, int, int, int ); //wycina z tablicy (wyjœciowa, wejœciowa, i-ty wiersz, j-kolumna, rozmiar)
void ComplMatrix( double**, double **, int ); //liczenie macierzy dope³nieñ (dope³nieñ, wejœciowa, rozmiar)
void TransMatrix( double**, int); //transponowanie

//-----------------------------------------------------------------------
int CreateMatrix(double*** pTab, int nSize)
{
	double **p = *pTab = (double**)(calloc(nSize,sizeof(double*)));
	if(! (*pTab) ) return 0;

	for( int i = 0; i<nSize; i++, p++)
	{
		*p = (double*)(calloc(nSize,sizeof(double)));
		if(! (*p) ) return 0;
	}

	return 1;
}
//-----------------------------------------------------------------------
int DeleteMatrix(double*** pTab, int nSize)
{
	double** p = *pTab;

	for (int i = 0; i<nSize;i++,p++)
		free(*p);

	free(*pTab); 
	*pTab = NULL;

	return 1;
}
//-----------------------------------------------------------------------
void InverseMatrix( double** pInv, double** pTab, int nDim, double det)
{
	ComplMatrix( pInv, pTab, nDim );
	TransMatrix( pInv, nDim );

	int nRow, nCol;
	
	double** p = pInv;
	for( nRow = 0; nRow<nDim; nRow++ )
	{
		double *v = *p++;
		for( nCol=0; nCol<nDim; nCol++, v++ )
			*v /= det;
	}
}
//-----------------------------------------------------------------------
double Det(double** pTab, int nDim)
{
	if( nDim == 1 ) return pTab[0][0];
	else if( nDim == 2 ) return pTab[0][0]*pTab[1][1] - pTab[0][1]*pTab[1][0];

	double res = 0;

	double** pT = NULL;
	CreateMatrix( &pT, nDim-1 );

	double* p = *pTab;

	int pot = 1;
	for( int nCol = 0; nCol<nDim; nCol++ )
	{
		Complement( pT, pTab, 0, nCol, nDim );

		res += pot * (*p++) * Det( pT, nDim-1 );
        pot = -pot;	
	}

	DeleteMatrix( &pT, nDim-1 );
	return res;
}
//-----------------------------------------------------------------------
void LayoutEqu( double** pInv, double* pB, double* pRes, int nDim)
{
	for( int i=0; i<nDim; i++ )
	{
		double *p = pB;
		double *v = *pInv++;

		for( int j=0; j<nDim; j++)
			*pRes += *v++ * *p++;
		
		*pRes++;
	}
}
//-----------------------------------------------------------------------
void PrintMatrix( double** pTab, int nDim )
{
	for( int i=0; i<nDim; i++ )
	{
		double* v = *pTab++;
		for( int j=0; j<nDim; j++ )
			printf( "%.2lf ", *v++ );
		printf( "\n" );
	}
	printf("\n");
}
//-----------------------------------------------------------------------
void Complement( double** pTab0, double** pTabI, int nRow, int nCol, int nDim )
{
	for( int i=0; i<nDim; i++)
	{
		double* p = *pTab0;
		double* v = *pTabI++;
		if( i == nRow )
			continue;

		for( int j=0; j < nDim; j++, *v++)
		{
			if( j == nCol )
				continue;

			*p++ = *v;		
		}
		*pTab0++;
	}
}
//-----------------------------------------------------------------------
void ComplMatrix( double** pTab0, double** pTab, int nDim )
{
	double** pCompl = NULL;
	CreateMatrix( &pCompl, nDim-1 );

	double** p = pTab0;
	for( int nRow=0; nRow<nDim; nRow++)
	{
		double* v = *p++;
		int pot = ( (nRow)%2 ) ? -1 : 1;
		for( int nCol=0; nCol<nDim; nCol++)
		{	
			Complement( pCompl, pTab, nRow, nCol, nDim );
        	*v++ = pot * Det( pCompl, nDim-1 );
            pot = -pot;
		}
	}
#ifdef _DEBUG_
	printf( "Macierz dopelnien: \n" );
	PrintMatrix( pTab0, nDim);
#endif

	DeleteMatrix( &pCompl, nDim-1 );
}
//----------------------------------------------------------------------- 
void TransMatrix( double** pTab, int nDim)
{
	double **p = pTab;

	for( int nRow=0; nRow<nDim-1; nRow++ )
	{
		double *v = *p++ + nRow + 1;

		for( int nCol=nRow+1; nCol<nDim; nCol++, v++)
		{
			double x = *v;
			*v = pTab[nCol][nRow];
			pTab[nCol][nRow] = x;
		}
	}
#ifdef _DEBUG_
	printf( "Macierz transponowana: \n");
	PrintMatrix(pTab, nDim);
#endif
}
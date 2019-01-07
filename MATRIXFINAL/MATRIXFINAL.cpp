// Matrix 3.0.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

void ReadData(FILE*, double**, double*, int );
						//(plik wejœciowy, macierz uk³adów, wektor wyr. wolnych, rozmiar tablicy)
#define _DEBUG_

int main(int argc, char *argv[])
{
	if( argc != 2 ) //Gdy nie zgadza siê liczba parametrów
	{
		printf( "Usage: %s\\test.txt \n\n", argv[1] );
		return 1;
	}

	FILE* fin=NULL;
	if( ( fin= ( fopen( argv[1], "r" ) ) ) == NULL ) //otwieranie pliku
	{
		perror( "* File open error!\n\n" );
		return 0;
	}

	int nSize;
	fscanf(fin, "%d", &nSize); //wczytanie liczby wierzcho³ków

	cout << nSize;

	#ifdef _DEBUG_
	printf("Liczba niewiadomych: %d\n\n", nSize);
	#endif	

	double ** Matrix = NULL;	//macierz uk³adu
	if( ! (CreateMatrix(&Matrix, nSize) ) )	//Tworzenie macierzy
	{
		printf( "Error Creating Matrix!!" );
		return 0;
	}
	
	double * b = NULL;			//wektor wyrazów wolnych
	b = (double*)calloc(nSize, sizeof(double));

	ReadData(fin, Matrix, b, nSize); //wczytywanie danych
	
	fclose(fin);

	#ifdef _DEBUG_
	printf("Macierz wejsciowa: \n");
	PrintMatrix( Matrix, nSize);
	#endif

	double Determinant = Det(Matrix, nSize);	//Wyznacznik
	#ifdef _DEBUG_
	printf("Wyznacznik: %lf \n\n", Determinant);
	#endif

	if ( fabs(Determinant) < 1.0e-10 )
	{
		printf("Det=0, Macierz osobliwa!!\n\n");
		return 0;
	}

	double **pTab0 = NULL;	//macierz pomocnicza
	if( ! (CreateMatrix(&pTab0, nSize) ) )
	{
		printf( "Error Creating Matrix!!" );
		return 0;
	}
	InverseMatrix(pTab0, Matrix, nSize, Determinant); //odwracanie macierzy dla det != 0

#ifdef _DEBUG_
	printf( "Macierz odwrotna: \n");
	PrintMatrix(pTab0, nSize);
#endif

	double * pRes = NULL;		//wektor rozwi¹zañ
	pRes = (double*)calloc(nSize, sizeof(double));

	LayoutEqu(pTab0, b, pRes, nSize);	//rozwi¹zanie uk³adu równañ
//wyniki

	//wypisanie rozwi¹zañ
	for( int k=0; k<nSize; k++)
		printf( "Wspolczynnik %d: %.2lf\n", k+1, pRes[k]);

	//Zwalnianie pamiêci
	DeleteMatrix(&Matrix, nSize);
	DeleteMatrix(&pTab0, nSize);
	free(b);
	free(pRes);

	return 0;
}
//-----------------------------------------------------------------------
void ReadData(FILE* fin, double **pMatrix, double *b, int nSize )
{
	for( int i=0; i < nSize; i++)
	{
		double* p = *pMatrix++;
		for( int j=0; j < nSize; j++, p++)
			fscanf(fin, "%lf", p);
 
		fscanf(fin, "%lf", b++);
	}
}
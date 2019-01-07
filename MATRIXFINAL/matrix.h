#ifndef _MATRIX_INCLUDE_
#define _MATRIX_INCLUDE_

int CreateMatrix(double***, int);
int DeleteMatrix(double***, int); // zwalnia pami��
void InverseMatrix( double**, double**, int, double); //zwracaj�ca macierz (wyj�ciowa, wej�ciowa, rozmiar, wyznacznik)
double Det (double**, int); //obliczanie wyznacznika macierzy
void LayoutEqu( double**, double*, double*, int); //rozwi�zywanie uk�adu r�wna�; (odwrotna, wyr. wolne, Result);
void PrintMatrix( double **, int );

#endif
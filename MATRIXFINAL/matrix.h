#ifndef _MATRIX_INCLUDE_
#define _MATRIX_INCLUDE_

int CreateMatrix(double***, int);
int DeleteMatrix(double***, int); // zwalnia pamiêæ
void InverseMatrix( double**, double**, int, double); //zwracaj¹ca macierz (wyjœciowa, wejœciowa, rozmiar, wyznacznik)
double Det (double**, int); //obliczanie wyznacznika macierzy
void LayoutEqu( double**, double*, double*, int); //rozwi¹zywanie uk³adu równañ; (odwrotna, wyr. wolne, Result);
void PrintMatrix( double **, int );

#endif
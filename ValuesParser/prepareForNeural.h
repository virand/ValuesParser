#pragma once

/*
Функция преобразует массив типа [1,2,3,4,5,6,7,8,9,10,11,12,13,14] в файл вида

1,2,3,4
4,5,6,7
8,9,10,11
11,12,13,14

valuesarray - указатель на массив исходных значений
valuesarraylength - длина массива valuesarray

outputfilename - имя выходного файла
colsnum - количество столбцов в файле
*/

void prepareForNeural_simple(double * valuesarray, int valuesarraylength, char * outputfilename, int colsnum);


/*
Функция преобразует массив типа [1,2,3,4,5,6,7,8,9,10,11,12,13,14] в файл вида

1,2,3,4
2,3,4,5
3,4,5,6
4,5,6,7
.......

valuesarray - указатель на массив исходных значений
valuesarraylength - длина массива valuesarray

outputfilename - имя выходного файла
colsnum - количество столбцов в файле
*/

void prepareForNeural_sliding_window(double * valuesarray, int valuesarraylength, char * outputfilename, int colsnum);

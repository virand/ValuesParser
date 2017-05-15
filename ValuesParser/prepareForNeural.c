#include "stdafx.h"
#include "mathProcessing.h"

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

void prepareForNeural_simple(double * valuesarray, int valuesarraylength, char * outputfilename, int colsnum)
{
	FILE *fp;

	fp = fopen(outputfilename, "w+");

	for (int i = 0; i < valuesarraylength; i++)
	{
		if (i % colsnum == colsnum - 1)
			fprintf(fp, "%f,\n", valuesarray[i]);
		else
			fprintf(fp, "%f,", valuesarray[i]);
	}

	fclose(fp);
}


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

void prepareForNeural_sliding_window(double * valuesarray, int valuesarraylength, char * outputfilename, int colsnum)
{
	FILE *fp;

	//Убрать
	int class = 0;


	fp = fopen(outputfilename, "w+");

	for (int i = 1; i <= colsnum; i++)
	{
		if (i == colsnum)
			fprintf(fp, "<T%d>\n", i);
		else
			fprintf(fp, "<T%d>,", i);
	}

	for (int i = 0; i < valuesarraylength - colsnum; i++)
	{
		for (int k = 0; k < colsnum; k++)
		{
			if (k == colsnum - 1)
			{
				//Вернуть следующую строчку на место!!!! а остальные убрать
				//fprintf(fp, "%f,\n", valuesarray[i + k]);
				class = getClassNumber(valuesarray, valuesarraylength, i + k, 2, 0);
				fprintf(fp, "%f,\n", (double)class);
			}
			else
				fprintf(fp, "%f,", valuesarray[i + k]);
		}
	}

	fclose(fp);
}
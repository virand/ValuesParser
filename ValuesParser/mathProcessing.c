#include "stdafx.h"
#include <stdlib.h>	

static int cmp(const void *a, const void *b) {
	if ((*(double*)a - *(double*)b) < 0) return -1;
	else if ((*(double*)a - *(double*)b) > 0) return 1;
	else return 0;
}

/*
»значально процентное изменение котировок будет иметь гауссово распределение, так как большинство изменений размещено в районе нул€
»з-за этого нейронна€ сеть будет переобучена на околонулевых значени€х
ѕоэтому разобьем изменени€ котировок на несколько классов, состо€щих из одинакового количества элементов дл€ того, чтобы уравновесить изменени€
¬озвращает номер класса, которому принадлежит элемент c номером numofelement в массиве difvaluesarray
*/

int getClassNumber(double * valuesarray, int lengthvaluesarray, int numofelement, int numofclasses, char debuginfo)
{
	double * sortsplitarray = malloc(sizeof(double)*lengthvaluesarray);
	memcpy(sortsplitarray, valuesarray, sizeof(double)*lengthvaluesarray);

	qsort(sortsplitarray, lengthvaluesarray, sizeof(double), cmp);

	if (debuginfo) for (int i = 0; i < lengthvaluesarray; i++) { printf("sortsplitarray[%d] = %f\n", i, sortsplitarray[i]); }

	//classesLimits[numofclasses][2]
	double **classesLimits = malloc(numofclasses * sizeof(double*));

	for (int i = 0; i < numofclasses; i++)
	{
		classesLimits[i] = malloc(2 * sizeof(double));
	}

	/*
	Ќапример, у нас есть массив [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15]
	Ќам необходимо его разбить на 6 классов таким образом
	[ 1 2 | 3 4 | 5 6 | 7 8 | 9 10 | 11 12 13 14 15 ]

	ћассив classesLimits содержит границы классов
	classesLimits[6][2]
	[ 1 2 ]
	[ 3 4 ]
	[ 5 6 ]
	[ 7 8 ]
	[ 9 10 ]
	[ 11 15 ]
	*/

	int sizeofclass = lengthvaluesarray / numofclasses; //количество элементов в классе не счита€ последнего

	for (int i = 0; i < numofclasses; i++)
	{
		for (int k = 0; k < 2; k++)
		{
			// Ћева€ граница класса
			if (k == 0)
			{
				classesLimits[i][k] = sortsplitarray[i*sizeofclass];
				if (debuginfo) printf("Class No %d [ %f ", i, classesLimits[i][k]);
			}
			// ѕрава€ граница класса
			if (k == 1)
			{
				//≈сли класс не последний, то права€ граница получаетс€ путем довалени€ количества элементов в классе -1
				if (i != numofclasses - 1)
				{
					classesLimits[i][k] = sortsplitarray[i*sizeofclass + sizeofclass - 1];

				}
				//≈сли класс последний, то права€ граница - последний элемент массива
				else
				{
					classesLimits[i][k] = sortsplitarray[lengthvaluesarray - 1];
				}

				if (debuginfo) printf("%f ]\n", classesLimits[i][k]);
			}
		}
	}

	//ќпредел€ем класс которому принадлежит элемент
	for (int i = 0; i < numofclasses; i++)
	{
		if ((classesLimits[i][0] <= valuesarray[numofelement]) && (valuesarray[numofelement] <= classesLimits[i][1]))
		{
			return i;
			break;
		}
	}

	return -1;

	free(sortsplitarray);
}
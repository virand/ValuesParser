#include "stdafx.h"
#include <string.h>
#include <stdlib.h>	

// Get field from line
const char* getField(char* line, int num)
{
	const char* tok;

	// strtok(line, ";") ��������� ������ s1 �� ������� � ������������ ";".
	// ����� strtok ���� � ������ ������ ����������� � �������� ��� �� \0
	// ��� ���������� ��������� �� ������, ���������� ������ �������
	// ���� ������� ������ �� �������, �� ������������ NULL
	// ��� ��������� ��������� ���������� ���������� �������� strtok(NULL, ";\n")
	// ���� �������� NULL, �� ������ ������ �� �������

	for (tok = strtok(line, ","); tok && *tok; tok = strtok(NULL, ",\n"))
	{
		if (!--num)
			return tok;
	}

	return NULL;
}

int countRowsInFile(char * filename)
{
	int linenumbers = 1;
	int c;

	FILE *fp = fopen(filename, "r");

	while (c = fgetc(fp))
	{
		if (c == EOF) break;

		if (c == 10) linenumbers++; //ASCII ��� new line = 10
	}

	fclose(fp);
	return linenumbers;
}

/*
Read certain column [columnNumber] from file [fileName] to outputArray
*/
double * readColumnFromFile(char * fileName, int numberOfLinesInFile, int columnNumber)
{
	FILE *fp;			//��������� �� ����

	if ((fp = fopen(fileName, "r")) == NULL)
	{
		printf("Can't open %s\n", fileName);
		getchar();
		exit(1);
	}

	double * outputArray = malloc(sizeof(double)*numberOfLinesInFile);
	char line[1024];

	int k = 0;

	while (fgets(line, 1024, fp))
	{
		char * tmp = malloc(strlen(line) + 1);
		strcpy(tmp, line);
		outputArray[k] = atof(getField(tmp, columnNumber));
		k++;
		free(tmp);
	}

	return outputArray;
	fclose(fp);
}
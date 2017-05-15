// ValuesParser.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>		// Прототип ANSI C функции exit()
#include <string.h>
#include "parsingFiles.h"
#include "prepareForNeural.h"
#include "mathProcessing.h"


// [inputFileName] [colNumberInFile] [outputFileName] [numberOfColumnsInOutputFile] [numberOfClasses]
int prepareFilesForNeuralNetwork(char * inputFileName, int colNumberInFile, char * outputFileName, int numberOfColumnsInOutputFile, int numberOfClasses)
{

	char postfix_simple[] = "_simple";
	char postfix_sliding_window[] = "_sliding_window";
	char postfix_classes[] = "_classes";

	char tmp_outputFileName[64]="";

	int numberOfLinesInInputFile = countRowsInFile(inputFileName);
	int lengthOfColumnFromInputFileArray = numberOfLinesInInputFile;
	int lengthOfDifColumnFromInputFileArray = numberOfLinesInInputFile - 1;

	double * columnFromInputFileArray = malloc(sizeof(double)*numberOfLinesInInputFile);
	columnFromInputFileArray = readColumnFromFile(inputFileName, numberOfLinesInInputFile, colNumberInFile);

	double * difColumnFromInputFileArray;
	difColumnFromInputFileArray = malloc(sizeof(double)*(lengthOfDifColumnFromInputFileArray));

	for (int i = 1; i < numberOfLinesInInputFile; i++)
	{
		difColumnFromInputFileArray[i - 1] = ((columnFromInputFileArray[i] - columnFromInputFileArray[i - 1]) / columnFromInputFileArray[i - 1]) * 100;
	}

	// Generate name: [outputFileName]_simple
	strcpy(tmp_outputFileName, outputFileName); strcat(tmp_outputFileName, postfix_simple);

	prepareForNeural_simple(difColumnFromInputFileArray, lengthOfDifColumnFromInputFileArray, tmp_outputFileName, numberOfColumnsInOutputFile);

	// Generate name: [outputFileName]_sliding_window
	strcpy(tmp_outputFileName, outputFileName); strcat(tmp_outputFileName, postfix_sliding_window);

	prepareForNeural_sliding_window(difColumnFromInputFileArray, lengthOfDifColumnFromInputFileArray, tmp_outputFileName, numberOfColumnsInOutputFile);

	double * difClassesColumnFromInputFileArray = malloc(sizeof(double)*lengthOfDifColumnFromInputFileArray);

	for (int i = 0; i < lengthOfDifColumnFromInputFileArray; i++)
	{
		if (i == 0)
			difClassesColumnFromInputFileArray[i] = getClassNumber(difColumnFromInputFileArray, lengthOfDifColumnFromInputFileArray, i, numberOfClasses, 1);
		else
			difClassesColumnFromInputFileArray[i] = getClassNumber(difColumnFromInputFileArray, lengthOfDifColumnFromInputFileArray, i, numberOfClasses, 0);
	}
	
	// Generate name: [outputFileName]_sliding_window_classes
	strcpy(tmp_outputFileName, outputFileName); strcat(tmp_outputFileName, postfix_sliding_window); strcat(tmp_outputFileName, postfix_classes);

	prepareForNeural_sliding_window(difClassesColumnFromInputFileArray, lengthOfDifColumnFromInputFileArray, tmp_outputFileName, numberOfColumnsInOutputFile);

	return 0;
}


// [desiredValuesFile] [colNumberInDesiredValuesFile] [predictedValuesFile] [colNumberInPredictedValuesFile] [numOfLastCheckedValues] [appropriateClasses] [debugInfo]
int checkTheAccuracyOfNeuralNetwork(char * desiredValuesFile, int colNumberInDesiredValuesFile, char * predictedValuesFile, int colNumberInPredictedValuesFile, int numOfLastCheckedValues, int appropriateClasses, int debugInfo)
{
	int numberOfRowsInDesiredValuesFile = countRowsInFile(desiredValuesFile);
	int numberOfRowsInPredictedValuesFile = countRowsInFile(predictedValuesFile);

	int lengthOfColumnFromDesiredValuesFileArray = numberOfRowsInDesiredValuesFile;
	int lengthOfColumnFromPredictedValuesFileArray = numberOfRowsInPredictedValuesFile;

	numberOfRowsInDesiredValuesFile = countRowsInFile(desiredValuesFile);
	numberOfRowsInPredictedValuesFile = countRowsInFile(predictedValuesFile);

	double * columnFromDesiredValuesFile = malloc(sizeof(double)*numberOfRowsInDesiredValuesFile);
	double * columnFromPredictedValuesFile = malloc(sizeof(double)*numberOfRowsInPredictedValuesFile);

	columnFromDesiredValuesFile = readColumnFromFile(desiredValuesFile, numberOfRowsInDesiredValuesFile, colNumberInDesiredValuesFile);
	columnFromPredictedValuesFile = readColumnFromFile(predictedValuesFile, numberOfRowsInPredictedValuesFile, colNumberInPredictedValuesFile);

	double * desiredValuesArray = malloc(sizeof(double)*numOfLastCheckedValues);
	double * predictedValuesArray = malloc(sizeof(double)*numOfLastCheckedValues);

	/*
	For example we have:
		columnFromDesiredValuesFile = [ 0, 1, 2, 3, 4, 5, 6 ], by using this file we'll get
		desiredValuesArray = [ 4, 5, 6 ]
	
	*/

	for (int i = 0; i < numOfLastCheckedValues; i++)
	{
		desiredValuesArray[i] = columnFromDesiredValuesFile[lengthOfColumnFromDesiredValuesFileArray - numOfLastCheckedValues + i];
		predictedValuesArray[i] = columnFromPredictedValuesFile[lengthOfColumnFromPredictedValuesFileArray - numOfLastCheckedValues + i];
	}

	if (debugInfo)
	{
		printf("lengthOfColumnFromDesiredValuesFileArray = %i\n", lengthOfColumnFromDesiredValuesFileArray);
		printf("lengthOfColumnFromPredictedValuesFileArray = %i\n", lengthOfColumnFromPredictedValuesFileArray);

		printf("numOfLastCheckedValues = %i\n", numOfLastCheckedValues);
		printf("appropriateClasses = %i\n", appropriateClasses);

		if (lengthOfColumnFromDesiredValuesFileArray == lengthOfColumnFromPredictedValuesFileArray)
		{
			printf("[DESIREDVALUES	|	PREDICTED]\n");
			for (int i=0; i<numOfLastCheckedValues; i++)
				printf("[%f | %f]\n",desiredValuesArray[i], predictedValuesArray[i]);
		}
		else
		{
			printf("lengthOfColumnFromDesiredValuesFileArray != lengthOfColumnFromPredictedValuesFileArray");
		}
	}

	int right = 0;
	int sum = 0;
	if (debugInfo)
	{
		printf("-----------------------------------------------------------\n");
		printf("[DESIREDVALUES	|	PREDICTED]\n");
	}
		
	for (int i = 0; i < numOfLastCheckedValues; i++)
	{
		if (predictedValuesArray[i] < 0.7)
			predictedValuesArray[i] = 0;
		else
			predictedValuesArray[i] = 1;
	}

	for (int i = 0; i < numOfLastCheckedValues; i++)
	{
		if (predictedValuesArray[i] >= appropriateClasses)
		{
			sum++;
			if (desiredValuesArray[i] >= appropriateClasses)
			{
				printf("[%f | %f] RIGHT\n", desiredValuesArray[i], predictedValuesArray[i]);
				right++;
			}
			else
			{
				printf("[%f | %f] FALSE\n", desiredValuesArray[i], predictedValuesArray[i]);
			}
		}
	}

	double result = (double)right / (double)sum;

	printf("Effective of neural predictions: %f", result);

	free(columnFromDesiredValuesFile);
	free(columnFromPredictedValuesFile);

	free(desiredValuesArray);
	free(predictedValuesArray);

	return 0;
}


int main(int argc, char *argv[])
{
	/*
	For get ready file for NeuralNetwork use:
		./ValuesParser [1] [inputFileName] [colNumberInFile] [outputFileName] [numberOfColumnsInOutputFile] [numberOfClasses]
	then program will read column with number [colNumberInFile] then it'll prepare data and write it to [outputFileName]

		1 input.txt 5 output 10 2

	For determining quality of NetworkResults use:
		./ValuesParser [2] [desiredValuesFile] [colNumberInDesiredValuesFile] [predictedValuesFile] [colNumberInPredictedValuesFile] [numOfLastCheckedValues] [appropriateClasses] [debugInfo]

		2 output_sliding_window_classes 10 output.csv 1 500 1 1

	*/

	int type = atoi(argv[1]);

	switch (type)
	{
		case 1:
		{
			char * inputFileName = argv[2];
			int colNumberInFile = atoi(argv[3]);
			char * outputFileName = argv[4];
			int numberOfColumnsInOutputFile = atoi(argv[5]);
			int numberOfClasses = atoi(argv[6]);

			prepareFilesForNeuralNetwork(inputFileName, colNumberInFile, outputFileName, numberOfColumnsInOutputFile, numberOfClasses);
			break;
		}
		
		case 2:
		{
			// [desiredValuesFile] [colNumberInDesiredValuesFile] [predictedValuesFile] [colNumberInPredictedValuesFile] [numOfLastCheckedValues] [appropriateClasses] [debugInfo]
			char * desiredValuesFile = argv[2];
			int colNumberInDesiredValuesFile = atoi(argv[3]);
			char * predictedValuesFile = argv[4];
			int colNumberInPredictedValuesFile = atoi(argv[5]);

			int numOfLastCheckedValues = atoi(argv[6]);
			int appropriateClasses = atoi(argv[7]);
			int debugInfo = atoi(argv[8]);

			checkTheAccuracyOfNeuralNetwork(desiredValuesFile, colNumberInDesiredValuesFile, predictedValuesFile, colNumberInPredictedValuesFile, numOfLastCheckedValues, appropriateClasses, debugInfo);
			break;
		}
			
		default:
			printf("Don't correct use of program\n");
			break;
	}

	getchar();
	

    return 0;
}
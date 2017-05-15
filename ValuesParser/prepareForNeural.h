#pragma once

/*
������� ����������� ������ ���� [1,2,3,4,5,6,7,8,9,10,11,12,13,14] � ���� ����

1,2,3,4
4,5,6,7
8,9,10,11
11,12,13,14

valuesarray - ��������� �� ������ �������� ��������
valuesarraylength - ����� ������� valuesarray

outputfilename - ��� ��������� �����
colsnum - ���������� �������� � �����
*/

void prepareForNeural_simple(double * valuesarray, int valuesarraylength, char * outputfilename, int colsnum);


/*
������� ����������� ������ ���� [1,2,3,4,5,6,7,8,9,10,11,12,13,14] � ���� ����

1,2,3,4
2,3,4,5
3,4,5,6
4,5,6,7
.......

valuesarray - ��������� �� ������ �������� ��������
valuesarraylength - ����� ������� valuesarray

outputfilename - ��� ��������� �����
colsnum - ���������� �������� � �����
*/

void prepareForNeural_sliding_window(double * valuesarray, int valuesarraylength, char * outputfilename, int colsnum);

#pragma once

static int cmp(const void *a, const void *b);

/*
���������� ���������� ��������� ��������� ����� ����� �������� �������������, ��� ��� ����������� ��������� ��������� � ������ ����
��-�� ����� ��������� ���� ����� ����������� �� ������������ ���������
������� �������� ��������� ��������� �� ��������� �������, ��������� �� ����������� ���������� ��������� ��� ����, ����� ������������ ���������
���������� ����� ������, �������� ����������� ������� c ������� numofelement � ������� difvaluesarray
*/

int getClassNumber(double * valuesarray, int lengthvaluesarray, int numofelement, int numofclasses, char debuginfo);
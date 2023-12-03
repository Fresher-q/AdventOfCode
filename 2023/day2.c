#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int power =  0;

int subsetExtr(char* set, char* subset, int size, int itr) {
	int j = 1;
	char* prevEnd = set;
	for (int i = 0; i < size; i++) {
		if ((set[i] == ';')) {
			if (j == itr) {
				set[i + 1] = '\0';
				strcpy(subset, prevEnd);
				set[i + 1] = " ";
				j = -1;
				break;
			}
			else
				prevEnd = &set[i+2];
			j++;
		}
	}
	if ((j != -1) && (prevEnd[0] >= '0' && prevEnd[0] <= '9')) {
		strcpy(subset, prevEnd);
	}
	
	if (j != -1)
		return 0;
	else
		return 1;
}

void part2(char* fullSet, int* rgbMax, int size) {
	char subset[50];
	char rgbText[3][6] = { "red", "green", "blue" };
	char* rgbValuePtr;
	char rgbValueArr[3];
	int maxRgb[3] = { 0, 0, 0 };
	for (int i = 1; i > 0; i++) {
		if (!subsetExtr(fullSet, subset, size, i))
			i = -100;
		for (int j = 0; j < 3; j++) {
			rgbValuePtr = strstr(subset, *(rgbText + j));
			if (rgbValuePtr != NULL) {
				if (&subset[3] == rgbValuePtr) {
					rgbValueArr[0] = subset[0];
					rgbValueArr[1] = subset[1];
					rgbValueArr[2] = '\0';
				}
				else if (&subset[2] == rgbValuePtr) {
					rgbValueArr[0] = subset[0];
					rgbValueArr[1] = '\0';
				}
				else if (isdigit(*(rgbValuePtr - 3))) {
					rgbValueArr[0] = *(rgbValuePtr - 3);
					rgbValueArr[1] = *(rgbValuePtr - 2);
					rgbValueArr[2] = '\0';
				}
				else {
					rgbValueArr[0] = *(rgbValuePtr - 2);
					rgbValueArr[1] = '\0';
				}
				if (maxRgb[j] < atoi(rgbValueArr)) {
					maxRgb[j] = atoi(rgbValueArr);
				}
			}
		}
	}
	power += (maxRgb[0] * maxRgb[1] * maxRgb[2]);
}

int part1(char* line, int* rgbMax, int size) {
	char fullSet[250];
	char subset[50];
	char rgbText[3][6] = { "red", "green", "blue" };
	char* rgbValuePtr;
	char rgbValueArr[3];
	int* actualRgb[3] = { 0, 0, 0 };
	if (line[8] == '*') {
		strcpy(fullSet, line + 9);
	}
	else {
		strcpy(fullSet, line + 8);
	}
	part2(fullSet, rgbMax, size);
	for (int i = 1; i > 0; i++) {
		if (!subsetExtr(fullSet, subset, size, i))
			i = -100;
		for (int j = 0; j < 3; j++) {
			rgbValuePtr = strstr(subset, *(rgbText+j));
			if (rgbValuePtr != NULL) {
				if (&subset[3] == rgbValuePtr) {
					rgbValueArr[0] = subset[0];
					rgbValueArr[1] = subset[1];
					rgbValueArr[2] = '\0';
				}
				else if (&subset[2] == rgbValuePtr) {
					rgbValueArr[0] = subset[0];
					rgbValueArr[1] = '\0';
				}
				else if (isdigit(*(rgbValuePtr - 3))) {
					rgbValueArr[0] = *(rgbValuePtr - 3);
					rgbValueArr[1] = *(rgbValuePtr - 2);
					rgbValueArr[2] = '\0';
				}
				else {
					rgbValueArr[0] = *(rgbValuePtr - 2);
					rgbValueArr[1] = '\0';
				}
				actualRgb[j] = atoi(rgbValueArr);
				if (actualRgb[j] > rgbMax[j]) {
					return 0;
				}
			}		
		}
	}
	return 1;
}

int main() {
	FILE* pF = fopen("games.txt", "r");
	if (pF == NULL) {
		printf("could not open the file");
		return -1;
	}
	int rgbMax[3] = { 12, 13, 14 };
	char buffer[250];
	int sum = 0;
	for (int i = 1; fgets(buffer, 250, pF) != NULL; i++) {
		if (i >= 10)
			*(buffer + 8) = '*';
		else
			*(buffer + 7) = '*';
		if (part1(buffer, rgbMax, strlen(buffer))) 
			sum += i;	
	}
	printf("\npart 1 = %d\n", sum);
	printf("part 2 = %d\n", power);
	return 0;
}

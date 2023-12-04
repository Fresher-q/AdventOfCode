#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int part1Sum = 0;
unsigned long long part2Sum = 0;

char* newArr(char* buffer, int size) {
	size += 1;
	char* arr = (char*)malloc(size+1);
	if (arr == NULL) {
		printf("mallock newArray failure");
		abort();
	}
	arr[0] = '.';
	arr[142] = '\0';
	strcpy(arr+1, buffer);
	arr[size - 1] = '.';
	return arr;
}

char* emptyLine() {
	char* arr = (char*)malloc(143);
	if (arr == NULL) {
		printf("mallock newArray failure");
		abort();
	}
	arr[142] = '\0';
	for (int i = 0; arr[i] != 0; i++) {
		arr[i] = '.';
	}
	return arr;
}

void neighborCheck(char* line1, char* line2, char* line3, int numSize, int i) {	
	int neighborsSize = numSize + 2;
	char* numChar = NULL;
	for (int j = 0; j < neighborsSize; j++) {
		if ((line1[i - j] != '.') || (line3[i - j] != '.')) {
			numChar = (char*)malloc((numSize * sizeof(char)) + 1);
			if (numChar == NULL) {
				printf("mallock numChar failure");
				abort();
			}
			numChar[numSize] = '\0';
			for (int j = 0; numChar[j] != '\0'; j++) {
				numChar[(numSize - 1) - j] = line2[(i - 1) - j];
			}
			part1Sum += atoi(numChar);
			free(numChar);
			return;
		}
	}
}

void part1(char* line1, char* line2, char* line3, int size) {
	char* numChar = NULL;
	int neighborsSize = 0;
	int numSize = 0; 
	for (int i = 0; i < size; i++) {
		if (isdigit(line2[i])) {
			numSize++;
		}
		else if (numSize > 0) {
			if (line2[i] != '.' || line2[i - numSize - 1] != '.') {
				numChar = (char*)malloc((numSize * sizeof(char)) + 1);
				if (numChar == NULL)
					abort();
				numChar[numSize] = '\0';
				for (int j = 0; numChar[j] != '\0'; j++) {
					numChar[(numSize - 1) - j] = line2[(i - 1) - j];
				}
				part1Sum += atoi(numChar);
				free(numChar);
				numSize = 0;
				continue;
			}
			neighborCheck(line1, line2, line3, numSize, i);
			numSize = 0;
		}
	}
}
int terminate = 0;
int getNum(char* arr, int dim) {
	int left = 0;
	int right = 0;
	char numChar[4];
	while (1) {
		if (!isdigit(arr[1 + right])) {
			break;
		}
		right++;
	}
	while (1) {
		if (!isdigit(arr[(-1) + left])) {
			break;
		}
		left--;
	}
	if ((right > 0) && (dim == 0 || dim == 2)) {
		terminate = 1;
	}
	int itr = 0;
	int length = 1 + right + (-left);
	switch (length) {
	case 3: numChar[3] = '\0'; break;
	case 2: numChar[2] = '\0'; break;
	case 1: numChar[1] = '\0'; break;
	}
	for (int i = 0; i < -left; i++) {
		numChar[i] = arr[(left) + i];
		itr++;
	}
	for (int i = itr; numChar[i] != '\0'; i++) {
		numChar[i] = arr[(left) + i];
	}
	return atoi(numChar);
}

void part2(char* line1, char* line2, char* line3, int size) {
	char* numChar = NULL;
	int neighborsSize = 0;
	int numSize = 0;
	int nums[4] = { 1, 1, 1, 1 };
	int multiply = 1;
	int limit = 0;
	for (int i = 0; i < size; i++) {
		if (line2[i]=='*') {
			if (isdigit(line2[i - 1]) && isdigit(line2[i + 1]) && limit<1) {
				multiply *= getNum(&line2[i - 1], 1);
				multiply *= getNum(&line2[i + 1], 1);
				limit = 2;
				terminate = 0;
			}
			if (isdigit(line2[i - 1]) && limit < 2) {
				nums[2] = getNum(&line2[i - 1], 1);
				if (nums[2] > 1) {
					multiply *= nums[2];
					nums[2] = 1;
					limit++;
				}
			}
			if (isdigit(line2[i + 1]) && limit < 2) {
				nums[3] = getNum(&line2[i + 1], 1);
				if (nums[3] > 1) {
					multiply *= nums[3];
					nums[3] = 1;
					limit++;
				}
			}
			for (int j = 0; j < 3; j++) {
				if (isdigit(line1[(i - 1) + j]) && limit < 2) {
					nums[0] *= getNum(&line1[(i - 1) + j], 0);
					if (terminate == 1) {
						limit++;
						multiply *= nums[0];
						nums[0] = 1;
						terminate = 0;
						break;
					}
					else if (nums[0] > 1) {
						multiply *= nums[0];
						nums[0] = 1;
						limit++;
					}
				}
			}
			for (int j = 0; j < 3; j++) {
				if (isdigit(line3[(i - 1) + j]) && limit < 2) {
					nums[1] *= getNum(&line3[(i - 1) + j], 2);
					if (terminate == 1) {
						limit++;
						multiply *= nums[1];
						nums[1] = 1;
						terminate = 0;
						break;
					}
					else if (nums[1] > 1) {
						multiply *= nums[1];
						nums[1] = 1;
						limit++;
					}
				}
			}
			if (limit == 2) {
				part2Sum += multiply;
			}	
			limit = 0;
			multiply = 1;
		}
	}
}

int main() {
	FILE* pF = fopen("schematic.txt", "r");
	char buffer[150];
	char* line1 = emptyLine();
	fgets(buffer, 150, pF);
	char* line2 = newArr (buffer, strlen(buffer));
	fgets(buffer, 150, pF);
	char* line3 = newArr (buffer, strlen(buffer));
	part1(line1, line2, line3, strlen(line2));
	for (int i = 2; fgets(buffer, 150, pF) != NULL; i++) {
		free(line1);
		line1 = line2;
		line2 = line3;
		line3 = newArr(buffer, strlen(buffer));
		part1(line1, line2, line3, strlen(line2));
		part2(line1, line2, line3, strlen(line2));
	}
	line1 = line2;
	line2 = line3;
	line3 = emptyLine();
	part1(line1, line2, line3, strlen(line2));
	printf("Part 1 = %d\n", part1Sum);
	printf("Part 2 = %llu\n", part2Sum);
	return 0;
}

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void reverse(char* arr, int size) {
	char temp;
	for (int i = 0, j = size - 1; i < j; i++, j--) {
		temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
	}
}

int part1(char* ptr, int size) {
	char num[3] = { 'N', 'N', '\0' };
	for (int i = 0; i < size; i++) {
		if ((num[0] == 'N') && (ptr[i] >= '0') && (ptr[i] <= '9')) {
			num[0] = ptr[i];
		}
		if ((ptr[i] >= '0') && (ptr[i] <= '9')) {
			num[1] = ptr[i];
		}
	}
	return atoi(num);
}

int part2(char* ptr, int size) {
	char single_digits[10][6] = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
	char rev_single_digits[10][6] = { "orez", "eno", "owt", "eerht", "ruof", "evif", "xis", "neves", "thgie", "enin" };
	char num[3] = { 'N', 'N', '\0' };
	char* first = NULL;
	char* tempFirst = NULL;
	int firstNumeric;
	for (int i = 0; ptr[i] != '\0'; i++) {
		if ((ptr[i] >= '0') && (ptr[i] <= '9')) {
			tempFirst = ptr + i;
			break;
		}
	}
	int numericMin;
	char* ptrMin = (ptr + (size - 1));
	for (int i = 0; i < 10; i++) {
		first = strstr(ptr, *(single_digits + i));
		if (first != NULL) {
			if (ptrMin > first) {
				ptrMin = first;
				numericMin = i;
			}					
		}
	}
	first = ptrMin;
	if ((first == NULL) || (first >= tempFirst)) {
		first = tempFirst;
		num[0] = *first;
	}
	else {
		num[0] = numericMin + '0';
	}
	reverse(ptr, size);
	for (int i = 0; ptr[i] != '\0'; i++) {
		if ((ptr[i] >= '0') && (ptr[i] <= '9')) {
			tempFirst = ptr + i;
			break;
		}
	}
	ptrMin = (ptr + (size - 1));
	for (int i = 0; i < 10; i++) {
		first = strstr(ptr, *(rev_single_digits + i));
		if (first != NULL) {
			if (ptrMin > first) {
				ptrMin = first;
				numericMin = i;
			}
		}
	}
	first = ptrMin;
	if ((first == NULL) || (first >= tempFirst)) {
		first = tempFirst;
		num[1] = *first;
	}
	else {
		num[1] = numericMin + '0';
	}
	return atoi(num);
}

int main() {
	FILE* pF = fopen("calibrationDoc.txt", "r");
	char buffer[100];
	if (pF == NULL) {
		printf("could not read the file");
		return -1;
	}
	int sum1 = 0;
	int sum2 = 0;
	while (fgets(buffer, 100, pF) != NULL) {
		sum1 += part1(buffer, strlen(buffer));
		sum2 += part2(buffer, strlen(buffer));
	}
	printf("part 1 : %d", sum1);
	printf("\n\npart 2 : %d\n\n", sum2);
	fclose(pF);
	return 0;
}

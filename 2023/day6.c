#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define EXAMPLE 0
#if EXAMPLE == 1
#define FILENAME "example.txt"
#define RACES_NUMBER 3
#define NUMS_LENGTH 6
#else
#define FILENAME "input.txt"
#define RACES_NUMBER 4
#define NUMS_LENGTH 15
#endif

void getFileData(int (*eachRace)[2]) {
	FILE* pF = fopen(FILENAME, "r");
	if (pF == NULL) {
		printf("fopen failure");
		return -1;
	}
	char buffer[50];
	for (int i = 0; fgets(buffer, 50, pF); i++) {
		char* nums = strtok(buffer, ":");
		nums = strtok(NULL, " ");
		for (int j = 0; nums != NULL; j++) {
			eachRace[j][i] = atoi(nums);
			nums = strtok(NULL, " ");
		}
	}
}

void getFileDataKerning(long long* oneBigRace) {
	FILE* pF = fopen(FILENAME, "r");
	if (pF == NULL) {
		printf("fopen failure");
		return -1;
	}
	char buffer[50];
	
	for (int i = 0; fgets(buffer, 50, pF)!=NULL; i++) {
		char* num = strtok(buffer, ":");
		int count = 0;
		num = strtok(NULL, "");
		for (int i = 0; num[i] != '\0'; i++) {
			if (num[i] != ' ')
				num[count++] = num[i];
		}
		num[count] = '\0';
		oneBigRace[i] = atoll(num);
	}
}


int part1(int(*eachRace)[2]) {
	int speed;
	int remainingTime;
	int waysCount = 0;
	int ret = 1;
	for (int i = 0; i < RACES_NUMBER; i++) {
		for (int j = 0; j < eachRace[i][0]; j++) {
			speed = j;
			remainingTime = eachRace[i][0] - j;
			if (speed * remainingTime > eachRace[i][1])
				waysCount++;
		}
		ret *= waysCount;
		waysCount = 0;
	}
	return ret;
}

int part2(long long* race) {
	long long speed;
	long long remainingTime;
	long long waysCount = 0;
	long long ret = 1;
	for (int j = 0; j < race[0]; j++) {
		speed = j;
		remainingTime = race[0] - j;
		if (speed * remainingTime > race[1])
			waysCount++;
	}
	ret *= waysCount;
	return ret;
}

int main() {
	int eachRace[RACES_NUMBER][2]; //arr[raceIndex][time, record_distance]
	long long oneBigRace[2];
	getFileData(eachRace);
	getFileDataKerning(oneBigRace);
	printf("Part 1 : %d\n", part1(eachRace));
	printf("Part 2 : %d\n", part2(oneBigRace));
	return 0;
}

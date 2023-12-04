#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define FILELINES 220

int getNums(int* nums, char* card) {
    int numsCount = 0;
    char* numTemp = strtok(card, " ");
    while (numTemp != NULL) {
        nums[numsCount] = atoi(numTemp);
        numTemp = strtok(NULL, " ");
        numsCount++;
    }
    return numsCount;
}

int main() {
    FILE* file = fopen("cards.txt", "r");
    if (file == NULL) {
        printf("fopen failed");
        return -1;
    }
    char line[FILELINES];
    int totalCards[FILELINES] = { 0 };
    int part1Sum = 0;
    for (int i = 0; fgets(line, FILELINES, file) != NULL; i++) {
        totalCards[i] += 1;
        char* firstHalf = strtok(line, "|");
        char* secondHalf = strtok(NULL, "|");
        char* card = strtok(firstHalf, ":");
        card = strtok(NULL, ":");

        int cardNums[FILELINES];
        int cardCount = getNums(cardNums, card);
        int winNums[FILELINES];
        int winCount = getNums(winNums, secondHalf);

        int val = 0;
        for (int j = 0; j < cardCount; j++) {
            for (int k = 0; k < winCount; k++) {
                if (cardNums[j] == winNums[k]) {
                    val++;
                    break;
                }
            }
        }
        if (val > 0) {
            part1Sum += 1 << (val - 1);
        }
        for (int j = 0; j < val; j++) {
            totalCards[i + 1 + j] += totalCards[i];
        }
    }
    fclose(file);

    int part2Sum = 0;
    for (int i = 0; i < FILELINES; i++) {
        part2Sum += totalCards[i];
    }
    printf("Part 1 = %d\n", part1Sum);
    printf("Part 2 = %d\n", part2Sum);
    return 0;
}

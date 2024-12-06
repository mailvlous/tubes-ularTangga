#ifndef saveFile_c
#define saveFile_c

#include <stdio.h>
#include "types.h"

void save(int playerCount, int mode, int currentTurn, Ladder L[], int ladderCount, Snake S[], int snakeCount, Player playerArray[], int winnerCount, int difficulty, char colors[][7], int grid, int colorCount) {
    FILE *file = fopen("saveFile.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    fprintf(file, "playerCount %d\n", playerCount);
    fprintf(file, "mode %d\n", mode);
    fprintf(file, "currentTurn %d\n", currentTurn);
    fprintf(file, "ladderCount %d\n", ladderCount);
    fprintf(file, "snakeCount %d\n", snakeCount);
    fprintf(file, "winnerCount %d\n", winnerCount);
    fprintf(file, "difficulty %d\n", difficulty);
    fprintf(file, "grid %d\n", grid);

    fprintf(file, "LADDERBEGIN\n");
    for (int i = 0; i < ladderCount; i++) {
        fprintf(file, "%d %d\n", L[i][0], L[i][1]);
    }
    fprintf(file, "LADDEREND\n");

    fprintf(file, "SNAKEBEGIN\n");
    for (int i = 0; i < snakeCount; i++) {
        fprintf(file, "%d %d\n", S[i][0], S[i][1]);
    }
    fprintf(file, "SNAKEEND\n");

    fprintf(file, "PLAYERBEGIN\n");
    for (int i = 0; i < playerCount; i++) {
        fprintf(file, "%s %d %d %d %d %d %d\n", playerArray[i].name, playerArray[i].position, playerArray[i].score, playerArray[i].isPlaying, playerArray[i].isComputer, playerArray[i].isWin, playerArray[i].rankPlayer);
    }
    fprintf(file, "PLAYEREND\n");

    fclose(file);
}

void load() {
    
}

#endif
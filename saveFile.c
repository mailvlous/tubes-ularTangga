#ifndef saveFile_c
#define saveFile_c

#include <stdio.h>
#include <stdbool.h>
#include "types.h"
#include "main.c"

void game(int playerCount, int mode, int currentTurn, Ladder L[], int ladderCount, Snake S[], int snakeCount, Player playerArray[], int *winnerCount, int difficulty, char colors[][7], int grid, int colorCount);

void save(int playerCount, int mode, int currentTurn, Ladder L[], int ladderCount, Snake S[], int snakeCount, Player playerArray[], int winnerCount, int difficulty, int grid, int colorCount) {
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
    fprintf(file, "colorCount %d\n", colorCount);
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

bool emptyCheck() {
    FILE *file = fopen("saveFile.txt", "r");
    if (file == NULL) {
        printf("File not found or cannot be opened.\n");
        return -1;
    }

    int c = fgetc(file);
    if (c == EOF) {
        printf("The file is empty.\n");
        fclose(file);
        return true;
    } else {
        printf("The file is not empty.\n");
        ungetc(c, file);
        fclose(file);
        return false;
    }

    
}

void load() {
    if (!emptyCheck()) {
        FILE *file = fopen("saveFile.txt", "r");
        if (file == NULL) {
            perror("Error opening file");
            return;
        }
        int playerCount, mode, currentTurn, ladderCount, snakeCount, winnerCount, difficulty, colorCount, grid;
        fscanf(file, "playerCount %d\n", &playerCount);
        fscanf(file, "mode %d\n", &mode);
        fscanf(file, "currentTurn %d\n", &currentTurn);
        fscanf(file, "ladderCount %d\n", &ladderCount);
        fscanf(file, "snakeCount %d\n", &snakeCount);
        fscanf(file, "winnerCount %d\n", &winnerCount);
        fscanf(file, "difficulty %d\n", &difficulty);
        fscanf(file, "colorCount %d\n", &colorCount);
        fscanf(file, "grid %d\n", &grid);
        Ladder L[ladderCount];
        fscanf(file, "LADDERBEGIN\n");
        for (int i = 0; i < ladderCount; i++) {
            fscanf(file, "%d %d\n", &L[i][0], &L[i][1]);
        }
        fscanf(file, "LADDEREND\n");
        Snake S[snakeCount];
        fscanf(file, "SNAKEBEGIN\n");
        for (int i = 0; i < snakeCount; i++) {
            fscanf(file, "%d %d\n", &S[i][0], &S[i][1]);
        }
        fscanf(file, "SNAKEEND\n");
        Player playerArray[playerCount];
        fscanf(file, "PLAYERBEGIN\n");
        for (int i = 0; i < playerCount; i++) {
            fscanf(file, "%s %d %d %d %d %d %d\n", &playerArray[i].name, &playerArray[i].position, &playerArray[i].score, &playerArray[i].isPlaying, &playerArray[i].isComputer, &playerArray[i].isWin, &playerArray[i].rankPlayer);
        }
        fscanf(file, "PLAYEREND\n");

        char colors[4][7] = {"\033[31m", "\033[34m", "\033[32m", "\033[33m"};

        game(playerCount, mode, currentTurn, L, ladderCount, S, snakeCount, playerArray, &winnerCount, difficulty, colors, grid, colorCount);
    } else {
        system("cls");
        printf("\nTidak ada game yang di save\n");
        printf("\nTekan q untuk kembali ke menu awal\n");
        bool waitInput = true;
        while (waitInput) {
          char ch = getch();
          if (ch == 'q') {
            waitInput = false;
          } else {
            printf("Input tidak valid\n");
          }
        }
    }
    
}

#endif
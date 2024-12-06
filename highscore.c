#ifndef highscore_c
#define highscore_c
#include "board.c"
#include "types.h"
#include <conio.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    int highScore;
} User;

void loadScores(User users[], int *count) {
    FILE *file = fopen("user.txt", "r");
    if (!file) {
        *count = 0;
        return;
    }

    *count = 0;
    while (fscanf(file, "%s %d", users[*count].name, &users[*count].highScore) == 2) {
        (*count)++;
    }
    fclose(file);
}

void updateHighScore(User users[], int *userCount, char name[], int newScore) {
    for (int i = 0; i < *userCount; i++) {
        if (strcmp(users[i].name, name) == 0) {
            if (newScore > users[i].highScore) {
                users[i].highScore = newScore;
            }
            return;
        }
    }
    strcpy(users[*userCount].name, name);
    users[*userCount].highScore = newScore;
    (*userCount)++;
}

void writeUsersToFile(User users[], int userCount) {
    FILE *file = fopen("user.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    for (int i = 0; i < userCount; i++) {
        fprintf(file, "%s %d\n", users[i].name, users[i].highScore);
    }

    fclose(file);
}

void displayScores(User users[], int count) {
    printf("High Scores:\n");
    printf("------------\n");
    for (int i = 0; i < count; i++) {
        printf("%s: %d\n", users[i].name, users[i].highScore);
    }
    printf("------------\n");
}

void saveHighScoreFromPlayer(Player playerArray[], int playerCount) {
    User users[100];
    int count = 0;
    loadScores(users, &count);
    // displayScores(users, count);

    for (int i = 0; i < playerCount; i++) {
        char newName[50];
        strcpy(newName, playerArray[i].name);
        int newScore = playerArray[i].score;
        updateHighScore(users, &count, newName, newScore);
    }
    // char newName[50] = "butoba";
    // int newScore = 1;
    writeUsersToFile(users, count);
    // displayScores(users, count);
}

void savePlayer(Player *playerArray, int players) {
  // Open file for writing
  FILE *file = fopen("saveFile.txt", "w");
  if (file == NULL) {
    perror("Error opening file");
  } else {
    //
  for (int i = 0; i < players; i++) {
    printf("%s", playerArray[i].name);
    fprintf(file, "%s, %d, %d, %d, %d\n", playerArray[i].name, playerArray[i].position, playerArray[i].score, 
            playerArray[i].isPlaying, playerArray[i].isComputer);
  }
  fprintf(file, "\n");
  // Close the file
  fclose(file);
  }  
}

void saveBoard(int dificulty, Ladder L, Snake S){
// Open file for writing
FILE *file = fopen("saveFile.txt", "w");
if (file == NULL) {
    perror("Error opening file");
} else {
    fprintf(file, "%d, %d, %d", dificulty, L, S);
    fprintf(file, "\n\n");
    fclose(file);
}

/*void saveTurn(int players){
FILE *file = fopen("saveFile.txt", "w");
if (file == NULL) {
    perror("Error opening file");
} else {
    fprintf(file, "%d", players );
    fclose(file);    
}
 */
}
void saveGame(Player playerArray[], int players, int ladderCount, int snakeCount, int dificulty){
FILE *file = fopen("saveFile.txt", "w");
if (file == NULL){
perror("Error opening file");
return;
}
savePlayer(&playerArray, players);
//saveBoard(ladderCount, snakeCount, dificulty);
fclose(file); 
}

#endif
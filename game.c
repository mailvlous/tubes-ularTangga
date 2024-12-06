#ifndef game_c
#define game_c
#include "board.c"
#include "types.h"
#include <conio.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void move(int n, Player *player, int grid);

void setScores(Player *players, int size, int newScore);
int score(Player *player);

void printScore(Player *player, int players);

int scoreTotal(Player *player, int position);
void setPosition(int n, Player *player);
int rollDice(int difficulty);
int rollDiceRigged(int difficulty, int nearestLadder, int nearestSnake);
bool timer();
int checkNearestLadder(Ladder L[], int ladderCount, Player player);

void checkLadderSnake(Player *player, Ladder L[], Snake S[], int ladderCount,
                      int snakeCount);
int checkNearestSnake(Snake S[], int snakeCount, Player player);

void writeOutputToFile(Player *playerArray, int players);
int move0(int n);

int modePicker();

int howManyPlayers(int players);

void checkWin(Player *player, int players);

void decideRank(Player *player, int players);

void printRank(Player *player, int players);

void checkLose(int playerCount, Player playerArray[]);

void decideComputerOrPlayer(Player *player, int players);



int rollDice(int difficulty) {
  int min = 1;
  int max = 6;

  // if (difficulty == 1) {
  //   return (rand() % (6 - 4 + 1) + min);
  // } else if (difficulty == 2) {
  //   return (rand() % (max - min + 1) + min);
  // } else if (difficulty == 3) {
  //   return (rand() % (3 - 1 + 1) + min);
  // }

  return (rand() % (max - min + 1) + min);
}

void checkWin(Player *player, int players) {
  for (int i = 0; i < players; i++) {
    if ((*player).position == 100) {
      (*player).isWin = true;
    } else {
      (*player).isWin = false;
  }
  }
}

void checkLose(int playerCount, Player playerArray[]) {
  for (int i = 0; i < playerCount; i++) {
    if (playerArray[i].isWin == false) {
      playerArray[i].score -= 50;
    }
  }
}

void decideRank(Player *player, int players) {
  int n = 3;
  for (int i = 0; i < players; i++) {
    if ((*player).isWin == true) {
      (*player).rankPlayer = 4 - n;
      n--;
    }
  }
}

void printRank(Player *player, int players) {
  for (int i = 0; i < players; i++) {
    if ((*player).isWin == true && (*player).rankPlayer == 1) {
      printf("%s Peringkat ke - %d dengan Skor : %d \n", player[i].name, player[i].rankPlayer, player[i].score);
    } else if ((*player).isWin == true && (*player).rankPlayer == 2) {
      printf("%s Peringkat ke - %d dengan Skor : %d \n", player[i].name, player[i].rankPlayer, player[i].score);
    } else if ((*player).isWin == true && (*player).rankPlayer == 3) {
      printf("%s Peringkat ke - %d dengan Skor : %d \n", player[i].name, player[i].rankPlayer, player[i].score);
    } else if ((*player).isWin == true && (*player).rankPlayer == 4) {
      printf("%s Peringkat ke - %d dengan Skor : %d \n", player[i].name, player[i].rankPlayer, player[i].score);
    }
  }
}

void decideComputerOrPlayer(Player *player, int players) {
  int input;
  for (int i = 0; i < players; i++) {
    printf("Tentukan player dengan nama %s adalah Player asli atau Computer \n Tekan 1 untuk Player dan 2 untuk Computer : ", player[i].name);
    scanf("%d", &input);
    if (input == 1) {
      player[i].isComputer = false;
    } else {
      player[i].isComputer = true;
    }
  }
}

bool isComputerOrPlayer(Player *player, int players) {

}

// printWinner(Player *playerArray, int players, int WinnerArray[], int winnerCount) {
//   if (())
// }

int rollDiceRigged(int difficulty, int nearestLadder, int nearestSnake) {
  int min = 1;
  int max = 6;
  int result = rand() % (max - min + 1) + min;
  if (difficulty == 1) {
    if (nearestLadder != -1) {
      int choose[2] = {result, nearestLadder};
      int chosen = rand() % (2);
      return (choose[chosen]);
    } else {
      return (result);
    }
  } else if (difficulty == 2) {
    return (result);
  } else if (difficulty == 3) {
    if (nearestSnake != -1) {
      int choose[2] = {result, nearestSnake};
      int chosen = rand() % (2);
      return (choose[chosen]);
    } else {
      return (result);
    }
  } else {
    return 0; // Invalid difficulty level.
  }
}

void sixCheck(int dice, int *i, char colors[][7], bool isComputer) {
  if (dice == 6) {
    printf("Karena mendapat angka 6, Player %d (", *i + 1);
    printPlayerIcons(*i, colors, 4, isComputer);
    printf(") mendapat giliran lagi");
    *i -= 1;
  }
}

int checkNearestLadder(Ladder L[], int ladderCount, Player player) {
  for (int i = player.position + 1; i <= player.position + 6; i++) {
    for (int j = 0; j < ladderCount; j++) {
      if (i == L[i][0]) {
        return i - player.position;
      }
    }
  }
  return -1;
}

int checkNearestSnake(Snake S[], int snakeCount, Player player) {
  for (int i = player.position + 1; i <= player.position + 6; i++) {
    for (int j = 0; j < snakeCount; j++) {
      if (i == S[i][0]) {
        return i - player.position;
      }
    }
  }
  return -1;
}

void move(int n, Player *player, int grid) {
  if ((*player).position == 0){
    int check = move0(n);
    if (check == true){
      (*player).position += 1;
      printf("Player %s moved %d steps, now on block %d\n ",
             (*player).name, n, (*player).position);
      printf("yay, anda dapat angka 1\n");
    } else {
        (*player).position += 0;
      printf("Player %s moved %d steps, now on block %d\n ",
             (*player).name, n, (*player).position);
      printf("aww, anda tidak dapat angka 1\n");       
    }
  } else if ((*player).position != 0){
int max = grid * grid;
  (*player).position += n;
  if ((*player).position > max) {
    (*player).position = max - (*player).position + max;
  }
  printf("Player %s moved %d steps, now on block %d\n ",
             (*player).name, n, (*player).position);
  }
}

int move0(int n){
  if (n == 1){
    return true;
  }
  return false;
}

void setScores(Player *players, int size, int newScore) {
  for (int i = 0; i < size; i++) {
    players[i].score = newScore;
  }
}

int score(Player *player) {

  return (*player).score - ((*player).position * 0.01);
  // (*player).score -= ((*player).position); // Kurangi skor pemain
  // return (*player).score;
  // for (int i = 0; i < 100; i++) {
  //   (*player).score = baseScore - minus;
  //   score = (*player).score;
  //   return score;
  // }
}

// int scoreTotal(Player *player, int position) {
//   return (*player).score - (*player).position;
// }

void printScore(Player *playerArray, int players) {
  for (int i = 0; i < players; i++) {
    printf("Player %s mendapatkan Score: %d\n", playerArray[i].name,
           playerArray[i].score);
  }
}

void writeOutputToFile(Player *playerArray, int players) {
  // Open file for writing
  FILE *file = fopen("output.txt", "w");
  if (file == NULL) {
    perror("Error opening file");
  } else {
    // Writing formatted text using fprintf
  for (int i = 0; i < players; i++) {
    printf("%s", playerArray[i].name);
    fprintf(file, "%s, %d\n", playerArray[i].name,
            playerArray[i].score);
  }

  // Close the file
  fclose(file);

  printf("Data written to 'output.txt'.\n");
  }  
}



void stepOnPlayer(Player playerArray[], int playerCount, int blockNum,
                  int playerNum) {
  int playerHere[playerCount];
  int playerHereCount = 0;
  if (blockNum != 0) {
    searchPlayer(playerArray, playerCount, blockNum, playerHere,
                 &playerHereCount);
    if (playerHereCount > 1) {
      for (int i = 0; i < playerHereCount; i++) {
        if (playerHere[i] != playerNum) {
          playerArray[playerHere[i]].position = 0;
          printf("Player %d menginjak Player %d (WKWK XD). PLayer %d sekarang "
                 "di kotak 0\n",
                 playerNum, playerHere[i], playerHere[i]);
        }
      }
    }
  }
}



void setPosition(int n, Player *player) {
   (*player).position = n; 
}

bool timer(int difficulty) {
  int seconds;
  if (difficulty == 1) {
    seconds = 10;
  } else if (difficulty == 2) {
    seconds = 5;
  } else if (difficulty == 3) {
    seconds = 3;
  }
  char ch;
  printf("Seconds: ");

  while (seconds > 0) {
    if (_kbhit()) {    // Periksa apakah ada input dari keyboard
      ch = _getch();   // Ambil input dari keyboard
      if (ch == ' ') { // Jika tombol spasi ditekan
        seconds = 0;   // Atur waktu menjadi 0
                     // Keluar dari loop
        return true;
      }
    }

    int s = seconds % 60;
    printf(" %d ", s);
    fflush(stdout);
    clock_t stop = clock() + CLOCKS_PER_SEC;
    while (clock() < stop) {
    }
    seconds--;
  }

  printf("\rTime's up!\n");
  return false;
}

void checkLadderSnake(Player *player, Ladder L[], Snake S[], int ladderCount,
                      int snakeCount) {
  for (int i = 0; i < ladderCount; i++) {
    if ((*player).position == L[i][0]) {
      setPosition(L[i][1], player);
      printf("Player %s discovered a Ladder! (YAYY :D) Player %s is now on "
             "block %d\n",
             (*player).name, (*player).name, L[i][1]);
    }
  }
  for (int i = 0; i < snakeCount; i++) {
    if ((*player).position == S[i][0]) {
      setPosition(S[i][1], player);
      printf("Player %s discovered a Snake! (AWW T-T) Player %s is now on "
             "block %d\n",
             (*player).name, (*player).name, S[i][1]);
    }
  }
}

int modePicker() {
  printf("Mode:\n");
  printf("1. Normal (Fair)\n");
  printf("2. Rigged\n");
  int mode;
  scanf("%d", &mode);
  while (mode != 1 && mode != 2) {
    scanf("%d", &mode);
  }
  return mode;
}

int howManyPlayers(int players) {
  printf("\n");
  printf("Banyak player (2 sampai 4): ");
  scanf("%d", &players);

  return players;
}

void printWinner(int WinnerArray[], int winnerCount) {
  for (int i = 0; i<winnerCount; i++) {
    printf("%d",WinnerArray[i]);
  }
}


#endif
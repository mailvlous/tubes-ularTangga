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
int rollDiceRigged(int difficulty, int nearestLadder, int nearestSnake, Player player);
bool timer();
int checkNearestLadder(Ladder L[], int ladderCount, Player player);

void checkLadderSnake(Player *player, Ladder L[], Snake S[], int ladderCount,
                      int snakeCount);
int checkNearestSnake(Snake S[], int snakeCount, Player player);

void writeOutputToFile(Player *playerArray, int players);
int move0(int n);

int modePicker();

int howManyPlayers(int players);

void checkWin(Player *player, int players, int *winnerCount);

void decideRank(Player *player, int players, int winnerCount);

void printRank(Player *player, int players);

void checkLose(int playerCount, Player playerArray[]);

void decideComputerOrPlayer(Player *player, int players);

void identifierComputer(Player *playerArray, int players);

void instruction(Player *playerArray);

void introScreen();


void introScreen() {
    printf("===========================================\n");
    printf("     WELCOME TO SNAKES AND LADDERS!        \n");
    printf("===========================================\n");


      printf("\n");
      printf("Menu:\n");
      printf("1. New Game\n");
      printf("2. High Score\n");
      printf("3. Exit\n");
      printf("4. Continue Previous Game\n");
      printf("\nPilih menu (1/2/3/4): ");
}



int rollDice(int difficulty) {
  /**
   * Deskripsi :
   *  Mengocok dadu untuk menentukan langkah player
   * IS:
   * 
   * FS:
   *  
 */
  int min = 1;
  int max = 6;
  return (rand() % (max - min + 1) + min);
}

void checkWin(Player *player, int players, int *winnerCount) {
    /**
   * Deskripsi :
   *  Mengocok dadu untuk menentukan langkah player
   * IS:
   * 
   * FS:
   *  
 */
  if ((*player).position == 100) {
    (*player).isWin = true;
    *winnerCount += 1;
  } else {
    (*player).isWin = false;
  }
}

void checkLose(int playerCount, Player playerArray[]) {
    /**
   * Deskripsi :
   *  Mengocok dadu untuk menentukan langkah player
   * IS:
   * 
   * FS:
   *  
 */
  for (int i = 0; i < playerCount; i++) {
    if (playerArray[i].isWin == false) {
      playerArray[i].score = 0;
    }
  }
}

void decideRank(Player *player, int players, int winnerCount) {
    /**
   * Deskripsi :
   *  Mengocok dadu untuk menentukan langkah player
   * IS:
   * 
   * FS:
   *  
 */
  (*player).rankPlayer = winnerCount;
}

void printRank(Player playerArray[], int players) {
  /**
   * Deskripsi :
   *  Mengocok dadu untuk menentukan langkah player
   * IS:
   * 
   * FS:
   *  
 */
  for (int i = 0; i < players; i++) {
    if (playerArray[i].isWin == true) {
      printf("%s Peringkat ke - %d dengan Skor : %d \n", playerArray[i].name, playerArray[i].rankPlayer, playerArray[i].score);
    } else {
      printf("%s kalah, dengan skor %d \n", playerArray[i].name, playerArray[i].score);
    }
  }
}

void decideComputerOrPlayer(Player *player, int players) {
    /**
   * Deskripsi :
   *  Mengocok dadu untuk menentukan langkah player
   * IS:
   * 
   * FS:
   *  
 */
  printf("\n");
  int input;
  for (int i = 0; i < players; i++) {
    printf("Tentukan player dengan nama %s adalah Manusia atau Computer\nTekan 1 untuk Manusia dan 2 untuk Computer: ", player[i].name);
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


int rollDiceRigged(int difficulty, int nearestLadder, int nearestSnake, Player player) {
    /**
   * Deskripsi :
   *  Mengocok dadu untuk menentukan langkah player
   * IS:
   * 
   * FS:
   *  
 */
  int min = 1;
  int max = 6;
  int result = rand() % (max - min + 1) + min;
  if (player.isComputer == false) {
      if (player.position == 0) {
      if (difficulty == 1) {
          int choose[2] = {result, 1};
          int chosen = rand() % (2);
          return (choose[chosen]);
      } else if ((difficulty == 2) || (difficulty == 3)) {
        return (result);
      } else {
        return -1; // Invalid difficulty level.
      }
    } else {
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
        return -1; // Invalid difficulty level.
      }
    }
  } else {
    if (player.position == 0) {
      if ((difficulty == 2) || (difficulty == 3)) {
          int choose[2] = {result, 1};
          int chosen = rand() % (2);
          return (choose[chosen]);
      } else if (difficulty == 1) {
        return (result);
      } else {
        return -1; // Invalid difficulty level.
      }
    } else {
      if (difficulty == 1) {
        if (nearestSnake != -1) {
          int choose[2] = {result, nearestSnake};
          int chosen = rand() % (2);
          return (choose[chosen]);
        } else {
          return (result);
        }
      } else if (difficulty == 2) {
        return (result);
      } else if (difficulty == 3) {
        if (nearestLadder != -1) {
          int choose[2] = {result, nearestLadder};
          int chosen = rand() % (2);
          return (choose[chosen]);
        } else {
          return (result);
        }
      } else {
        return -1; // Invalid difficulty level.
      }
    }
  }
  
  
}

void sixCheck(int dice, int *i, char colors[][7], bool isComputer) {
    /**
   * Deskripsi :
   *  Mengocok dadu untuk menentukan langkah player
   * IS:
   * 
   * FS:
   *  
 */
  if (dice == 6) {
    printf("Karena mendapat angka 6, Player %d (", *i + 1);
    printPlayerIcons(*i, colors, 4, isComputer);
    printf(") mendapat giliran lagi");
    *i -= 1;
  }
}

int checkNearestLadder(Ladder L[], int ladderCount, Player player) {
    /**
   * Deskripsi :
   *  Mengocok dadu untuk menentukan langkah player
   * IS:
   * 
   * FS:
   *  
 */
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
    /**
   * Deskripsi :
   *  Mengocok dadu untuk menentukan langkah player
   * IS:
   * 
   * FS:
   *  
 */
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
    /**
   * Deskripsi :
   *  Mengocok dadu untuk menentukan langkah player
   * IS:
   * 
   * FS:
   *  
 */
  if ((*player).position == 0){
    int check = move0(n);
    if (check == true){
      (*player).position += 1;
      printf("Player %s moved %d steps, now on block %d\n",
             (*player).name, n, (*player).position);
      printf("yay, anda dapat angka 1\n");
    } else {
        (*player).position += 0;
      printf("Player %s moved %d steps, now on block %d\n",
             (*player).name, n, (*player).position);
      printf("aww, anda tidak dapat angka 1\n");       
    }
  } else if ((*player).position != 0){
int max = grid * grid;
  (*player).position += n;
  if ((*player).position > max) {
    (*player).position = max - (*player).position + max;
  }
  printf("Player %s moved %d steps, now on block %d\n",
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
      /**
   * Deskripsi :
   *  Mengocok dadu untuk menentukan langkah player
   * IS:
   * 
   * FS:
   *  
 */
  for (int i = 0; i < size; i++) {
    players[i].score = newScore;
  }
}

int score(Player *player) {
      /**
   * Deskripsi :
   *  Mengocok dadu untuk menentukan langkah player
   * IS:
   * 
   * FS:
   *  
 */
  return (*player).score - ((*player).position * 0.01);
}

// int scoreTotal(Player *player, int position) {
//   return (*player).score - (*player).position;
// }

void printScore(Player *playerArray, int players) {
      /**
   * Deskripsi :
   *  Mengocok dadu untuk menentukan langkah player
   * IS:
   * 
   * FS:
   *  
 */
  printf("\n ------- Skor Sementara ------\n");
  for (int i = 0; i < players; i++) {
    printf("Player %s mendapatkan Score: %d\n", playerArray[i].name,
           playerArray[i].score);
  }
}

void writeOutputToFile(Player *playerArray, int players) {
      /**
   * Deskripsi :
   *  Mengocok dadu untuk menentukan langkah player
   * IS:
   * 
   * FS:
   *  
 */
  // Open file for writing
  FILE *file = fopen("output.txt", "w");
  if (file == NULL) {
    perror("Error opening file");
  } else {
    // Writing formatted text using fprintf
  for (int i = 0; i < players; i++) {
    printf("%s", playerArray[i].name);
    if (playerArray[i].score <= 100) {
      fprintf(file, "%s, %d\n", playerArray[i].name,
        playerArray[i].score);
    } else if (playerArray[i].score > 100) {
      playerArray[i].score = playerArray[i].score - 16;
    }

  }

  // Close the file
  fclose(file);

  printf("Data written to 'output.txt'.\n");
  }  
}



void stepOnPlayer(Player playerArray[], int playerCount, int blockNum,
                  int playerNum) {
/**
   * Deskripsi :
   *  Mengocok dadu untuk menentukan langkah player
   * IS:
   * 
   * FS:
   *  
 */
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
      /**
   * Deskripsi :
   *  Mengocok dadu untuk menentukan langkah player
   * IS:
   * 
   * FS:
   *  
 */
   (*player).position = n; 
}

bool timer(int difficulty, Player *player) {
  /**
   * Deskripsi :
   *  Mengocok dadu untuk menentukan langkah player
   * IS:
   * 
   * FS:
   *  
 */
  int seconds;
  if (difficulty == 1) {
    seconds = 10;
  } else if (difficulty == 2) {
    seconds = 5;
  } else if (difficulty == 3) {
    seconds = 3;
  }
  char ch;
  printf("Timer: ");

  if ((*player).isComputer == false ) {
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
  } else {
    int seconds = 1;
    int s = seconds % 60;
    printf(" %d ", s);
    fflush(stdout);
    clock_t stop = clock() + CLOCKS_PER_SEC;
    while (clock() < stop) {
    }
    seconds--;
    return true;
  }
  printf("\rTime's up!\n");
  return false;
}

void identifierComputer(Player *playerArray, int players) {
    /**
   * Deskripsi :
   *  Mengocok dadu untuk menentukan langkah player
   * IS:
   * 
   * FS:
   *  
 */
    for (int i = 0; i < players; i++) {
        if (playerArray[i].isComputer ==  true) {
            strcpy(playerArray[i].name, "(Computer)");
        }
    }
}

void checkLadderSnake(Player *player, Ladder L[], Snake S[], int ladderCount,
                      int snakeCount) {
  /**
   * Deskripsi :
   *  Mengocok dadu untuk menentukan langkah player
   * IS:
   * 
   * FS:
   *  
 */
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
  /**
   * Deskripsi :
   *  Mengocok dadu untuk menentukan langkah player
   * IS:
   * 
   * FS:
   *  
 */
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
  /**
   * Deskripsi :
   *  Mengocok dadu untuk menentukan langkah player
   * IS:
   * 
   * FS:
   *  
 */
  printf("\n");
  printf("Banyak player (2 sampai 4): ");
  scanf("%d", &players);
  printf("\n");

  return players;
}

void printWinner(int WinnerArray[], int winnerCount) {
  /**
   * Deskripsi :
   *  Mengocok dadu untuk menentukan langkah player
   * IS:
   * 
   * FS:
   *  
 */
  for (int i = 0; i<winnerCount; i++) {
    printf("%d",WinnerArray[i]);
  }
}

void instruction(Player *playerArray) {
  /**
   * Deskripsi :
   *  Mengocok dadu untuk menentukan langkah player
   * IS:
   * 
   * FS:
   *  
 */
    printf("=== Permainan Ular Tangga ===\n");
    printf("Instruksi:\n");
    printf("- Tekan [Spasi] untuk giliran selanjutnya (lempar dadu).\n");
    printf("- Tekan [W] untuk menyerah dan keluar tanpa menyimpan.\n");
    printf("- Tekan [S] untuk keluar dan menyimpan permainan.\n");
    printf("- Tekan [Q] untuk keluar dan menyelesaikan permainan tanpa menyimpan.\n");
    printf("Player dengan nama %s berada di Posisi: %d\n", (*playerArray).name,  (*playerArray).position);
}




#endif
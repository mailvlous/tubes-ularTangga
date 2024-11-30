#include "board.c"
#include "game.c"
#include "types.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
// #include <curses.h>

void multiplayer(int players);
int setDifficulty();

int main() {
  printf("\n");
  printf("---------------------\n");
  printf("Snakes and Ladders !!\n");
  printf("---------------------\n");
  printf("\n");
  bool isRunning = true;
  while (isRunning) {
    printf("Menu:\n");
    printf("1. Main multiplayer\n");
    printf("2. VS Computer\n");
    printf("3. Exit\n");
    printf("Pilih menu (1/2): ");
    int menuPicked;
    scanf("%d", &menuPicked);
    getchar();
    switch (menuPicked) {
    case 1:
      printf("\n");
      printf("Banyak player (1 sampai 4): ");
      int players;
      scanf("%d", &players);
      printf("\n");
      multiplayer(players);
      break;
    case 2:
      printf("\n");
      printf("Banyak player (1 sampai 4): ");
      int playerss;
      scanf("%d", &playerss);
      printf("\n");
    case 3:
      printf("\n");
      printf("bai baii\n");
      printf("\n");
      isRunning = false;
      break;
    default:
      printf("\n");
      printf("Pilihan menu tidak ada\n");
      printf("\n");
    }
  }
  return 0;
}

void multiplayer(int players) {
  // printf("Ceritanya anda bermain nichhh dengan %d player", players);
  char colors[4][7] = {"\033[31m", "\033[34m", "\033[32m", "\033[33m"};
  int ladderCount, snakeCount;
  Player playerArray[players];
  initiatePlayers(playerArray, players);
  printPlayers(playerArray, players, colors, 4);
  int difficulty = setDifficulty();
  getLadderSnakeCount(&ladderCount, &snakeCount, difficulty);
  Snake S[snakeCount];
  Ladder L[ladderCount];

  initiateBoard(snakeCount, ladderCount, S, L);
  bool isRunning = true;
  int grid = 10;
  while (isRunning) {
    for (int i = 0; i < players; i++) {
      system("clear");
      printf("Keterangan: L = Tangga, S = Ular");
      printf("\n");
      printBoardVSPlayer(S, L, playerArray, snakeCount, ladderCount, players,
                         grid);
      printBlock0(playerArray, players);
      char ch;

      printf("Giliran Player %d (", i + 1);
      printPlayerIcons(i, colors, 4);
      printf(")\nTekan spasi untuk mengocok dadu\n");
      while (isRunning) {
        ch = getchar();
        if (ch == ' ') {
          break;
        }
      }

      int dice = rollDice(difficulty);
      system("clear");
      move(dice, &playerArray[i], grid);

      checkLadderSnake(&playerArray[i], L, S, ladderCount, snakeCount);
      if (difficulty == 3) {
        stepOnPlayer(playerArray,players,playerArray[i].position,i);
      }
      printBoardVSPlayer(S, L, playerArray, snakeCount, ladderCount, players,
                         grid);
      printBlock0(playerArray, players);
      if (dice == 6) {
        printf("Karena mendapat angka 6, Player %d (", i + 1);
        printPlayerIcons(i, colors, 4);
        printf(") mendapat giliran lagi");
        i -= 1;
      }
      printf("\nTekan spasi untuk ke giliran selanjutnya\n");
      while (isRunning) {
        ch = getchar();
        if (ch == ' ') {
          break;
        }
      }
    }
  }
}

// void computer(int computer, int player){
//     // printf("Ceritanya anda bermain nichhh dengan %d player", players);
//   char colors[4][7] = {"\033[31m", "\033[34m", "\033[32m", "\033[33m"};
//   Computer computerArray[computer];
//   Computer playerArray[player];
//   int ladderCount, snakeCount;
//   Snake S[snakeCount];
//   Ladder L[ladderCount];

//   initiatePlayers(computerArray, computer);
//   printPlayers(computerArray, computer, colors, 4);
//   int difficulty = setDifficulty();

//   getLadderSnakeCount(&ladderCount, &snakeCount, difficulty);

//   initiateBoard(snakeCount, ladderCount, S, L);
//   bool isRunning = true;
//   int grid = 10;
//   while (isRunning) {
//     for (int i = 0; i < computer; i++) {
//       system("clear");
//       printf("Keterangan: L = Tangga, S = Ular");
//       printf("\n");
//       printBoardVSPlayer(S, L, computerArray, snakeCount, ladderCount,
//       computer, grid); printBlock0(computerArray, computer); int temp;
//       getchar();
//       printf("Giliran Comoputer %d\n", i+1);
//       printf("Tekan angka 1 untuk mengocok dadu\n");
//       // timer();
//       scanf("%d", &temp);

//       move(rollDice(difficulty), &playerArray[i], grid);
//       move(rollDice(difficulty), &computerArray[i], grid);
//       checkLadderSnake(&playerArray[i], L, S, ladderCount, snakeCount);
//     }
//   }
// }

int setDifficulty() {
  printf("1. Easy\n2. Normal\n3. Hard\n");
  int selected;
  getchar();
  printf("Pilih Difficulty (1/2/3)");
  scanf("%d", &selected);
  while ((selected != 1) && (selected != 2) && (selected != 3)) {
    printf("Difficulty tidak ada");
    scanf("%d", &selected);
  }
  return selected;
}
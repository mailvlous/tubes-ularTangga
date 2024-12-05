#include "board.c"
#include "game.c"
#include "types.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
// #include <curses.h>

void multiplayer(int players, int mode);
int modePicker();
void multiplayer(int players, int mode);
int setDifficulty();
void startGame();

void setScores(Player *players, int size, int newScore);

int score(Player *player);

void printScore(Player *player, int players);

bool timer(int difficulty);

void writeOutputToFile(Player *playerArray, int players);

int howManyPlayers(int players);

void checkWin(Player *player, int players);

void decideRank(Player *player, int players);

void printRank(Player *player, int players);

// void printWinner(int WinnerArray[], int winnerCount);

int main() {
  startGame();
  return 0;
}


void startGame() {
  system("cls");
  printf("---------------------\n");
  printf("Snakes and Ladders :D\n");
  printf("---------------------\n");
  printf("\n");
  bool isRunning = true;
  while (isRunning) {
    printf("Menu:\n");
    printf("1. Main multiplayer\n");
    printf("2. VS Computer\n");
    printf("3. Exit\n");
    printf("Pilih menu (1/2): ");
    //int menuPicked;
    printf("wsaws");
    //scanf("%d", &menuPicked);
    //getchar();
    int mode = modePicker();
    switch (mode) {
    case 1:
      printf("\n");
      printf("Banyak player (1 sampai 4): ");
      int players;
      players = howManyPlayers(players);
      multiplayer(players, mode);
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
}

void multiplayer(int players, int mode) {
  // printf("Ceritanya anda bermain nichhh dengan %d player", players);
  char colors[4][7] = {"\033[31m", "\033[34m", "\033[32m", "\033[33m"};
  int ladderCount, snakeCount;
  Player playerArray[players];
  initiatePlayers(playerArray, players);
  decideComputerOrPlayer(playerArray, players);
  printPlayers(playerArray, players, colors, 4);
  int difficulty = setDifficulty();
  getLadderSnakeCount(&ladderCount, &snakeCount, difficulty);
  Snake S[snakeCount];
  Ladder L[ladderCount];
  int minus;
  setScores(playerArray, players, 116);
  int winnerArray[players-1];

  int winnerCount = 0;
  initiateBoard(snakeCount, ladderCount, S, L);
  bool isRunning = true;
  int grid = 10;
  while (isRunning) {
    for (int i = 0; i < players; i++) {
      system("cls");
      if (winnerCount == players) {
        printf("GAME SELESAIIII");
        isRunning = false;
        break;
      } else if (playerArray[i].isPlaying == true) {

      char ch;

      printf("Giliran Player %d (", i + 1);
      printPlayerIcons(i, colors, 4);
      printf(")\nTekan spasi untuk mengocok dadu\n");

      
      bool roll = timer(difficulty);
      
      // while (isRunning) { 
      //   ch = getch(); 
      //   if (ch == ' ') {
      //     // playerArray[i].score = score(&playerArray[i], minus, baseScore); // Kurangi skor
      //     // minus++; // Tambah nilai pengurangan
      //     // printf("Skor Pemain %d sekarang: %d\n", i + 1, &playerArray[i].score);
      //     break; // Keluar dari loop untuk giliran pemain
      //   }
      // }
      int dice;

      if (roll == true) {
  
      if (mode == 1) {
        dice = rollDice(difficulty);
      } else {
        int nearestLadder = checkNearestLadder(L, ladderCount, playerArray[i]);
        int nearestSnake = checkNearestSnake(S, snakeCount, playerArray[i]);
        dice = rollDiceRigged(difficulty, nearestLadder, nearestSnake);
      }
      
      int scoreTotal;
      system("cls");
      move(dice, &playerArray[i], grid);
      playerArray[i].score = score(&playerArray[i]);
      } else {
        dice = 0;
      }
      
      
      // // playerArray[i].score = 116;
      // minus = 1;
      // playerArray[i].score = score(&playerArray[i], minus, baseScore);
      // minus++;
      // printf("%d", i);
      bool isWin;
      checkWin(&playerArray[i], winnerArray, &winnerCount, i, &isWin);
      if (!isWin) {
          checkLadderSnake(&playerArray[i], L, S, ladderCount, snakeCount);
        if (difficulty == 3) {
          stepOnPlayer(playerArray,players,playerArray[i].position,i);
        }
        printf("Keterangan: L = Tangga, S = Ular");
        printf("\n");
        printBoardVSPlayer(S, L, playerArray, snakeCount, ladderCount, players,
                           grid);
        printBlock0(playerArray, players);

        char ch;

        printf("Giliran Player %d (", i + 1);
        printPlayerIcons(i, colors, 4);
        printf("\nTekan spasi untuk mengocok dadu\n");

        bool roll = timer(difficulty);

        int dice;
        if (roll == true) {

          if (mode == 1) {
            dice = rollDice(difficulty);
          } else {
            int nearestLadder =
                checkNearestLadder(L, ladderCount, playerArray[i]);
            int nearestSnake = checkNearestSnake(S, snakeCount, playerArray[i]);
            dice = rollDiceRigged(difficulty, nearestLadder, nearestSnake);
          }

          int scoreTotal;
          system("cls");
          move(dice, &playerArray[i], grid);
          playerArray[i].score = score(&playerArray[i]);
        } else {
          dice = 0;
        }

        bool isWin;

        checkWin(&playerArray[i], players);
        decideRank(&playerArray[i], players);
        

        if (!isWin) {
          checkLadderSnake(&playerArray[i], L, S, ladderCount, snakeCount);
          if (difficulty == 3) {
            stepOnPlayer(playerArray, players, playerArray[i].position, i);
          }
          printBoardVSPlayer(S, L, playerArray, snakeCount, ladderCount,
                             players, grid);
          printBlock0(playerArray, players);
          printScore(playerArray, players);

          sixCheck(dice, &i, colors);
          // printf("%d", winnerCount);
        } else {
          printBoardVSPlayer(S, L, playerArray, snakeCount, ladderCount,
                             players, grid);
          printBlock0(playerArray, players);
          printScore(playerArray, players);
        }

        printf("\nTekan spasi untuk ke giliran selanjutnya\n");
        printf("\nTekan q untuk keluar, kembali ke menu awal, dan mencetak "
               "skor\n");
        printf("Posisi: %d\n", playerArray[i].position);
        printRank(&playerArray[i], players);
        // bool wawa = true;
        // while (isRunning) {
        // printf("%d", i);
        bool waitInput = true;
        while (waitInput) {
          ch = getch();
          if (ch == 'q') {
            writeOutputToFile(&playerArray[i], players);
            isRunning = false;
            break;
          } else if (ch == ' ') {
            waitInput = false;
          } else {
            printf("Input tidak valid\n");
          }
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
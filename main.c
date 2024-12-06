#include "board.c"
#include "game.c"
#include "types.h"
#include "highscore.c"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
// #include <curses.h>

void multiplayer();
void printAllHighScore();
int modePicker();
int setDifficulty();
void startGame();

void setScores(Player *players, int size, int newScore);

int score(Player *player);

void printScore(Player *player, int players);

bool timer(int difficulty, Player *player);

void writeOutputToFile(Player *playerArray, int players);

int howManyPlayers(int players);

// void checkWin(Player *player, int players);

// void decideRank(Player *player, int players);

void printRank(Player *player, int players);

// void printWinner(int WinnerArray[], int winnerCount);

int main() {
  startGame();
  return 0;
}


void startGame() {
  
  bool isRunning = true;
  while (isRunning) {
    system("cls");
  printf("---------------------\n");
  printf("Snakes and Ladders :D\n");
  printf("---------------------\n");
  printf("\n");
    printf("Menu:\n");
    printf("1. New Game\n");
    printf("2. High Score\n");
    printf("3. Exit\n");
    printf("4. Continue Previous Game\n");
    printf("\nPilih menu (1/2/3/4): ");
    int menuPicked;
    scanf("%d", &menuPicked);
    getchar();
    
    switch (menuPicked) {
    case 1:
      multiplayer();
      break;
    case 2:
    printAllHighScore();
      break;
    case 3:
      printf("\nTHANKS FOR PLAYING :3\n");
      isRunning = false;
      break;
    default:
      printf("\n");
      printf("Pilihan menu tidak ada ._.\n");
      printf("\n");
    }
  }
}

void multiplayer() {
  int players;
  players = howManyPlayers(players);
  int mode = modePicker();
  // printf("Ceritanya anda bermain nichhh dengan %d player", players);
  char colors[4][7] = {"\033[31m", "\033[34m", "\033[32m", "\033[33m"};
  int ladderCount, snakeCount;
  Player playerArray[players];
  initiatePlayers(playerArray, players);
  decideComputerOrPlayer(playerArray, players);
  colorsComputer(playerArray, players);
  printPlayers(playerArray, players, colors, 4);
  int difficulty = setDifficulty();
  getLadderSnakeCount(&ladderCount, &snakeCount, difficulty);
  Snake S[snakeCount];
  Ladder L[ladderCount];
  int minus;
  setScores(playerArray, players, 116);
  int winnerArray[players-1];
  int grid = 10;
  int winnerCount = 0;
  initiateBoard(snakeCount, ladderCount, S, L);
  bool isRunning = true;
  
  while (isRunning) {
    for (int i = 0; i < players; i++) {
      system("cls");
      if (winnerCount == players-1) {
        printf("\nKarena sisa satu orang, permainan selesai :)\n");
        i = players;
        isRunning = false;
        printf("\nTekan spasi untuk melanjutkan\n");
        bool waitInput = true;
        while (waitInput) {
          char ch = getch();
          if (ch == ' ') {
            waitInput = false;
          } else {
            printf("Input tidak valid\n");
          }
        }
      } else if (playerArray[i].isWin == false) {
        char ch;
        printBoardVSPlayer(S, L, playerArray, snakeCount, ladderCount, players,
                           grid);
                           printBlock0(playerArray, players);
        printf("Giliran Player %d (", i + 1);
        printPlayerIcons(i, colors, 4, playerArray[i].isComputer);
        printf("\nTekan spasi untuk mengocok dadu\n");

        bool roll = timer(difficulty, &playerArray[i]);

        int dice;
        if (roll == true) {
          if (mode == 1) {
            dice = rollDice(difficulty);
          } else {
            int nearestLadder =
                checkNearestLadder(L, ladderCount, playerArray[i]);
            int nearestSnake = checkNearestSnake(S, snakeCount, playerArray[i]);
            dice = rollDiceRigged(difficulty, nearestLadder, nearestSnake, playerArray[i]);
          }

          int scoreTotal;
          system("cls");
          move(dice, &playerArray[i], grid);
          playerArray[i].score = score(&playerArray[i]);
        } else {
          dice = 0;
        }

        checkWin(&playerArray[i], players, &winnerCount);

        if (playerArray[i].isWin == false) {
          checkLadderSnake(&playerArray[i], L, S, ladderCount, snakeCount);
          if (difficulty == 3) {
            stepOnPlayer(playerArray, players, playerArray[i].position, i);
          }
          printBoardVSPlayer(S, L, playerArray, snakeCount, ladderCount,
                             players, grid);
          printBlock0(playerArray, players);
          printScore(playerArray, players);

          sixCheck(dice, &i, colors, playerArray[i].isComputer);
          // printf("%d", winnerCount);
        } else {
          decideRank(&(playerArray[i]), players, winnerCount);
          printBoardVSPlayer(S, L, playerArray, snakeCount, ladderCount,
                             players, grid);
          printBlock0(playerArray, players);
          printScore(playerArray, players);
        }

        printf("\nTekan spasi untuk ke giliran selanjutnya\n");
        printf("Tekan w untuk udahan sendiri\n");
        printf("Tekan s untuk keluar dan menyimpan game untuk dimainkan di lain waktu\n");
        printf("Tekan q untuk menyelesaikan game tanpa menyimpan game\n");
        printf("Posisi: %d\n", playerArray[i].position);
        // printRank(playerArray, players);
        // bool wawa = true;
        // while (isRunning) {
        // printf("%d", i);
        bool waitInput = true;
        while (waitInput) {
          ch = getch();
          if (ch == 'q') {
            i = players;
            isRunning = false;
            break;
          } else if (ch == ' ') {
            waitInput = false;
          } else if (ch == 'w') {
            playerArray[i].isPlaying == false;
          } else {
            printf("Input tidak valid\n");
          }
        }
      }
    }
  }
  system("cls");
  checkLose(players, playerArray);
  printRank(playerArray, players);
  writeOutputToFile(playerArray, players);
  saveHighScoreFromPlayer(playerArray, players);
  printf("GAME SELESAIIII");
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

// void gameLoop(int playerCount, int mode, int currentTurn, )

void printAllHighScore() {
  system("cls");
  User users[100];
    int count = 0;
    loadScores(users, &count);
    displayScores(users, count);
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
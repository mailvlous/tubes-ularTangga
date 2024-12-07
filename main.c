#ifndef main_c
#define main_c

#include "board.c"
#include "game.c"
#include "types.h"
#include "highscore.c"
#include "saveFile.c"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
// #include <curses.h>

void initiateGame();
void printAllHighScore();
int modePicker();
int setDifficulty();
void startGame();
void game(int playerCount, int mode, int currentTurn, Ladder L[], int ladderCount, Snake S[], int snakeCount, Player playerArray[], int *winnerCount, int difficulty, char colors[][7], int grid, int colorCount);

void setScores(Player *players, int size, int newScore);

int getTurn(int j, int playerCount);

int score(Player *player);

void printScore(Player *player, int players);

bool timer(int difficulty, Player *player);

void writeOutputToFile(Player *playerArray, int players);

int howManyPlayers(int players);

void introScreen();

void infoRule();

void infoDifficulty();

void infoMode();

// void checkWin(Player *player, int players);

// void decideRank(Player *player, int players);

// void printRank(Player *player, int players);

// void printWinner(int WinnerArray[], int winnerCount);

int main() {
  /**
   * Deskripsi: 
   * Fungsi utama yang memulai permainan dengan memanggil `startGame`.
   *
   * IS: Tidak ada input sebelum memulai permainan.
   * FS: Permainan dimulai.
   */
  startGame();
  return 0;
}


void startGame() {
  /**
   * Deskripsi:
   *  - Memulai permainan dengan menampilkan layar intro dan memberikan pilihan kepada pengguna untuk:
   *    1. Memulai permainan multiplayer
   *    2. Melihat skor tertinggi
   *    3. Keluar dari permainan
   *    4. Memuat permainan yang disimpan
   *    5. Menampilkan aturan permainan
   *  - Fungsi ini akan terus berjalan hingga pengguna memilih untuk keluar dari permainan.
   *
   * IS:
   *  - Menampilkan layar intro dan menunggu input dari pengguna untuk memilih opsi.
   *
   * FS:
   *  - Berdasarkan input pengguna, memulai opsi yang dipilih (misalnya memulai permainan, menampilkan skor, keluar, dll).
   */
  bool isRunning = true;
  while (isRunning) {
    system("cls");
    introScreen();
    bool waitInput = true;
    while (waitInput) {
          char ch = getch();
          if (ch == '1') {
            initiateGame();
            waitInput = false;
          } else if (ch == '2') {
            printAllHighScore();
            waitInput = false;
          } else if (ch == '3') {
            printf("\nTHANKS FOR PLAYING :3\n");
            isRunning = false;
            waitInput = false;
          } else if (ch == '4') {
            load();
            waitInput = false;
          } else if (ch == '5') {
            infoRule();
            while (waitInput){
            char ch = getch();
            if (ch == ' '){
              waitInput = false;
            } else {
              printf("input tidak valid\n");
            }
          }
          }
        }
  }
}

void initiateGame() {
    /**
   * Deskripsi:
   *  - Memulai permainan dengan mempersiapkan semua elemen permainan seperti jumlah pemain, mode permainan, papan, ular, tangga, dan pemain.
   *  - Mengatur kesulitan permainan, warna pemain, serta memilih pemain komputer atau manusia.
   *  - Menginisialisasi skor dan elemen lainnya yang diperlukan sebelum memulai permainan.
   *  - Setelah persiapan selesai, fungsi game dijalankan untuk mengelola jalannya permainan.
   *
   * IS:
   *  - Input jumlah pemain, mode permainan, dan kesulitan telah diterima.
   *  - Pemain diinisialisasi dengan benar, dan papan permainan disiapkan.
   *
   * FS:
   *  - Semua elemen permainan sudah siap dan permainan dimulai dengan memanggil fungsi `game()`.
   */
  system("cls");
  int players;
  players = howManyPlayers(players);
  infoMode();
  int mode = modePicker();
  char colors[4][7] = {"\033[31m", "\033[34m", "\033[32m", "\033[33m"};
  int colorCount = 4;
  int ladderCount, snakeCount;
  Player playerArray[players];
  initiatePlayers(playerArray, players);
  decideComputerOrPlayer(playerArray, players);
  printPlayers(playerArray, players, colors, 4);
  infoDifficulty();
  int difficulty = setDifficulty();
  getLadderSnakeCount(&ladderCount, &snakeCount, difficulty);
  Snake S[snakeCount];
  Ladder L[ladderCount];
  setScores(playerArray, players, 116);
  int grid = 10;
  int winnerCount = 0;
  initiateBoard(snakeCount, ladderCount, S, L);
  int currentTurn = 0;
  int playing = players;
  bool isFinished = false;
  game(players, mode, currentTurn, L, ladderCount, S, snakeCount, playerArray, &winnerCount, difficulty, colors, grid, colorCount);
}

void game(int playerCount, int mode, int currentTurn, Ladder L[], int ladderCount, Snake S[], int snakeCount, Player playerArray[], int *winnerCount, int difficulty, char colors[][7], int grid, int colorCount) {
  /**
   * Deskripsi:
   *  Menjalankan permainan, mengelola giliran pemain, mengocok dadu, pergerakan pemain,
   *  pengecekan kemenangan, serta interaksi dengan ular, tangga, dan penyimpanan status permainan.
   *
   * IS:
   *  - Data terkait pemain, ular, tangga, dan mode permainan sudah ada.
   *  - Permainan berjalan, pemain mendapatkan giliran.
   *  - Mode permainan dan tingkat kesulitan sudah ditentukan.
   *
   * FS:
   *  - Pemain bergiliran bermain, bergerak di papan, dan mempengaruhi permainan.
   *  - Pemain yang menang atau kalah diperiksa, dan peringkat akhir dihitung.
   *  - Input pengguna diproses untuk melanjutkan permainan, menyimpan progres, atau keluar.
   *  - Setelah selesai, peringkat dan data permainan disimpan.
   */
  bool isFinished = false;
  bool isRunning = true;
  while (isRunning) {
    for (int j = currentTurn; j < currentTurn + playerCount; j++) {
        int i = getTurn(j, playerCount);
      system("cls");
      if ((*winnerCount == playerCount - 1)) {
        printf("Karena sisa satu orang, permainan selesai :)\n");
        j = currentTurn + playerCount;
        isFinished = true;
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
      } else if ((playerArray[i].isWin == false) && (playerArray[i].isPlaying == true)) {
        char ch;
        printBoard(S, L, playerArray, snakeCount, ladderCount, playerCount, grid);
        printBlock0(playerArray, playerCount);
        printf("Giliran Player %d ", i + 1 );
        printPlayerIcons(i, colors, 4, playerArray[i].isComputer);
        printf("\nTekan spasi untuk mengocok dadu\n");

        bool roll = timer(difficulty, &playerArray[i]);
        playerArray[i].score = score(&playerArray[i]);

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
          
        } else {
          dice = 0;
        }

        checkWin(&playerArray[i], playerCount, winnerCount);

        if (playerArray[i].isWin == false) {
          checkLadderSnake(&playerArray[i], L, S, ladderCount, snakeCount);
          if (difficulty == 3) {
            stepOnPlayer(playerArray, playerCount, playerArray[i].position, i);
          }
          printBoard(S, L, playerArray, snakeCount, ladderCount,
                             playerCount, grid);
          printBlock0(playerArray, playerCount);
          printScore(playerArray, playerCount);

          sixCheck(dice, &j, i, colors, playerArray[i].isComputer);
          // printf("%d", winnerCount);
        } else {
          decideRank(&(playerArray[i]), playerCount, *winnerCount);
          printBoard(S, L, playerArray, snakeCount, ladderCount,
                             playerCount, grid);
          printBlock0(playerArray, playerCount);
          printScore(playerArray, playerCount);
        }

        instruction(playerArray);
        // printRank(playerArray, players);
        // bool wawa = true;
        // while (isRunning) {
        // printf("%d", i);
        bool waitInput = true;
        while (waitInput) {
          ch = getch();
          if (ch == 'q') {
            isFinished = true;
            j = currentTurn + playerCount;
            isRunning = false;
            break;
          }/*else if (ch == 's'){
            saveGame(playerArray, players, ladderCount, snakeCount, difficulty);
            i = players;
            isRunning = false;
            break;
            
          } */
          else if (ch == ' ') {
            waitInput = false;
            break;
          } else if (ch == 'w') {
            playerArray[i].isPlaying == false;
          } else if (ch == 's') {
            int nextTurn = getTurn(j + 1, playerCount);
            save(playerCount, mode, nextTurn, L, ladderCount, S, snakeCount, playerArray, *winnerCount, difficulty, grid, colorCount);
            j = currentTurn + playerCount;
            isRunning = false;
            break;
          } else {
            printf("Input tidak valid\n");
          }
        }
      }
    }
  }
  if (isFinished == true) {
    system("cls");
    checkLose(playerCount, playerArray);
    printRank(playerArray, playerCount);
    writeOutputToFile(playerArray, playerCount);
    saveHighScoreFromPlayer(playerArray, playerCount);
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
}

int getTurn(int j, int playerCount) {
  /**
   * Deskripsi:
   * Fungsi untuk menghitung giliran pemain dengan memastikan giliran tetap berada dalam batas jumlah pemain.
   *
   * IS: `j` adalah indeks giliran pemain yang sedang dimainkan, `playerCount` adalah total jumlah pemain.
   * FS: Mengembalikan indeks pemain berikutnya dengan memutar kembali setelah mencapai jumlah pemain.
   */
  if (j >= playerCount) {
    return j - playerCount;
  } else {
    return j;
  }
}

void printAllHighScore() {
  /**
   * Deskripsi:
   * Fungsi untuk menampilkan daftar skor tertinggi dari pemain yang disimpan.
   * Menunggu input dari pengguna untuk kembali ke menu awal.
   *
   * IS: Menampilkan layar kosong, memuat data skor pemain.
   * FS: Menunggu input pengguna (tekan 'q' untuk kembali ke menu utama), konsol menampilkan data highscore pemain.
   */
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

int setDifficulty() {
  /**
   * Deskripsi: 
   * Menampilkan pilihan tingkat kesulitan (Easy, Normal, Hard) dan meminta input dari pengguna.
   * Input akan terus diminta hingga valid (1, 2, atau 3).
   *
   * IS: Menampilkan pilihan kesulitan dan menerima input.
   * FS: Mengembalikan tingkat kesulitan yang dipilih (1, 2, atau 3).
   */
  printf("1. Easy\n2. Normal\n3. Hard\n");
  int selected;
  getchar();
  printf("Pilih Difficulty (1/2/3)");
  scanf("%d", &selected);
  while ((selected != 1) && (selected != 2) && (selected != 3)) {
    printf("Difficulty tidak ada\n");
    scanf("%d", &selected);
  }
  return selected;
}



#endif
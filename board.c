#ifndef board_c
#define board_c
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// #include <string.h>
#include "types.h"
// #include <stdlib.h>

void getLadderSnakeCount(int *ladderCount, int *snakeCount, int difficulty);
void searchPlayer(Player playerArray[], int playerCount, int blockNum,
                  int playerHere[], int *playerHereCount);
int compareAscending(const void *a, const void *b);
int compareDescending(const void *a, const void *b);
void printPlayerIcons(int playerNum, char colors[][7], int colorCount, bool isComputer);
void initiateBoard(int snakeCount, int ladderCount, Snake S[], Ladder L[]);
void initiateLadders(int numLadders, int grid, int occupied[],
                     int *occupiedCount, Ladder arr[]);
void initiateSnakes(int numSnakes, int grid, int occupied[], int *occupiedCount,
                    Snake arr[]);

int searchNumber(int arr[], int size, int num);
int searchNumber2DReturnRow(int arr[][2], int col, int row, int num);

void printBoard(Snake S[], Ladder L[], Player playerArray[],
                        int snakeCount, int ladderCount, int playerCount,
                        int grid);

void printBoardVSComputer(Snake S[], Ladder L[], Player playerArray[],
                          int snakeCount, int ladderCount, int playerCount,
                          int grid);

////////////////////////////////////////////////////////////////////////////////////////////////////////////

void printBoard(Snake S[], Ladder L[], Player playerArray[],
                        int snakeCount, int ladderCount, int playerCount,
                        int grid) {
  /**
   * printBoard - Menampilkan papan permainan ular tangga.
   *
   * Menampilkan grid papan permainan dengan ular, tangga, pemain, dan nomor
   * kotak. Posisi ular/tangga ditandai "S" atau "L" diikuti nomor, pemain
   * ditampilkan dengan ikon berwarna, dan nomor kotak ditampilkan dalam pola
   * zig-zag.
   *
   * Parameter:
   * @S, @L         : Array ular dan tangga.
   * @playerArray   : Array pemain.
   * @snakeCount    : Jumlah ular.
   * @ladderCount   : Jumlah tangga.
   * @playerCount   : Jumlah pemain.
   * @grid          : Ukuran grid papan (n x n).
   */
  int gridNum = grid * grid;
  for (int i = 0; i < grid; i++) {
    for (int j = 0; j < grid; j++) {
      printf("---------");
    }
    printf("\n");
    for (int j = 0; j < grid; j++) {
      int sum;
      if (i % 2 == 0) {
        sum = gridNum - j;
      } else {
        sum = gridNum - grid + 1 + j;
      }

      int ladderNum = searchNumber2DReturnRow(L, 2, ladderCount, sum);
      int snakeNum = searchNumber2DReturnRow(S, 2, snakeCount, sum);
      if (ladderNum != -1) {
        printf("L%d      |", ladderNum + 1);
      } else if (snakeNum != -1) {
        printf("S%d      |", snakeNum + 1);
      } else {
        printf("        |");
      }
    }
    printf("\n");
    for (int j = 0; j < grid; j++) {
      int sum;
      if (i % 2 == 0) {
        sum = gridNum - j;
      } else {
        sum = gridNum - grid + 1 + j;
      }
      char colors[4][7] = {"\033[31m", "\033[34m", "\033[32m", "\033[33m"};
      int playerHere[playerCount];
      int playerHereCount = 0;
      searchPlayer(playerArray, playerCount, sum, playerHere, &playerHereCount);
      if (playerHereCount == 4) {
        printf("  ");

        for (int k = 0; k < playerHereCount; k++) {
          printPlayerIcons(playerHere[k], colors, 4, playerArray[playerHere[k]].isComputer);
        }
        printf("  |");
      } else if (playerHereCount == 3) {
        printf("  ");

        for (int k = 0; k < playerHereCount; k++) {
          printPlayerIcons(playerHere[k], colors, 4, playerArray[playerHere[k]].isComputer);
        }
        printf("   |");
      } else if (playerHereCount == 2) {
        printf("   ");
        for (int k = 0; k < playerHereCount; k++) {
          printPlayerIcons(playerHere[k], colors, 4, playerArray[playerHere[k]].isComputer);
        }
        printf("   |");
      } else if (playerHereCount == 1) {
        printf("   ");
        for (int k = 0; k < playerHereCount; k++) {
          printPlayerIcons(playerHere[k], colors, 4, playerArray[playerHere[k]].isComputer);
        }
        printf("    |");
      } else {
        printf("        |");
      }
    }
    printf("\n");
    for (int j = 0; j < grid; j++) {
      int sum;
      if (i % 2 == 0) {
        sum = gridNum - j;
      } else {
        sum = gridNum - grid + 1 + j;
      }

      if (sum > 99) {
        printf("%d     |", sum);
      } else if (sum > 9) {
        printf("%d      |", sum);
      } else {
        printf("%d       |", sum);
      }
    }

    printf("\n");
    gridNum -= grid;
  }
  for (int j = 0; j < grid; j++) {
    printf("---------");
  }
  printf("\n");
}

void printBlock0(Player playerArray[], int playerCount) {
  /**
   * printBlock0 - Menampilkan pemain yang berada di blok 0 (luar papan).
   *
   * Fungsi ini mencetak informasi pemain yang belum memasuki papan permainan.
   * Pemain ditampilkan dengan ikon berwarna sesuai ID masing-masing.
   *
   * Parameter:
   * @playerArray   : Array pemain.
   * @playerCount   : Jumlah pemain dalam permainan.
   */
  char colors[4][7] = {"\033[31m", "\033[34m", "\033[32m", "\033[33m"};
  int playerHere[playerCount];
  int playerHereCount = 0;
  searchPlayer(playerArray, playerCount, 0, playerHere, &playerHereCount);
  if (playerHereCount > 0) {
    printf("Block 0 (Luar papan)\n");
    printf("---------\n");
    printf("        |\n");

    if (playerHereCount == 4) {
      printf("  ");

      for (int k = 0; k < playerHereCount; k++) {
        printPlayerIcons(playerHere[k], colors, 4, playerArray[playerHere[k]].isComputer);
      }
      printf("  |");
    } else if (playerHereCount == 3) {
      printf("  ");

      for (int k = 0; k < playerHereCount; k++) {
        printPlayerIcons(playerHere[k], colors, 4, playerArray[playerHere[k]].isComputer);
      }
      printf("   |");
    } else if (playerHereCount == 2) {
      printf("   ");
      for (int k = 0; k < playerHereCount; k++) {
        printPlayerIcons(playerHere[k], colors, 4, playerArray[playerHere[k]].isComputer);
      }
      printf("   |");
    } else if (playerHereCount == 1) {
      printf("   ");
      for (int k = 0; k < playerHereCount; k++) {
        printPlayerIcons(playerHere[k], colors, 4, playerArray[playerHere[k]].isComputer);
      }
      printf("    |");
    }
    printf("\n        |\n");
    printf("---------\n");
  }
}

void initiateBoard(int snakeCount, int ladderCount, Snake S[], Ladder L[]) {
  /**
   * initiateBoard - Menginisialisasi papan permainan dengan ular dan tangga.
   *
   * Fungsi ini secara acak menentukan posisi ular dan tangga pada papan
   * permainan, memastikan tidak ada konflik posisi antara ular dan tangga.
   *
   * Parameter:
   * @snakeCount    : Jumlah ular.
   * @ladderCount   : Jumlah tangga.
   * @S             : Array untuk menyimpan data ular.
   * @L             : Array untuk menyimpan data tangga.
   */

  srand(time(0));
  int n = 10;
  int occupied[(ladderCount + snakeCount) * 2];
  int occupiedCount = 0;
  initiateLadders(ladderCount, n, occupied, &occupiedCount, L);
  initiateSnakes(snakeCount, n, occupied, &occupiedCount, S);
}

void initiateLadders(int numLadders, int grid, int occupied[],
                     int *occupiedCount, Ladder arr[]) {
  /**
   * initiateLadders - Menginisialisasi posisi tangga pada papan permainan.
   *
   * Fungsi ini menentukan posisi awal dan akhir tangga secara acak pada papan,
   * memastikan setiap posisi tangga tidak bertabrakan dengan posisi lain yang
   * sudah ditempati (ular atau tangga lain).
   *
   * Parameter:
   * @numLadders     : Jumlah tangga yang akan diinisialisasi.
   * @grid           : Ukuran grid papan (n x n).
   * @occupied       : Array yang menyimpan posisi yang sudah ditempati.
   * @occupiedCount  : Pointer ke jumlah posisi yang sudah ditempati.
   * @arr            : Array untuk menyimpan posisi awal dan akhir tangga.
   */

  for (int i = 0; i < numLadders; i++) {
    int j = 0;
    while (j < 2) {
      int max = grid * grid - 1;
      int min = 2;
      int block = rand() % (max - min + 1) + min;
      if (searchNumber(occupied, *occupiedCount, block) == -1) {
        arr[i][j] = block;
        occupied[*occupiedCount] = block;
        (*occupiedCount)++;
        j++;
      }
    }
    qsort(arr[i], 2, sizeof(arr[i][0]), compareAscending);
  }
}

int searchNumber(int arr[], int size, int num) {
  /**
   * searchNumber - Mencari angka dalam array.
   *
   * Fungsi ini memeriksa apakah sebuah angka terdapat dalam array tertentu
   * dan mengembalikan indeksnya jika ditemukan, atau -1 jika tidak ditemukan.
   *
   * Parameter:
   * @arr   : Array yang akan dicari.
   * @size  : Ukuran array.
   * @num   : Angka yang akan dicari.
   *
   * Return:
   * Indeks angka dalam array jika ditemukan, -1 jika tidak ditemukan.
   */

  for (int i = 0; i < size; i++) {
    if (num == arr[i]) {
      return i;
    }
  }
  return -1;
}

int searchNumber2DReturnRow(int arr[][2], int col, int row, int num) {
  /**
   * searchNumber2DReturnRow - Mencari angka dalam array 2D.
   *
   * Fungsi ini memeriksa apakah sebuah angka terdapat dalam array 2D tertentu
   * dan mengembalikan indeks BARIS tempat angka ditemukan, atau -1 jika tidak
   * ditemukan.
   *
   * Parameter:
   * @arr   : Array 2D yang akan dicari.
   * @col   : Jumlah kolom dalam array.
   * @row   : Jumlah baris dalam array.
   * @num   : Angka yang akan dicari.
   *
   * Return:
   * Indeks baris dalam array 2D jika angka ditemukan, -1 jika tidak ditemukan.
   */

  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      if (num == arr[i][j]) {
        return i;
      }
    }
  }
  return -1;
}

void initiateSnakes(int numSnakes, int grid, int occupied[], int *occupiedCount,
                    Snake arr[]) {
  /**
   * initiateSnakes - Menginisialisasi posisi ular pada papan permainan.
   *
   * Fungsi ini menentukan posisi kepala dan ekor ular secara acak pada papan,
   * memastikan setiap posisi tidak bertabrakan dengan posisi lain yang sudah
   * ditempati (ular atau tangga). Posisi kepala ular selalu lebih besar dari
   * ekornya.
   *
   * Parameter:
   * @numSnakes      : Jumlah ular yang akan diinisialisasi.
   * @grid           : Ukuran grid papan (n x n).
   * @occupied       : Array yang menyimpan posisi yang sudah ditempati.
   * @occupiedCount  : Pointer ke jumlah posisi yang sudah ditempati.
   * @arr            : Array untuk menyimpan posisi kepala dan ekor ular.
   */

  for (int i = 0; i < numSnakes; i++) {
    int j = 0;
    while (j < 2) {
      int max = grid * grid - 1;
      int min = 2;
      int block = rand() % (max - min + 1) + min;
      if (searchNumber(occupied, *occupiedCount, block) == -1) {
        arr[i][j] = block;
        occupied[*occupiedCount] = block;
        (*occupiedCount)++;
        j++;
      }
    }
    qsort(arr[i], 2, sizeof(arr[i][0]), compareDescending);
  }
}

int compareAscending(const void *a, const void *b) {
  /**
   * compareAscending - Fungsi pembanding untuk urutan menaik.
   *
   * Fungsi ini digunakan untuk membandingkan dua elemen bertipe integer dalam
   * urutan menaik, digunakan dalam fungsi `qsort` dari stdlib.h.
   *
   * Parameter:
   * @a   : Pointer ke elemen pertama yang akan dibandingkan.
   * @b   : Pointer ke elemen kedua yang akan dibandingkan.
   *
   * Return:
   * Nilai negatif jika a < b, nol jika a == b, atau nilai positif jika a > b.
   */

  return (*(int *)a - *(int *)b);
}

int compareDescending(const void *a, const void *b) {
  /**
   * compareDescending - Fungsi pembanding untuk urutan menurun.
   *
   * Fungsi ini digunakan untuk membandingkan dua elemen bertipe integer dalam
   * urutan menurun, digunakan dalam fungsi `qsort` dari stdlib.h.
   *
   * Parameter:
   * @a   : Pointer ke elemen pertama yang akan dibandingkan.
   * @b   : Pointer ke elemen kedua yang akan dibandingkan.
   *
   * Return:
   * Nilai negatif jika a > b, nol jika a == b, atau nilai positif jika a < b.
   */

  return (*(int *)b - *(int *)a);
}

void initiatePlayers(Player playerArray[], int playerCount) {
  /**
   * initiatePlayers - Menginisialisasi data pemain.
   *
   * Fungsi ini meminta input nama untuk setiap pemain, menginisialisasi posisi
   * pemain ke 0, dan menyimpannya dalam array pemain.
   *
   * Parameter:
   * @playerArray : Array untuk menyimpan data pemain.
   * @playerCount : Jumlah pemain yang akan diinisialisasi.
   */

  for (int i = 0; i < playerCount; i++) {
    printf("Nama player ke-%d (jangan pakai spasi :3): ", i + 1);
    getchar();
    scanf("%s", playerArray[i].name);
    playerArray[i].position = 0;
    playerArray[i].isComputer = false;
    playerArray[i].isPlaying = true;
    playerArray[i].isWin = false;
    playerArray[i].rankPlayer = -1;

  }
}

void resetColor() {
  /**
     * Mengembalikan warna teks ke default.
     */
  printf("\033[0m");
}

void printPlayerIcons(int playerNum, char colors[][7], int colorCount, bool isComputer) {
  /**
   * printPlayerIcons - Menampilkan ikon pemain berdasarkan nomor pemain.
   *
   * Fungsi ini mencetak simbol "P" dengan warna yang sesuai untuk setiap pemain
   * berdasarkan nomor pemain yang diberikan.
   *
   * Parameter:
   * @playerNum   : Nomor pemain yang akan ditampilkan.
   * @colors      : Array warna untuk ikon pemain.
   * @colorCount  : Jumlah warna yang tersedia untuk pemain.
   */

  for (int i = 0; i < colorCount; i++) {
    if (i == playerNum) {
      if (isComputer) {
        printf("%sC", colors[i]);
        resetColor();
      } else {
        printf("%sP", colors[i]);
        resetColor();
      }
      
    }
  }
}



void printPlayers(Player playerArray[], int playerCount, char colors[][7],
                  int colorCount) {
  /**
   * printPlayers - Menampilkan daftar pemain dengan ikon dan nama.
   *
   * Fungsi ini mencetak nama setiap pemain bersama dengan ikon warna yang
   * sesuai, berdasarkan urutan pemain yang ada dalam array pemain.
   *
   * Parameter:
   * @playerArray : Array yang menyimpan data pemain.
   * @playerCount : Jumlah pemain yang akan ditampilkan.
   * @colors      : Array warna untuk ikon pemain.
   * @colorCount  : Jumlah warna yang tersedia untuk pemain.
   */

  for (int i = 0; i < playerCount; i++) {
    printPlayerIcons(i, colors, colorCount, playerArray[i].isComputer);
    printf(": %s\n", playerArray[i].name);
  }
  printf("\n");
}

void getLadderSnakeCount(int *ladderCount, int *snakeCount, int difficulty) {
  /**
   * getLadderSnakeCount - Mengatur jumlah tangga dan ular berdasarkan tingkat
   * kesulitan.
   *
   * Fungsi ini mengubah nilai jumlah tangga dan ular berdasarkan tingkat
   * kesulitan permainan. Tingkat kesulitan yang lebih tinggi akan mengurangi
   * jumlah tangga dan meningkatkan jumlah ular.
   *
   * Parameter:
   * @ladderCount : Pointer yang akan diubah untuk menyimpan jumlah tangga.
   * @snakeCount  : Pointer yang akan diubah untuk menyimpan jumlah ular.
   * @difficulty  : Tingkat kesulitan permainan (1, 2, atau 3).
   */

  if (difficulty == 1) {
    *ladderCount = 7;
    *snakeCount = 3;
  } else if (difficulty == 2) {
    *ladderCount = 5;
    *snakeCount = 5;
  } else if (difficulty == 3) {
    *ladderCount = 3;
    *snakeCount = 7;
  }
}

void searchPlayer(Player playerArray[], int playerCount, int blockNum,
                  int playerHere[], int *playerHereCount) {
  /**
   * searchPlayer - Mencari pemain yang berada di blok tertentu.
   *
   * Fungsi ini mencari pemain yang posisinya sama dengan nomor blok yang
   * diberikan, dan menyimpan indeks pemain yang ditemukan dalam array
   * `playerHere`.
   *
   * Parameter:
   * @playerArray     : Array yang menyimpan data pemain.
   * @playerCount     : Jumlah pemain yang ada.
   * @blockNum        : Nomor blok yang dicari.
   * @playerHere      : Array yang akan diisi dengan indeks pemain yang berada
   * di blok tersebut.
   * @playerHereCount : Pointer yang akan diubah untuk menyimpan jumlah pemain
   * yang berada di blok tersebut.
   */

  *playerHereCount = 0;
  for (int i = 0; i < playerCount; i++) {
    if (blockNum == playerArray[i].position) {
      playerHere[*playerHereCount] = i;
      *playerHereCount += 1;
    }
  }
}

#endif
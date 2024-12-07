#ifndef game_c
#define game_c
#include "board.c"
#include "types.h"
#include <conio.h>
#include <string.h>
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

void infoRule();

void infoDifficulty();

void infoMode();


void introScreen() {
    /**
   * Deskripsi :
   *  Menampilkan tampilan awal permainan
   * IS:
   * Layar belum menampilkan apa apa
   * FS:
   * Layar menampilkan tampilan awal permainan
 */

    printf("===========================================\n");
    printf("     WELCOME TO SNAKES AND LADDERS!        \n");
    printf("===========================================\n");


      printf("\n");
      printf("Menu:\n");
      printf("1. New Game\n");
      printf("2. High Score\n");
      printf("3. Exit\n");
      printf("4. Continue Previous Game\n");
      printf("5. See Rules\n");
      printf("\nPilih menu (1/2/3/4/5): ");
}



int rollDice(int difficulty) {
  /**
   * Deskripsi :
   *  Mengocok dadu untuk menentukan langkah player
   * IS:
   * Dadu masih belum ada
   * FS:
   * Dadu telah dikocok berdasarkan difficulty
 */
  int min = 1;
  int max = 6;
  return (rand() % (max - min + 1) + min);
}

void checkWin(Player *player, int players, int *winnerCount) {
    /**
   * Deskripsi :
   *  Menentukan apakah Player mememenangkan permainan atau tidak. Jika player berada pada posisi 100
   *  Player memenangkan permainan
   * IS:
   * Nilai subvar isWin dari player masih belum ditentukan
   * FS:
   * Nilai subvar isWin dari player telah ditentukan
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
   *  Mengecek apakah Player kalah dalam permainan atau tidak
   * IS:
   * Score pemain masih belum berubah
   * FS:
   * Score pemain berubah jika isWin bernilai false
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
   *  Menentukan peringkat player
   * IS:
   * Rank seluruh pemain masih belum terisi
   * FS:
   * Rank pemain menjadi 0
   *  
 */
  (*player).rankPlayer = winnerCount;
}

void printRank(Player playerArray[], int players) {
  /**
   * Deskripsi :
   *  Menampilkan peringkat seluruh Player
   * IS:
   * Layar belum menampilkan apa apa
   * FS:
   * Layar menampilkan peringkat seluruh Player
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
   *  User menentukan suatu player manusia atau computer
   * IS:
   * Subvar isComputer masih belum terisi
   * FS:
   * Subvar isComputer telah terisi apakah Player manusia atau computer
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
   *  Mengecek apakah Player mendapatkan angka pada pengocokan dadu
   * IS:
   * Layar tidak menampilkan apa apa
   * FS:
   * Layer menampilkan Player mendapatkan angka 6, dan akan mendapatkan giliran lagi
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
   *  
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
   * Procedure untuk player berpindah ke kotak selanjutnya berdasarkan n diambil dari pengocokan dadu.
   * Player wajib mendapatkan nilai n=1 untuk mulai bergerak dari papan
   * IS:
   * Layar tidak menampilkan apa apa, posisi player masih belum berubah, score masih belum berubah
   * , position masih belum berubah.
   * FS:
   * Layar menampilkan Player berpindah ke kotak selanjutnya berdasarkan n, posisi player berubah, score berubah
   * dan position berubah
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
   *  Procedure mengubah seluruh nilai subvar score menjadi 
   * IS:
   * Subvar score pada struct Player masih belum terisi
   * FS:
   * Subvar score pada struct Player telah terisi senilai newScore
 */
  for (int i = 0; i < size; i++) {
    players[i].score = newScore;
  }
}

int score(Player *player) {
      /**
   * Deskripsi :
   *  Fungsi player mengembalikan skor player dengan kalkulasi score - 1
   * IS:
   * Score player masih belum berubah
   * FS:
   * Score Player telah berubah, berkurang 1
 */
  return (*player).score - ((*player).position * 0.01);
}


void printScore(Player *playerArray, int players) {
      /**
   * Deskripsi :
   * Procedure menampilkan seluruh score setiap player
   * IS:
   * Layar belum menampilkan apa apa
   * FS:
   * Layar menampilkan score seluruh player
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
   *  Menulis output dari data nama player, rank, dan score ke file output.txt 
   * IS:
   * File output.txt belum menampilkan apa apa 
   * FS:
   * File output.txt menampilkan nama player, rank, dan score
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

  printf("Data disimpan di 'output.txt'.\n");
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
   * Menentukan posisi player berdasarkan n
   * IS:
   * Nilai subvar position masih belum berubah
   * FS:
   * Nilai subvar position telah berubah sesuai n
 */
   (*player).position = n; 
}

bool timer(int difficulty, Player *player) {
  /**
   * Deskripsi :
   *  Fungsi ini mengembalikan nilai boolean true/false.
   *  Fungsi ini digunakan untuk menampilkan timer pada permainan
   * IS:
   *  Layar belum menampilkan apa apa
   * FS:
   *  Layar menampilkan waktu hitung mundur dalam permainan, jika tombol spasi ditekan maka waktu akan berhenti
   *  dan mengembalikan nila boolean true
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
   *  Memeriksa apakah Player adalah manusia atau computer, jika computer maka diubah menjadi (Computer)
   * IS:
   * Layar belum menampilkan apa apa
   * FS:
   * Layar menampilkan tambahan (Computer) pada player computer
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
   * Function ini menerima input dari user untuk memilih mode permainan
   * IS:
   * Nilai integer mode masih belum ditentukan
   * FS:
   * Nilai integer mode telah ditentukan
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
   * Menentukan seberapa banyak player yang akan bermain, sesuai input user
   * IS:
   * Berapa banyak player belum ditentukan
   * FS:
   * Berapa banyak player telah ditentukan
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
   * Menampilkan Player yang telah jadi pemenang
   * IS:
   * Layar belum menampilkan apa apa
   * FS:
   * Layar menampilkan Player yang telah jadi pemenang
 */
  for (int i = 0; i<winnerCount; i++) {
    printf("%d",WinnerArray[i]);
  }
}

void instruction(Player *playerArray) {
  /**
   * Deskripsi :
   * Memberi instruksi kepada User agar lebih mudah menjalankan permainan
   * IS:
   * Layar belum menampilkan apa apa
   * FS:
   * Layar menampilkan intruksi
 */
    printf("=== Permainan Ular Tangga ===\n");
    printf("Instruksi:\n");
    printf("- Tekan [Spasi] untuk giliran selanjutnya (lempar dadu).\n");
    printf("- Tekan [W] untuk menyerah dan keluar tanpa menyimpan.\n");
    printf("- Tekan [S] untuk keluar dan menyimpan permainan.\n");
    printf("- Tekan [Q] untuk keluar dan menyelesaikan permainan tanpa menyimpan.\n");
    printf("Player dengan nama %s berada di Posisi: %d\n", (*playerArray).name,  (*playerArray).position);
}

void infoRule() {
  /**
   * Deskripsi :
   * Menampilkan aturan permainan Ular Tangga
   * IS:
   * Layar belum menampilkan apa apa
   * FS:
   * Layar menampilkan aturan permainan
 */
    printf("\n=== Permainan Ular Tangga ===\n");
    printf("===========================================\n");
    printf("|               ATURAN PERMAINAN          |\n");
    printf("===========================================\n");
    printf("| 1. Setiap player akan diberi base score |\n");
    printf("|    116.                                 |\n");
    printf("| 2. Score player akan terus berkurang 1  |\n");
    printf("|    setiap giliran.                      |\n");
    printf("| 3. Setiap player/computer akan mengocok |\n");
    printf("|    dadu sebelum bergerak.               |\n");
    printf("| 4. Player akan bergerak hanya jika      |\n");
    printf("|    player/computer mendapatkan angka 1. |\n");
    printf("| 5. Setiap player akan mengocok dadu     |\n");
    printf("|    sebelum bergerak setiap giliran.     |\n");
    printf("| 6. Pengocokan dadu akan diberi timer    |\n");
    printf("|    jika Player adalah pemain asli.      |\n");
    printf("| 7. Jika Player tidak mengocok dadu      |\n");
    printf("|    hingga timer habis, maka akan        |\n");
    printf("|    berpindah ke giliran selanjutnya.    |\n");
    printf("| 8. Score setiap player akan tetap       |\n");
    printf("|    berkurang jika player tidak mengocok |\n");
    printf("|    dadu hingga timer habis.             |\n");
    printf("| 9. Computer tidak akan diberi timer.    |\n");
    printf("| 10. Player akan bergerak sesuai dengan  |\n");
    printf("|     angka dadu setelah mengocok.        |\n");
    printf("| 11. Jika player mendapat angka 6,       |\n");
    printf("|     player akan mendapatkan giliran     |\n");
    printf("|     lagi.                               |\n");
    printf("| 12. Jika player menginjak tangga atau L,|\n");
    printf("|     maka player akan naik tangga.       |\n");
    printf("| 13. Jika player menginjak ular, maka    |\n");
    printf("|     player akan turun ke ekor ular.     |\n");
    printf("| 14. Jika player menginjak player lain,  |\n");
    printf("|     maka player yang terinjak akan      |\n");
    printf("|     kembali ke kotak 0 (hanya di        |\n");
    printf("|     difficulty hard).                   |\n");
    printf("| 15. Player yang mencapai kotak 100      |\n");
    printf("|     akan menang.                        |\n");
    printf("===========================================\n");
    printf("===         Permainan Ular Tangga       ===\n");
    printf("===========================================\n");
  printf("Tekan [spasi] untuk mulai permainan\n");
}

void infoMode() {
  /**
   * Deskripsi :
   * Menampilkan informasi mode permainan Ular Tangga
   * IS:
   * Layar belum menampilkan apa apa
   * FS:
   * Layar menampilkan informasi mode permainan
 */
    printf("===========================================\n");
    printf("|             PERBEDAAN MODE              |\n");
    printf("===========================================\n");
    printf("| 1. Mode Normal (Fair) :                 |\n");
    printf("|    - Seperti permainan ular tangga      |\n");
    printf("|      pada umumnya.                      |\n");
    printf("|                                         |\n");
    printf("| 2. Mode Rigged :                        |\n");
    printf("|    - Player memiliki chance 50/50 jika  |\n");
    printf("|      mendekati tangga di mode easy.     |\n");
    printf("|    - Player memiliki chance 50/50 jika  |\n");
    printf("|      mendekati ular di mode hard.       |\n");
    printf("|    - Computer memiliki chance 50/50     |\n");
    printf("|      jika mendekati ular di mode easy.  |\n");
    printf("|    - Computer memiliki chance 50/50     |\n");
    printf("|      jika mendekati tangga di mode hard.|\n");
    printf("===========================================\n");
    printf("|             PERBEDAAN MODE              |\n");
    printf("===========================================\n");
}

void infoDifficulty() {
  /**
   * Deskripsi :
   * Menampilkan informasi difficulty permainan Ular Tangga
   * IS:
   * Layar belum menampilkan apa apa
   * FS:
   * Layar menampilkan informasi difficulty permainan
 */

    printf("===========================================\n");
    printf("|         PERBEDAAN DIFFICULTY            |\n");
    printf("===========================================\n");
    printf("| 1. Easy :                               |\n");
    printf("|    - Setiap player diberi waktu kocok   |\n");
    printf("|      dadu 10 detik.                     |\n");
    printf("|    - Peluang player mendekati tangga    |\n");
    printf("|      lebih besar.                       |\n");
    printf("|    - Peluang computer mendekati ular    |\n");
    printf("|      lebih besar.                       |\n");
    printf("|                                         |\n");
    printf("| 2. Normal :                             |\n");
    printf("|    - Setiap player diberi waktu kocok   |\n");
    printf("|      dadu 5 detik.                      |\n");
    printf("|                                         |\n");
    printf("| 3. Hard :                               |\n");
    printf("|    - Setiap player diberi waktu kocok   |\n");
    printf("|      dadu 3 detik.                      |\n");
    printf("|    - Jika player menginjak player lain, |\n");
    printf("|      maka player yang terinjak akan     |\n");
    printf("|      kembali ke kotak 0.                |\n");
    printf("|    - Peluang player mendekati ular      |\n");
    printf("|      lebih besar.                       |\n");
    printf("|    - Peluang computer mendekati ular    |\n");
    printf("|      lebih kecil.                       |\n");
    printf("===========================================\n");
    printf("|         PERBEDAAN DIFFICULTY            |\n");
    printf("===========================================\n");


}



#endif
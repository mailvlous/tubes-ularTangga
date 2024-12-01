#ifndef game_c
#define game_c
#include "board.c"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void move(int n, Player *player, int grid);

int score(Player *player, int minus, int baseScore);
void setPosition(int n, Player *player);
int rollDice(int difficulty);
int rollDiceRigged(int difficulty, int nearestLadder, int nearestSnake);
bool timer();
int checkNearestLadder(Ladder L[], int ladderCount, Player player);

void checkLadderSnake(Player *player, Ladder L[], Snake S[], int ladderCount,
                      int snakeCount);
int checkNearestSnake(Snake S[], int snakeCount, Player player);
int checkWin(Player player, Player Winners[]);

int rollDice(int difficulty) {
  int min = 1;
  int max = 6;

  if (difficulty == 1) {
    return (rand() % (6 - 4 + 1) + min);
  } else if (difficulty == 2) {
    return (rand() % (max - min + 1) + min);
  } else if (difficulty == 3) {
    return (rand() % (3 - 1 + 1) + min);
  }

}

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

int checkNearestLadder(Ladder L[], int ladderCount, Player player) {
  for (int i = player.position + 1; i <= player.position + 6; i++) {
    for (int j = 0; j < ladderCount; j++) {
      if (i == L[i][0]) {
        return i;
      }
    }
  }
  return -1;
}

int checkNearestSnake(Snake S[], int snakeCount, Player player) {
  for (int i = player.position + 1; i <= player.position + 6; i++) {
    for (int j = 0; j < snakeCount; j++) {
      if (i == S[i][0]) {
        return i;
      }
    }
  }
  return -1;
}

void move(int n, Player *player, int grid) {
  int max = grid * grid;
  (*player).position += n;
  if ((*player).position > max) {
    (*player).position = max - (*player).position + max;
  }
}

int score(Player *player, int minus, int baseScore) {
  int score;
  baseScore = (*player).score;

  (*player).score -= minus; // Kurangi skor pemain
  score = (*player).score;
  return score;
  // for (int i = 0; i < 100; i++) {
  //   (*player).score = baseScore - minus;
  //   score = (*player).score;
  //   return score;
  // }

}

void printScore(int score) {
  printf("Score: %d\n", score);
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

  printf("Seconds: ");

  while (seconds > 0) {


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

#endif
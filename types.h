#ifndef types_h
#define types_h
#include <stdbool.h>

typedef struct {
  char name[50];
  int position;
  int score;
  bool isPlaying;
  bool isComputer;
} Player;

// typedef struct {
//   char name[50];
//   int position;
// } Computer;

typedef int Ladder[2];
typedef int Snake[2];
// typedef char Color[7];
#endif
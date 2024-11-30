#ifndef types_h
#define types_h
typedef struct {
  char name[50];
  int position;
  int score;
  int type;
} Player;

typedef struct {
  char name[50];
  int position;
} Computer;

typedef int Ladder[2];
typedef int Snake[2];
// typedef char Color[7];
#endif
#ifndef highscore_c
#define highscore_c
#include "board.c"
#include "types.h"
#include <conio.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    int highScore;
} User;

void loadScores(User users[], int *count) {
     /**
     * Deskripsi:
     * Prosedur untuk memuat data skor tertinggi pengguna dari file "user.txt".
     * Mengisi array `users` dan memperbarui jumlah pengguna yang dimuat ke dalam `count`.
     *
     * IS: Membuka file "user.txt" dan membaca nama serta skor pengguna.
     * FS: Array `users` diisi dengan data pengguna dan `count` diperbarui sesuai jumlah pengguna.
     */
    FILE *file = fopen("user.txt", "r");
    if (!file) {
        *count = 0;
        return;
    }
    *count = 0;
    while (fscanf(file, "%s %d", users[*count].name, &users[*count].highScore) == 2) {
        (*count)++;
    }
    fclose(file);
}

void updateHighScore(User users[], int *userCount, char name[], int newScore) {
    /**
     * Deskripsi:
     * Prosedur untuk memperbarui skor tertinggi pengguna. Jika pengguna sudah ada,
     * dan skor baru lebih tinggi, maka skor akan diperbarui. Jika pengguna belum ada,
     * akan ditambahkan ke daftar dengan skor baru.
     *
     * IS: Daftar pengguna (users[]) dengan jumlah pengguna (userCount) yang diketahui, dan setiap pengguna memiliki nama dan skor tertinggi masing-masing.
     * FS: Skor tertinggi pengguna diperbarui atau pengguna baru ditambahkan ke daftar.
     */
    for (int i = 0; i < *userCount; i++) {
        if (strcmp(users[i].name, name) == 0) {
            if (newScore > users[i].highScore) {
                users[i].highScore = newScore;
            }
            return;
        }
    }
    strcpy(users[*userCount].name, name);
    users[*userCount].highScore = newScore;
    (*userCount)++;
}

void writeUsersToFile(User users[], int userCount) {
    /**
     * Deskripsi:
     * Procedure ini untuk menulis daftar pengguna beserta skor tertingginya ke dalam file.
     *
     * IS: Data pengguna dan skor tertingginya tersedia dalam array `users`, jumlah user di userCount.
     * FS: File "user.txt" akan berisi nama pengguna dan skor tertingginya.
     */
    FILE *file = fopen("user.txt", "w");
    if (file == NULL) {
        printf("Error opening file");
        return;
    }
    for (int i = 0; i < userCount; i++) {
        fprintf(file, "%s %d\n", users[i].name, users[i].highScore);
    }
    fclose(file);
}

void displayScores(User users[], int count) {
    /**
     * Deskripsi:
     *Prosedur ini menampilkan daftar skor tertinggi dari pengguna ke layar.
     *
     * IS: Daftar pengguna dengan skor tertinggi tersedia dalam array `users`, jumlah user ada di userCount.
     * FS: Menampilkan nama pengguna beserta skor tertinggi mereka.
     */
    printf("High Scores:\n");
    printf("------------\n");
    for (int i = 0; i < count; i++) {
        printf("%s: %d\n", users[i].name, users[i].highScore);
    }
    printf("------------\n");
}

void saveHighScoreFromPlayer(Player playerArray[], int playerCount) {
    /**
     * Deskripsi:
     * Memperbarui atau menambahkan skor tertinggi pemain ke dalam file.
     *
     * IS: Daftar pengguna (users[]) dengan skor tertinggi yang sudah ada dan jumlah pengguna (count). Data pemain (playerArray[]) dengan skor yang ingin diperbarui.
     * FS: Skor diperbarui atau pemain baru ditambahkan ke daftar, disimpan di suatu file.
     */
    User users[100];
    int count = 0;
    loadScores(users, &count);
    for (int i = 0; i < playerCount; i++) {
        char newName[50];
        strcpy(newName, playerArray[i].name);
        int newScore = playerArray[i].score;
        updateHighScore(users, &count, newName, newScore);
    }
    writeUsersToFile(users, count);
}

#endif
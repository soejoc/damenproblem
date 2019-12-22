#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "main.h"

#define ROW_SIZE 8
#define COLUMN_SIZE 8

int main() {
    printf("Anzahl der Lösungen: %d", damenproblem(ROW_SIZE, COLUMN_SIZE));
    return 0;
}

int damenproblem(int nRowSize, int nColumnSize) {
    struct Vector2D * vDame = malloc(sizeof(struct Vector2D) * nColumnSize);
    int nCounter;

    setze(1, vDame, nColumnSize, nRowSize, &nCounter);

    free(vDame);

    return nCounter;
}

void setze(int nDameNumber, struct Vector2D vDame[], int nColumnSize, int nRowSize, int * pCount) {
    vDame[nDameNumber - 1].x = 0;
    vDame[nDameNumber - 1].y = nDameNumber - 1;

    for(int i = 0; i < nColumnSize; ++i, ++vDame[nDameNumber - 1].x) {
        if(!bedroht(&vDame[nDameNumber - 1], vDame, nDameNumber - 1, nRowSize)) {
            if(nDameNumber == nColumnSize) {
                ++(*pCount);
                ausgabe(vDame, nRowSize, nColumnSize);
            }
            else
                setze(nDameNumber + 1, vDame, nColumnSize, nRowSize, pCount);
        }
    }
}

int bedroht(const struct Vector2D * pDame, const struct Vector2D vDames[], int nDamesUntil, int nDameCount) {
    if(nDamesUntil == 0)
        return 0;

    if(isDameInSameRowOrColumn(pDame, vDames, nDamesUntil))
        return 1;

    // Check left to right diagonal

    struct Vector2D * vDamePosDiagonal = malloc(sizeof(struct Vector2D) * (nDamesUntil + 1));
    memcpy(vDamePosDiagonal, vDames, sizeof(struct Vector2D) * (nDamesUntil + 1));

    for(int i = 0; i < nDamesUntil + 1; ++i) {
        vDamePosDiagonal[i].y -= vDamePosDiagonal[i].x;
    }

    int nRet = 0;

    if(isDameInSameRowOrColumn(&vDamePosDiagonal[nDamesUntil], vDamePosDiagonal, nDamesUntil))
        nRet = 1;

    // Check right to left diagonal

    if(nRet == 0) {
        memcpy(vDamePosDiagonal, vDames, sizeof(struct Vector2D) * (nDamesUntil + 1));

        for (int i = 0; i < nDamesUntil + 1; ++i) {
            vDamePosDiagonal[i].y -= nDameCount - 1 - vDamePosDiagonal[i].x;
        }

        if (isDameInSameRowOrColumn(&vDamePosDiagonal[nDamesUntil], vDamePosDiagonal, nDamesUntil))
            nRet = 1;
    }

    free(vDamePosDiagonal);

    return nRet;
}

int isDameInSameRowOrColumn(const struct Vector2D * pDame, const struct Vector2D vDames[], int nDamesUntil) {
    for(int i = 0; i < nDamesUntil; ++i) {
        if(vDames[i].x == pDame->x || vDames[i].y == pDame->y)
            return 1;
    }

    return 0;
}

void ausgabe(const struct Vector2D vDames[], int nRowSize, int nColumnSize) {
    for(int x = 0; x < nRowSize; ++x) {
        printf("|");

        for (int y = 0; y < nColumnSize; ++y) {
            char next = ' ';

            for (int k = 0; k < nColumnSize; ++k) {
                if(vDames[k].x == x && vDames[k].y == y)
                    next = 'D';
            }

            printf("%c|", next);
        }

        printf("\n");
    }

    printf("\n\n");
}
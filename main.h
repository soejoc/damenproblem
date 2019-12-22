//
// Created by Sören Jochimsen on 21.12.2019.
//

#ifndef DAMENPROBLEM_MAIN_H
#define DAMENPROBLEM_MAIN_H

struct Vector2D {
    int x;
    int y;
};

int bedroht(const struct Vector2D * pDame, const struct Vector2D vDames[], int nDamesUntil, int nDameCount);
void ausgabe(const struct Vector2D vDames[], int nRowSize, int nColumnSize);
int isDameInSameRowOrColumn(const struct Vector2D * pDame, const struct Vector2D vDames[], int nDamesUntil);
void setze(int nDameNumber, struct Vector2D vDame[], int nColumnSize, int nRowSize, int * pCount);
int damenproblem(int nRowSize, int nColumnSize);

#endif //DAMENPROBLEM_MAIN_H

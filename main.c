#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "stopper.h"

#define N = 2;
#define M = 4;

typedef double *vektor;
typedef vektor *matrix;

vektor VektorAlloc(int n) {
    vektor v;
    if ((v = (vektor)malloc(n*sizeof(*v))) == NULL) {
        fprintf(stderr, "Nincs eleg memoria\n");
        exit (1);
    }
    return v;
}


matrix MatrixAlloc(int n, int m){
    matrix a;
    int i;
    if ((a = (matrix)malloc(n* sizeof(*a))) == NULL) {
        fprintf(stderr, "Nincs eleg memoria\n");
        exit (1);
    }
    for (i = 0; i<n; i++) {
        a[i] = VektorAlloc(m);
    }
    return a;
}

void matrixFree(matrix a, int n) {
    int i;
    for (i = 0; i < n; i++) {
        free(a[i]);
    }
    free(a);
}

void MatrixMatrixSzorzas(int n, matrix m1, matrix m2, matrix em) {
    int i,j,k;
    double s;

    for (i = 0; i<n; i++) {
        for (j = 0; j < n; j++) {
            s = 0.0;
            for (k = 0; k < n; k++) {
                s += m1[i][k]*m2[k][j];
            }
            em[i][j] = s;
        }
    }
}

int main() {
    stopper st;
    startS(&st);

    int n = 1024;

    matrix m1 = MatrixAlloc(n, n);
    matrix m2 = MatrixAlloc(n, n);
    matrix multiple = MatrixAlloc(n, n);
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            m1[i][j] = i + j + 1;
            m2[j][i] = i + j + 1;
        }
    }

    //printf("matrix m1 \n");
    //for (i = 0; i < n; i++) {
    //    for (j = 0; j < n; j++) {
    //        printf("%f  ", m1[i][j]);
     //   }
     //   printf("\n");
    //}

    //printf("matrix m2 \n");
    //for (i = 0; i < n; i++) {
     //   for (j = 0; j < n; j++) {
     //       printf("%f  ", m2[i][j]);
     //   }
     //   printf("\n");
    //}

    MatrixMatrixSzorzas(n, m1, m2, multiple);

    //printf("matrix multiple\n");
    //for (i = 0; i < n; i++) {
     //   for (j = 0; j < n; j++) {
     //       printf("%f  ", multiple[i][j]);
     //   }
     //   printf("\n");
    //}

    matrixFree(m1, n);
    matrixFree(m2, n);
    matrixFree(multiple, n);

    stopS(&st);
    tprintf(&st,"\n");

    return 0;
}
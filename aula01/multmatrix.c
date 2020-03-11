#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int height;
    int width;
    int **data;
} Matrix;

int **readMatrix(Matrix matrix) {
    int **mat = malloc(sizeof(int *) * matrix.height);
    for (int i = 0; i < matrix.height; i++) {
        mat[i] = malloc(sizeof(int) * matrix.width);
        for (int j = 0; j < matrix.width; j++) {
            scanf("%d", &mat[i][j]);
        }
    }

    return mat;
}

void printMatrix(Matrix matrix) {
    for (int i = 0; i < matrix.height; i++) {
        for (int j = 0; j < matrix.width; j++) {
            printf("%d ", matrix.data[i][j]);
        }
        printf("\n");
    }
}

void freeMatrix (Matrix matrix) {
    for (int i = 0; i < matrix.height; i++) {
        free(matrix.data[i]);
    }
    free(matrix.data);
}

Matrix multiplyMatrix(Matrix m1, Matrix m2) {
    if (m1.width != m2.height) {
        printf("Cannot multiply these matrices.\n");
        return (Matrix) {0, 0, NULL};
    }

    Matrix mR;
    mR.height = m1.height;
    mR.width = m2.width;

    int **mat = (int **) malloc(sizeof(int *) * mR.height);
    for (int i = 0; i < mR.height; i++) {
        mat[i] = (int *) calloc(mR.width, sizeof(int));

        for (int j = 0; j < mR.width; j++) {
            for (int k = 0; k < m1.width; k++) {
                mat[i][j] += m1.data[i][k] * m2.data[k][j];
            }
        }
    }

    mR.data = mat;
    return mR;
}

int main(int argc, char *argv[]){
    Matrix m1, m2, mR;

    scanf("%d %d %d %d", &m1.height, &m1.width, &m2.height, &m2.width);

    m1.data = readMatrix(m1);
    m2.data = readMatrix(m2);

    // only for tests
    // printMatrix(m1);
    // printMatrix(m2);

    mR = multiplyMatrix(m1, m2);
    printMatrix(mR);

    freeMatrix(m1);
    freeMatrix(m2);
    if (mR.data) {
        freeMatrix(mR);
    }

    return 0;
}

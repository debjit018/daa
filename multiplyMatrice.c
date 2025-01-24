#include <stdio.h>
#include <stdlib.h>

int** createMatrix(int rows, int cols) {
    int **matrix = (int**)malloc(rows * sizeof(int*));
    for(int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
    }
    return matrix;
}

void freeMatrix(int **matrix, int rows) {
    for(int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void inputMatrix(int **matrix, int rows, int cols) {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
}

int** multiplyMatrices(int **a, int **b, int rowsA, int colsA, int colsB) {
    int **result = createMatrix(rowsA, colsB);
    for(int i = 0; i < rowsA; i++) {
        for(int j = 0; j < colsB; j++) {
            result[i][j] = 0;
            for(int k = 0; k < colsA; k++) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return result;
}

void printMatrix(int **matrix, int rows, int cols) {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int rowsA, colsA, rowsB, colsB;
    printf("Enter rows and columns for the first matrix: ");
    scanf("%d %d", &rowsA, &colsA);
    printf("Enter rows and columns for the second matrix (rows must equal columns of the first): ");
    scanf("%d %d", &rowsB, &colsB);

    if (colsA != rowsB) {
        printf("Matrix multiplication is not possible.\n");
        return 1;
    }

    int **a = createMatrix(rowsA, colsA);
    int **b = createMatrix(rowsB, colsB);

    printf("Enter elements of the first matrix:\n");
    inputMatrix(a, rowsA, colsA);

    printf("Enter elements of the second matrix:\n");
    inputMatrix(b, rowsB, colsB);

    int **result = multiplyMatrices(a, b, rowsA, colsA, colsB);

    printf("Result of matrix multiplication:\n");
    printMatrix(result, rowsA, colsB);

    freeMatrix(a, rowsA);
    freeMatrix(b, rowsB);
    freeMatrix(result, rowsA);

    return 0;
}


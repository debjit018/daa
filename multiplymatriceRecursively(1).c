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

void multiplyRowByColumn(int **a, int **b, int **result, int row, int col, int n, int k) {
    if (k >= n) return;
    result[row][col] += a[row][k] * b[k][col];
    multiplyRowByColumn(a, b, result, row, col, n, k + 1);
}

void multiplyMatrices(int **a, int **b, int **result, int rowsA, int colsA, int colsB, int i, int j) {
    if (i >= rowsA) return;
    if (j >= colsB) {
        multiplyMatrices(a, b, result, rowsA, colsA, colsB, i + 1, 0);
        return;
    }
    result[i][j] = 0;
    multiplyRowByColumn(a, b, result, i, j, colsA, 0);
    multiplyMatrices(a, b, result, rowsA, colsA, colsB, i, j + 1);
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
    int **result = createMatrix(rowsA, colsB);

    printf("Enter elements of the first matrix:\n");
    inputMatrix(a, rowsA, colsA);

    printf("Enter elements of the second matrix:\n");
    inputMatrix(b, rowsB, colsB);

    multiplyMatrices(a, b, result, rowsA, colsA, colsB, 0, 0);

    printf("Result of matrix multiplication:\n");
    printMatrix(result, rowsA, colsB);

    freeMatrix(a, rowsA);
    freeMatrix(b, rowsB);
    freeMatrix(result, rowsA);

    return 0;
}


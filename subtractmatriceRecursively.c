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

void subtractMatrices(int **a, int **b, int **result, int rows, int cols, int i, int j) {
    if (i >= rows) return;
    if (j >= cols) {
        subtractMatrices(a, b, result, rows, cols, i + 1, 0);
        return;
    }
    result[i][j] = a[i][j] - b[i][j];
    subtractMatrices(a, b, result, rows, cols, i, j + 1);
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
    int rows, cols;
    printf("Enter the number of rows and columns: ");
    scanf("%d %d", &rows, &cols);

    int **a = createMatrix(rows, cols);
    int **b = createMatrix(rows, cols);
    int **result = createMatrix(rows, cols);

    printf("Enter elements of the first matrix:\n");
    inputMatrix(a, rows, cols);

    printf("Enter elements of the second matrix:\n");
    inputMatrix(b, rows, cols);

    subtractMatrices(a, b, result, rows, cols, 0, 0);

    printf("Result of subtracting the second matrix from the first:\n");
    printMatrix(result, rows, cols);

    freeMatrix(a, rows);
    freeMatrix(b, rows);
    freeMatrix(result, rows);

    return 0;
}


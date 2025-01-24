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

int** subtractMatrices(int **a, int **b, int rows, int cols) {
    int **result = createMatrix(rows, cols);
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            result[i][j] = a[i][j] - b[i][j];
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
    int rows, cols;
    printf("Enter the number of rows and columns: ");
    scanf("%d %d", &rows, &cols);

    int **a = createMatrix(rows, cols);
    int **b = createMatrix(rows, cols);

    printf("Enter elements of the first matrix:\n");
    inputMatrix(a, rows, cols);

    printf("Enter elements of the second matrix:\n");
    inputMatrix(b, rows, cols);

    int **result = subtractMatrices(a, b, rows, cols);

    printf("Result of subtracting the second matrix from the first:\n");
    printMatrix(result, rows, cols);

    freeMatrix(a, rows);
    freeMatrix(b, rows);
    freeMatrix(result, rows);

    return 0;
}


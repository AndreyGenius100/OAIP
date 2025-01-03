#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

void readMatrix(FILE* file, int* rows, int* cols, float** matrix) {
    fscanf_s(file, "%d", cols); // Читаем количество столбцов
    *rows = 0;
    float value;

    // Подсчёт количества строк
    while (fscanf_s(file, "%f", &value) == 1) {
        (*rows)++;
    }
    *rows /= *cols; // Количество строк = общее количество элементов / столбцов

    // Выделяем память для матрицы
    *matrix = (float*)malloc((*rows) * (*cols) * sizeof(float));
    if (*matrix == NULL) {
        printf("Ошибка: не удалось выделить память для матрицы.\n");
        exit(EXIT_FAILURE);
    }

    // Считываем матрицу
    rewind(file);
    fscanf_s(file, "%d", cols); // Пропускаем количество столбцов
    for (int i = 0; i < (*rows) * (*cols); i++) {
        fscanf_s(file, "%f", &(*matrix)[i]);
    }
}

void multiplyMatrices(int rowsA, int colsA, float* matrixA, int rowsB, int colsB, float* matrixB, float** result, int* rowsC, int* colsC) {
    // Проверяем возможность умножения
    if (colsA != rowsB) {
        *result = NULL;
        *rowsC = *colsC = 0;
        return;
    }

    *rowsC = rowsA;
    *colsC = colsB;

    // Выделяем память для результата
    *result = (float*)malloc((*rowsC) * (*colsC) * sizeof(float));
    if (*result == NULL) {
        printf("Ошибка: не удалось выделить память для результата.\n");
        exit(EXIT_FAILURE);
    }

    // Умножение матриц
    for (int i = 0; i < *rowsC; i++) {
        for (int j = 0; j < *colsC; j++) {
            (*result)[i * (*colsC) + j] = 0;
            for (int k = 0; k < colsA; k++) {
                (*result)[i * (*colsC) + j] += matrixA[i * colsA + k] * matrixB[k * colsB + j];
            }
        }
    }
}

void writeMatrixToFile(FILE* file, int rows, int cols, float* matrix) {
    fprintf(file, "%d\n", cols); // Записываем количество столбцов
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fprintf(file, "%.2f ", matrix[i * cols + j]);
        }
        fprintf(file, "\n");
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    FILE* fileA, * fileB, * fileC;
    errno_t errA, errB, errC;

    // Открытие файлов
    errA = fopen_s(&fileA, "fA.txt", "r");
    errB = fopen_s(&fileB, "fB.txt", "r");
    errC = fopen_s(&fileC, "fC.txt", "w");

    if (errA != 0 || errB != 0 || errC != 0) {
        printf("Ошибка открытия одного из файлов.\n");
        return EXIT_FAILURE;
    }

    int rowsA, colsA, rowsB, colsB, rowsC, colsC;
    float* matrixA, * matrixB, * matrixC;

    // Считываем матрицы
    printf("Считывание матрицы из файла fA.txt...\n");
    readMatrix(fileA, &rowsA, &colsA, &matrixA);
    printf("Считывание матрицы из файла fB.txt...\n");
    readMatrix(fileB, &rowsB, &colsB, &matrixB);

    // Умножаем матрицы
    printf("Выполняется умножение матриц...\n");
    multiplyMatrices(rowsA, colsA, matrixA, rowsB, colsB, matrixB, &matrixC, &rowsC, &colsC);

    if (matrixC != NULL) {
        // Записываем результат в файл
        printf("Результат умножения записан в файл fC.txt.\n");
        writeMatrixToFile(fileC, rowsC, colsC, matrixC);
    }
    else {
        printf("Матрицы нельзя перемножить. Файл fC.txt остался пустым.\n");
    }

    // Закрываем файлы и освобождаем память
    fclose(fileA);
    fclose(fileB);
    fclose(fileC);
    free(matrixA);
    free(matrixB);
    free(matrixC);

    printf("Программа завершена.\n");
    return 0;
}

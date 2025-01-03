#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "Russian");

    int a;            // Переменная для цикла
    FILE* f;          // Указатель на файл для записи
    char buffer[256]; // Буфер для чтения содержимого файла

    // Открытие файла "a.txt" для записи
    errno_t err = fopen_s(&f, "a.txt", "w");
    if (err != 0 || f == NULL) {
        perror("Невозможно создать файл");
        return EXIT_FAILURE;
    }

    // Цикл записи чисел от 0 до 69 с шагом 3 в файл
    for (a = 0; a < 70; a += 3) {
        fprintf(f, "%d, ", a);
    }

    printf("Данные записаны в файл a.txt\n");
    fclose(f); // Закрытие файла после записи

    // Открытие файла "a.txt" для чтения
    err = fopen_s(&f, "a.txt", "r");
    if (err != 0 || f == NULL) {
        perror("Невозможно открыть файл для чтения");
        return EXIT_FAILURE;
    }

    printf("Содержимое файла a.txt:\n");
    // Чтение содержимого файла и вывод на экран
    while (fgets(buffer, sizeof(buffer), f) != NULL) {
        printf("%s", buffer); // Вывод строки из файла
    }

    fclose(f); // Закрытие файла после чтения
    return 0;  // Успешное завершение программы
}

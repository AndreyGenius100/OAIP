#include <iostream>
#include <cstdio>     // Для работы с FILE, fopen_s, fwrite, fread
#include <cstring>    // Для strlen
#include <locale.h>   // Для установки локали

int main() {
    setlocale(LC_CTYPE, "Russian"); // Установка локали для отображения русского текста

    FILE* fp;               // Указатель на файл
    errno_t err;            // Переменная для кода ошибки
    const char* st = "привет"; // Строка для записи
    char buffer[50];        // Буфер для чтения данных из файла

    // Открытие файла для записи в двоичном режиме
    err = fopen_s(&fp, "a.bin", "wb"); // "wb" — режим записи в бинарном формате
    if (err != 0 || fp == NULL) {
        perror("Ошибка открытия файла a.bin для записи");
        return EXIT_FAILURE;
    }

    // Запись строки в файл
    size_t bytesWritten = fwrite(st, sizeof(char), strlen(st), fp);
    if (bytesWritten != strlen(st)) {
        perror("Ошибка записи в файл");
        fclose(fp);
        return EXIT_FAILURE;
    }
    printf("Записано %zu байт в файл a.bin\n", bytesWritten);
    fclose(fp); // Закрытие файла после записи

    // Открытие файла для чтения в двоичном режиме
    err = fopen_s(&fp, "a.bin", "rb"); // "rb" — режим чтения в бинарном формате
    if (err != 0 || fp == NULL) {
        perror("Ошибка открытия файла a.bin для чтения");
        return EXIT_FAILURE;
    }

    // Чтение содержимого файла
    size_t bytesRead = fread(buffer, sizeof(char), sizeof(buffer) - 1, fp);
    if (bytesRead > 0) {
        buffer[bytesRead] = '\0'; // Завершение строки
        printf("\nСодержимое файла a.bin: %s\n", buffer);
    }
    else {
        printf("\nОшибка или пустой файл\n");
    }

    fclose(fp); // Закрытие файла после чтения
    return EXIT_SUCCESS;
}

#include <stdio.h>  // Для работы с файлами и стандартного ввода-вывода
#include <stdlib.h> // Для использования EXIT_FAILURE
#include <locale.h> // Для установки локали
#include <string.h> // Для работы со строками

int main() {
    setlocale(LC_ALL, "Russian"); // Установка локали для корректного отображения сообщений

    FILE* mf;           // Указатель на файл
    char str[50];       // Буфер для строки
    errno_t err;        // Переменная для хранения кода ошибки
    char* estr;         // Указатель для результата чтения строки

    // Ввод строки текста от пользователя
    printf("Введите текст: ");
    if (fgets(str, sizeof(str), stdin) == NULL) { // Безопасный ввод строки
        printf("Ошибка ввода строки\n");
        return EXIT_FAILURE;
    }

    // Удаление возможного символа новой строки ('\n'), если он есть
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }

    // Открытие файла "tst.txt" для записи
    err = fopen_s(&mf, "tst.txt", "w");
    if (err != 0 || mf == NULL) { // Проверка успешного открытия файла
        printf("Ошибка открытия файла для записи\n");
        return EXIT_FAILURE;
    }

    // Запись строки в файл
    fputs(str, mf);
    fputs("\n", mf); // Запись символа новой строки
    fclose(mf); // Закрытие файла после записи
    printf("Данные записаны в файл tst.txt\n");

    // Открытие файла "tst.txt" для чтения
    err = fopen_s(&mf, "tst.txt", "r");
    if (err != 0 || mf == NULL) { // Проверка успешного открытия файла
        printf("Ошибка открытия файла для чтения\n");
        return EXIT_FAILURE;
    }

    printf("\nСодержимое файла tst.txt:\n");

    // Чтение строк из файла и вывод их на экран
    while ((estr = fgets(str, sizeof(str), mf)) != NULL) {
        printf("%s", str); // Вывод строки
    }

    // Проверка, если чтение завершилось из-за конца файла
    if (feof(mf)) {
        printf("\nЧтение файла завершено.\n");
    }
    else {
        printf("\nОшибка чтения из файла\n");
        fclose(mf); // Закрытие файла перед завершением
        return EXIT_FAILURE;
    }

    // Закрытие файла после чтения
    if (fclose(mf) == EOF) {
        printf("Ошибка закрытия файла\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS; // Успешное завершение программы
}

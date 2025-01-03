#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "Russian"); // Установка локали для корректного вывода
    FILE* file_f, * file_g;
    int number, K, err_f, err_g;

    // Запрос у пользователя значения K
    printf("Введите значение K: ");
    scanf_s("%d", &K);

    // Открытие исходного файла f.txt для чтения
    err_f = fopen_s(&file_f, "f.txt", "r");
    if (err_f != 0 || file_f == NULL) {
        perror("Ошибка открытия файла f.txt");
        return EXIT_FAILURE;
    }

    // Открытие результирующего файла g.txt для записи
    err_g = fopen_s(&file_g, "g.txt", "w");
    if (err_g != 0 || file_g == NULL) {
        perror("Ошибка открытия файла g.txt");
        fclose(file_f);
        return EXIT_FAILURE;
    }

    printf("Числа из f.txt, кратные %d, записаны в g.txt:\n", K);

    // Чтение чисел из файла f.txt
    while (fscanf_s(file_f, "%d", &number) == 1) {
        if (number % K == 0) {
            fprintf(file_g, "%d\n", number); // Запись в g.txt
            printf("%d ", number);          // Вывод на экран
        }
    }

    // Закрытие файлов
    fclose(file_f);
    fclose(file_g);

    printf("\nОперация завершена.\n");
    return 0;
}

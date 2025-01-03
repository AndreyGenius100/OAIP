#include <iostream>
#include <cstdio> // Для работы с FILE
#include <locale>
#include <cstring> // Для работы со строками

using namespace std;

int main() {
    setlocale(LC_CTYPE, "Russian");

    int number;           // Номер предложения для вывода
    char ch;              // Для чтения символов из файла
    FILE* fd;             // Указатель на файл
    errno_t err;          // Переменная для кода ошибки

    // Открытие файла "b.txt" для чтения
    err = fopen_s(&fd, "b.txt", "r");
    if (err != 0 || fd == NULL) {
        perror("Ошибка открытия файла b.txt");
        return EXIT_FAILURE;
    }

    printf("Введите номер предложения n (0 - вывести все): ");
    scanf_s("%d", &number);

    int currentSentence = 0; // Счётчик предложений
    string sentence = "";    // Хранение текущего предложения

    printf("\nСодержимое файла:\n");
    while (fread(&ch, sizeof(char), 1, fd) == 1) {
        sentence += ch; // Добавляем символ в строку
        if (ch == '.') { // Конец предложения
            currentSentence++;
            if (number == 0 || currentSentence <= number) {
                printf("%d-е предложение: %s\n", currentSentence, sentence.c_str());
            }
            sentence.clear(); // Очищаем строку для нового предложения
        }
    }

    if (number > currentSentence) {
        printf("\nТакого номера предложения нет в файле.\n");
    }

    fclose(fd); // Закрытие файла
    return EXIT_SUCCESS;
}

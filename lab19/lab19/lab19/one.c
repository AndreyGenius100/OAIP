#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "Russian");

    int a;            // ���������� ��� �����
    FILE* f;          // ��������� �� ���� ��� ������
    char buffer[256]; // ����� ��� ������ ����������� �����

    // �������� ����� "a.txt" ��� ������
    errno_t err = fopen_s(&f, "a.txt", "w");
    if (err != 0 || f == NULL) {
        perror("���������� ������� ����");
        return EXIT_FAILURE;
    }

    // ���� ������ ����� �� 0 �� 69 � ����� 3 � ����
    for (a = 0; a < 70; a += 3) {
        fprintf(f, "%d, ", a);
    }

    printf("������ �������� � ���� a.txt\n");
    fclose(f); // �������� ����� ����� ������

    // �������� ����� "a.txt" ��� ������
    err = fopen_s(&f, "a.txt", "r");
    if (err != 0 || f == NULL) {
        perror("���������� ������� ���� ��� ������");
        return EXIT_FAILURE;
    }

    printf("���������� ����� a.txt:\n");
    // ������ ����������� ����� � ����� �� �����
    while (fgets(buffer, sizeof(buffer), f) != NULL) {
        printf("%s", buffer); // ����� ������ �� �����
    }

    fclose(f); // �������� ����� ����� ������
    return 0;  // �������� ���������� ���������
}

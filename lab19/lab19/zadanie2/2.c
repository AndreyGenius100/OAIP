#include <stdio.h>  // ��� ������ � ������� � ������������ �����-������
#include <stdlib.h> // ��� ������������� EXIT_FAILURE
#include <locale.h> // ��� ��������� ������
#include <string.h> // ��� ������ �� ��������

int main() {
    setlocale(LC_ALL, "Russian"); // ��������� ������ ��� ����������� ����������� ���������

    FILE* mf;           // ��������� �� ����
    char str[50];       // ����� ��� ������
    errno_t err;        // ���������� ��� �������� ���� ������
    char* estr;         // ��������� ��� ���������� ������ ������

    // ���� ������ ������ �� ������������
    printf("������� �����: ");
    if (fgets(str, sizeof(str), stdin) == NULL) { // ���������� ���� ������
        printf("������ ����� ������\n");
        return EXIT_FAILURE;
    }

    // �������� ���������� ������� ����� ������ ('\n'), ���� �� ����
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }

    // �������� ����� "tst.txt" ��� ������
    err = fopen_s(&mf, "tst.txt", "w");
    if (err != 0 || mf == NULL) { // �������� ��������� �������� �����
        printf("������ �������� ����� ��� ������\n");
        return EXIT_FAILURE;
    }

    // ������ ������ � ����
    fputs(str, mf);
    fputs("\n", mf); // ������ ������� ����� ������
    fclose(mf); // �������� ����� ����� ������
    printf("������ �������� � ���� tst.txt\n");

    // �������� ����� "tst.txt" ��� ������
    err = fopen_s(&mf, "tst.txt", "r");
    if (err != 0 || mf == NULL) { // �������� ��������� �������� �����
        printf("������ �������� ����� ��� ������\n");
        return EXIT_FAILURE;
    }

    printf("\n���������� ����� tst.txt:\n");

    // ������ ����� �� ����� � ����� �� �� �����
    while ((estr = fgets(str, sizeof(str), mf)) != NULL) {
        printf("%s", str); // ����� ������
    }

    // ��������, ���� ������ ����������� ��-�� ����� �����
    if (feof(mf)) {
        printf("\n������ ����� ���������.\n");
    }
    else {
        printf("\n������ ������ �� �����\n");
        fclose(mf); // �������� ����� ����� �����������
        return EXIT_FAILURE;
    }

    // �������� ����� ����� ������
    if (fclose(mf) == EOF) {
        printf("������ �������� �����\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS; // �������� ���������� ���������
}

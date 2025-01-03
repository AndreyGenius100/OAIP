#include <iostream>  // ����������� ����������� ���������� �����-������

// �������� ������� metodPr: ��������� ������� ������������� ��������
// fun - ��������� �� �������, ����������� �������� ������� � �����
// a, b - ������� ��������������
// h - ��� ���������
double metodPr(double(*fun)(double), double a, double b, double h);

// �������� ������� f: ��������� �������������� �������
double f(double);

int main()
{
    double z;  // ���������� ��� �������� ���������� ����������

    // ����� ������� metodPr ��� ������� f �� ��������� [0.0, 2.0] � ����� 0.01
    z = metodPr(f, 0.0, 2.0, 0.01);

    // ����� ���������� ����������
    std::cout << "Result1=" << z;

    return 0;  // �������� ���������� ���������
}

// ������� metodPr: �������� ��������� ������� ������������� ��������
double metodPr(double (*fun)(double), double a, double b, double h)
{
    double x, s = 0.0;  // x - ������� �����, s - ����������� �����
    x = a + h;  // ��������� �������� x (��������� ����� a)

    // ���� ������������ �� ��������
    while (x <= b)
    {
        s += h * fun(x);  // ��������� ������� �������������� � ����� �����
        x = x + h;  // ������� � ��������� �����
    }

    return s / 2;  // ���������� �������� ����� (���� ��������)
}

// ������� f: ��������� ����������� y = 2x + 5
double f(double x)
{
    return (2 * x + 5);  // ���������� �������� ������� � ����� x
}

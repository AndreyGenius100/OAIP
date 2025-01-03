#include <iostream>
#include <cmath>
#include <iomanip> // Для форматирования вывода

const double EPSILON = 0.001; // Заданная точность

// Первая функция: x^2 + 4x - 2
double equation1(double x) {
    return x * x + 4 * x - 2;
}

// Вторая функция: sin(x) + 0.1
double equation2(double x) {
    return sin(x) + 0.1;
}

// Метод дихотомии для нахождения корня
double bisectionMethod(double (*func)(double), double a, double b) {
    if (func(a) * func(b) > 0) {
        std::cerr << "Ошибка: функция должна иметь разные знаки на концах интервала!" << std::endl;
        return NAN;
    }

    double c;
    while ((b - a) >= EPSILON) {
        c = (a + b) / 2; // Середина интервала

        if (func(c) == 0.0) {
            break; // Если корень найден точно
        }

        // Выбираем подинтервал, в котором функция меняет знак
        if (func(c) * func(a) < 0) {
            b = c;
        }
        else {
            a = c;
        }
    }

    return c;
}

int main() {
    setlocale(LC_ALL, "Rus");
    std::cout << std::fixed << std::setprecision(3); // Формат вывода с 3 знаками после запятой

    double a1, b1, a2, b2;

    // Ввод интервалов для первого уравнения
    std::cout << "Введите границы интервала для первого уравнения (x^2 + 4x - 2): ";
    std::cin >> a1 >> b1;

    // Ввод интервалов для второго уравнения
    std::cout << "Введите границы интервала для второго уравнения (sin(x) + 0.1): ";
    std::cin >> a2 >> b2;

    // Нахождение корня для первого уравнения
    double root1 = bisectionMethod(equation1, a1, b1);
    if (!std::isnan(root1)) {
        std::cout << "Корень первого уравнения на интервале [" << a1 << ", " << b1 << "]: " << root1 << std::endl;
    }

    // Нахождение корня для второго уравнения
    double root2 = bisectionMethod(equation2, a2, b2);
    if (!std::isnan(root2)) {
        std::cout << "Корень второго уравнения на интервале [" << a2 << ", " << b2 << "]: " << root2 << std::endl;
    }

    return 0;
}

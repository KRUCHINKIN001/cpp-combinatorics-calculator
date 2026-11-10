#include <iostream>
#include <limits>
#include <string>
#include <windows.h>

using ull = unsigned long long;

// Функция безопасного ввода неотрицательного целого числа
bool readNonNegativeInt(const std::string& prompt, int& value) {
    std::cout << prompt;

    std::string input;
    if (!(std::cin >> input)) {
        return false;
    }

    for (char c : input) {
        if (!std::isdigit(static_cast<unsigned char>(c))) {
            return false;
        }
    }

    try {
        value = std::stoi(input);
    } catch (const std::exception&) {
        return false;
    }

    return value >= 0;
}

// Функция безопасного ввода k (не больше n)
bool readK(const std::string& prompt, int n, int& k) {
    while (true) {
        if (!readNonNegativeInt(prompt, k)) {
            std::cout << "Ошибка: введите неотрицательное целое число.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (k > n) {
            std::cout << "Ошибка: k не может быть больше n (" << n << ").\n";
            continue;
        }

        return true;
    }
}

// Вычисление факториала с проверкой на переполнение
bool factorial(int n, ull& result) {
    result = 1;

    for (int i = 2; i <= n; ++i) {
        if (result > std::numeric_limits<ull>::max() / static_cast<ull>(i)) {
            return false;
        }
        result *= static_cast<ull>(i);
    }

    return true;
}

// 1. Перестановки P(n) = n!
void permutations() {
    int n;

    while (!readNonNegativeInt("Введите n: ", n)) {
        std::cout << "Ошибка: введите неотрицательное целое число.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    ull result;

    if (!factorial(n, result)) {
        std::cout << "Ошибка: переполнение при вычислении P(" << n << ").\n";
        return;
    }

    std::cout << "Результат: P(" << n << ") = " << result << "\n";
}

// 2. Размещения A(n, k) = n! / (n-k)!
// Считаем "в лоб" без нахождения двух факториалов, чтобы избежать лишнего переполнения
void arrangements() {
    int n, k;

    while (!readNonNegativeInt("Введите n: ", n)) {
        std::cout << "Ошибка: введите неотрицательное целое число.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    readK("Введите k: ", n, k);

    ull result = 1;

    // Формула: умножаем n * (n-1) * (n-2) ... (n-k+1)
    for (int i = 0; i < k; ++i) {
        ull multiplier = static_cast<ull>(n - i);

        if (result > std::numeric_limits<ull>::max() / multiplier) {
            std::cout << "Ошибка: переполнение при вычислении A(" << n << ", " << k << ").\n";
            return;
        }
        result *= multiplier;
    }

    std::cout << "Результат: A(" << n << ", " << k << ") = " << result << "\n";
}

// 3. Сочетания C(n, k) = n! / (k! * (n-k)!)
void combinations() {
    int n, k;

    while (!readNonNegativeInt("Введите n: ", n)) {
        std::cout << "Ошибка: введите неотрицательное целое число.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    readK("Введите k: ", n, k);

    ull result = 1;
    int smaller = (k < n - k) ? k : n - k;

    // Оптимизированный расчет, чтобы не считать огромные факториалы
    for (int i = 1; i <= smaller; ++i) {
        ull multiplier = static_cast<ull>(n - smaller + i);
        ull divisor = static_cast<ull>(i);

        if (result > std::numeric_limits<ull>::max() / multiplier) {
            std::cout << "Ошибка: переполнение при вычислении C("
                      << n << ", " << k << ").\n";
            return;
        }

        result *= multiplier;
        result /= divisor;
    }

    std::cout << "Результат: C(" << n << ", " << k << ") = " << result << "\n";
}

int main() {
    // Исправляем кракозябры в консоли Windows
    system("chcp 65001 > nul");
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    setlocale(LC_ALL, "Russian");

    while (true)


{
        std::cout << "\n=== КАЛЬКУЛЯТОР КОМБИНАТОРИКИ ===\n";
        std::cout << "1. Перестановки\n";
        std::cout << "2. Размещения\n";
        std::cout << "3. Сочетания\n";
        std::cout << "0. Выход\n";
        std::cout << "Выберите метод: ";

        std::string choice;
        if (!(std::cin >> choice)) {
            break;
        }

        if (choice == "1") {
            permutations();
        } else if (choice == "2") {
            arrangements();
        } else if (choice == "3") {
            combinations();
        } else if (choice == "0") {
            std::cout << "Программа завершена.\n";
            break;
        } else {
            std::cout << "Ошибка: выберите пункт меню от 0 до 3.\n";
        }
    }

    return 0;
}

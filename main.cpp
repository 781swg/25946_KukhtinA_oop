#include <iostream>
#include "average.h"
#include "average_random.h"

int main() {
    int a;
    double b;
    char mode;

    std::cout << "Выберите режим (n - обычное среднее, m - модифицированное): ";
    std::cin >> mode;

    std::cout << "Введите два числа через пробел: ";
    std::cin >> a >> b;

    if (mode == 'n') {
        std::cout << orig::average<float>(a, b) << '\n';
    } else if (mode == 'm') {
        std::cout << modified::average<float>(a, b) << '\n';
    } else {
        std::cout << "Некорректный режим\n";
        return 1;
    }

    return 0;
}

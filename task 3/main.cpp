#include <iostream>
#include <array>
#include <vector>
#include <list>
#include <deque>
#include <random>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include "average_modified.h"

int main() {
    using T1 = double;
    using T2 = int;

    const int M = 14;
    const int N = 2;

    // генератор случайных чисел
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<T1> dist(-N, N);

    // создание контейнеров
    std::array<T1, M> arr;
    std::vector<T1> vec(M);
    std::list<T1> lst;
    std::deque<T1> deq;

    // заполнение контейнеров случайными значениями
    for (int i = 0; i < M; i++) {
        arr[i] = dist(gen);
        vec[i] = dist(gen);
        lst.push_back(dist(gen));
        deq.push_back(dist(gen));
    }

    // один общий второй аргумент для функции
    T1 second_arg = dist(gen);

    // контейнеры для результатов
    std::vector<T2> arr_result;
    std::list<T2> vec_result;
    std::deque<T2> lst_result;
    std::array<T2, M> deq_result;

    // обработка array обычным for
    for (int i = 0; i < M; i++) {
        arr_result.push_back(mod::average<T1, T2>(arr[i], second_arg));
    }

    // обработка vector через итератор
    for (std::vector<T1>::iterator it = vec.begin(); it != vec.end(); ++it) {
        vec_result.push_back(mod::average<T1, T2>(*it, second_arg));
    }

    // обработка list через range-based for
    for (T1 value : lst) {
        lst_result.push_back(mod::average<T1, T2>(value, second_arg));
    }

    // обработка deque обычным for
    for (int i = 0; i < M; i++) {
        deq_result[i] = mod::average<T1, T2>(deq[i], second_arg);
    }

    // строки будущей markdown таблицы
    std::ostringstream header;
    std::ostringstream separator;
    std::ostringstream arr_row;
    std::ostringstream arr_result_row;
    std::ostringstream vec_row;
    std::ostringstream vec_result_row;
    std::ostringstream lst_row;
    std::ostringstream lst_result_row;
    std::ostringstream deq_row;
    std::ostringstream deq_result_row;

    // названия строк таблицы
    header << "| Container |";
    separator << "|---|";
    arr_row << "| array<T1> |";
    arr_result_row << "| array -> vector<T2> |";
    vec_row << "| vector<T1> |";
    vec_result_row << "| vector -> list<T2> |";
    lst_row << "| list<T1> |";
    lst_result_row << "| list -> deque<T2> |";
    deq_row << "| deque<T1> |";
    deq_result_row << "| deque -> array<T2> |";

    // итераторы для list
    std::list<T1>::const_iterator lst_it = lst.cbegin();
    std::list<T2>::const_iterator vec_result_it = vec_result.cbegin();

    // заполнение таблицы значениями
    for (int i = 0; i < M; i++) {
        header << " " << i << " |";
        separator << "---|";

        arr_row << " " << std::fixed << std::setprecision(3) << arr[i] << " |";
        arr_result_row << " " << arr_result[i] << " |";

        vec_row << " " << std::fixed << std::setprecision(3) << vec[i] << " |";
        vec_result_row << " " << *vec_result_it << " |";

        lst_row << " " << std::fixed << std::setprecision(3) << *lst_it << " |";
        lst_result_row << " " << lst_result[i] << " |";

        deq_row << " " << std::fixed << std::setprecision(3) << deq[i] << " |";
        deq_result_row << " " << deq_result[i] << " |";

        ++lst_it;
        ++vec_result_it;
    }

    // сбор всех строк таблицы
    std::vector<std::string> rows;
    rows.push_back(header.str());
    rows.push_back(separator.str());
    rows.push_back(arr_row.str());
    rows.push_back(arr_result_row.str());
    rows.push_back(vec_row.str());
    rows.push_back(vec_result_row.str());
    rows.push_back(lst_row.str());
    rows.push_back(lst_result_row.str());
    rows.push_back(deq_row.str());
    rows.push_back(deq_result_row.str());

    // создание markdown файла
    std::ofstream out("table.md");

    // проверка открытия файла
    if (!out.is_open()) {
        return 1;
    }

    // запись данных в файл
    out << "# Results\n\n";
    out << "Second argument: " << second_arg << "\n\n";

    for (std::vector<std::string>::const_iterator it = rows.cbegin(); it != rows.cend(); ++it) {
        out << *it << '\n';
    }

    out.close();

    std::cout << "table.md created\n";

    return 0;
}
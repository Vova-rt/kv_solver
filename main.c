
#include <TXLib.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


#define TRUE 1
#define FALSE 0
#define E 0.000001
#define TESTS 1000
#define BUFF 100
#define BUFF_NUM 30


#define RED "\033[0;31m" // красный текст
#define ONLY_GREEN "\033[0;32m" // зеленый текст
#define GREEN "\033[32;47m" // зеленый текст на белом фоне
#define YELLOW "\033[0;33m" // желтый текст
#define BLACK "\033[30;47m" // черный текст на белом фоне
#define PURPLE "\033[0;35m" // фиолетовый текст
#define ORANGE "\033[38;2;255;127;m" // оранжевый текст
#define BLUE "\033[1;34m"
#define RESET "\033[0m" // Сброс цвета к стандартному
//printf(RED "Этот текст красный!" RESET "\n");


struct KvEq {
    double a , b, c;
    double x1, x2;
    double D;
    int nroots;
};


struct TestCase {
    double a, b, c;
    int nrootsRef;
    double x1ref,  x2ref;
};


// int abc_(char, double*); // чтение коэффициентов
int exit_before_start(); // проверяет хочет ли пользователь завершить программу после завершения тестов
int input(struct KvEq *); //обработка ввода(вида ax^2 + bx + c)
void discriminant(struct KvEq *); // вычисление дискриминанта
void solve_eq(struct KvEq *); // счет корней
void output(const struct KvEq *); // вывод корней
int continuE(void); //хочет ли пользователь продолжить
bool is_zero(double); //является ли число нулем
void clear_buffer(void); //очистка мусорной части ввода
int is_root(const struct KvEq *, double); //является ли х корнем
int RunOneTest(struct TestCase, int, int*, int*); // ручные тесты
int RunTests(); // запуск тестов
void RandomTests(); // рандом тесты
void print_struct(struct TestCase); // печать содержимого структуры(для тестов)
void what_test_failed(int); // номер теста, который провалился

int main(void)
{
    struct KvEq main_kv ={};

    srand((unsigned)time(NULL));

    if (!RunTests()) {
        printf(BLACK "Программа завершена" RESET);
        return 0;
    }
    RandomTests();
    if (exit_before_start() == FALSE)
        return 0;
    do {
        input(&main_kv);
        solve_eq(&main_kv);
        output(&main_kv);
    } while (continuE() == TRUE);

    return 0;
}
#include "kvadratka.c"
#include "tests.c"

#include <kvadratka.c>
#include <tests.c>

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


#define RED "\033[0;31m" // красный текст
#define ONLY_GREEN "\033[0;32m" // зеленый текст
#define GREEN "\033[32;47m" // зеленый текст на белом фоне
#define YELLOW "\033[0;33m" // желтый текст
#define BLACK "\033[30;47m" // черный текст на белом фоне
#define PURPLE "\033[0;35m" // фиолетовый текст
#define ORANGE "\033[38;2;255;127;m" // оранжевый текст
#define RESET "\033[0m" // —брос цвета к стандартному
//printf(RED "Ётот текст красный!" RESET "\n");


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
int input(struct KvEq *); //обработка ввода
void discriminant(struct KvEq *); // вычисление дискриминанта
void solve_sq(struct KvEq *); // счет корней
void output(const struct KvEq *); // вывод корней
int continuE(void); //хочет ли пользователь продолжить
bool is_zero(double); //€вл€етс€ ли число нулем
void clear_buffer(void); //очистка мусорной части ввода
int is_root(const struct KvEq *, double); //€вл€етс€ ли х корнем
int RunOneTest(struct TestCase, int, int*, int*); // ручные тесты
int RunTests(); // запуск тестов
int exit_before_start(); // провер€ет хочет ли пользователь завершить программу в самом начале
void print_struct(struct TestCase); // печать содержимого структуры
void RandomTest(); //рандом тесты
void what_test_failed(int); //какой тест провалилс€

int main(void)
{

    struct KvEq kv = {};

    srand((unsigned)time(NULL));

    if (!RunTests()) {
        printf(BLACK "ѕрограмма завершена" RESET);
        return 0;
    }
    RandomTest();
    if (exit_before_start() == FALSE)
        return 0;
    do {
        input(&kv);
        solve_sq(&kv);
        output(&kv);
    } while (continuE() == TRUE);

    return 0;
}

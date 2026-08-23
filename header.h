#include <TXLib.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>


#define TRUE 1
#define FALSE 0
#define E 0.000001
#define TESTS 1000


struct Test_Case {
    double a, b, c;
    int nrootsRef;
    double x1ref,  x2ref;
};


int abc_(char, double*); // чтение коэффициентов
int input(double *, double *, double *); //обработка ввода
void discriminant(double , double , double, double*); // вычисление дискриминанта
int Solvesq(double, double, double, double*, double*); // счет корней
void output(int, double, double); // вывод корней
int continuE(void); //хочет ли пользователь продолжить
bool is_zero(double); //является ли число нулем
void clear_buffer(void); //очистка мусорной части ввода
int is_root(double, double, double, double); //является ли х корнем
int RunOneTest(struct Test_Case, int*, int*); // ручные тесты
void RunTests(); // запуск тестов
int exit_before_start(); // проверяет хочет ли пользователь завершить программу в самом начале ввода
void print_struct(struct Test_Case); // печать содержимого структуры
void RandomTest();




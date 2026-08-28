
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
#define MAX_TESTS 10
#define WIDTH 100
#define HEIGHT 30


#define RED "\033[0;31m" // красный текст
#define ONLY_GREEN "\033[0;32m" // зеленый текст
#define GREEN "\033[32;47m" // зеленый текст на белом фоне
#define YELLOW "\033[0;33m" // желтый текст
#define BLACK "\033[30;47m" // черный текст на белом фоне
#define PURPLE "\033[0;35m" // фиолетовый текст
#define ORANGE "\033[38;2;255;127;m" // оранжевый текст
#define BLUE "\033[1;34m"
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
    int line_number;
};


// int abc_(char, double*); // чтение коэффициентов
int exit_before_start(); // провер€ет хочет ли пользователь завершить программу после завершени€ тестов
int input(struct KvEq *); //обработка ввода(вида ax^2 + bx + c)
void discriminant(struct KvEq *); // вычисление дискриминанта
void solve_eq(struct KvEq *); // счет корней
void output(const struct KvEq *); // вывод корней
void paint_func(struct KvEq ); // отрисовка графика функции в терминале
int continuE(void); //хочет ли пользователь продолжить
bool is_zero(double); //€вл€етс€ ли число нулем
void clear_buffer(void); //очистка мусорной части ввода
int is_root(const struct KvEq *, double); //€вл€етс€ ли х корнем
int equal(double, double); // провер€ет равны ли х1 и х2
int is_str_number(char*); // провер€ет €вл€етс€ ли строковое представление числа числом
int RunOneTest(struct TestCase, int, int*); // ручные тесты
int RunTests(); // запуск тестов
void RandomTests(); // рандом тесты
void print_struct(struct TestCase); // печать содержимого структуры(дл€ тестов)
void what_test_failed(int); // номер теста, который провалилс€
void what_line_skipped(int); // номер строки файла с тестами, котора€ не была корректно считана

int main(void)
{
    struct KvEq main_kv ={};

    srand((unsigned)time(NULL));

    if (!RunTests()) {
        printf(BLACK "ѕрограмма завершена" RESET);
        return 0;
    }
    RandomTests();
    if (exit_before_start() == FALSE)
        return 0;
    do {
        input(&main_kv);
        solve_eq(&main_kv);
        paint_func(main_kv);
        output(&main_kv);
    } while (continuE() == TRUE);

    return 0;
}
#include "kvadratka.c"
#include "tests.c"

void paint_func(struct KvEq paint) {

    double x_min = 0, x_max = 0;
    if (is_zero(paint.a)) {
        x_min = -15;
        x_max = 15;
    }
    else if (paint.D >= 0) {
        x_min = fmin(paint.x1, paint.x2) - 5;
        x_max = fmax(paint.x1, paint.x2) + 5;

        if (x_max - x_min < 1) {
            x_min -= 1;
            x_max += 1;
        }
    }

    else {
        double height = -paint.b/(2*paint.a);
        double i = 3 / (fabs(paint.a));
        if (i > 30)
            i = 30;
        if (i < 1)
            i = 1;
        x_min = height - i;
        x_max = height + i;
    }

    double step_x = (x_max-x_min) / (WIDTH - 1);
    double y[WIDTH];
    double y_min = 100000;
    double y_max = -100000;

    for (int i = 0; i < WIDTH; i++) {
        double x_cur = x_min + i * step_x;
        y[i] = paint.a * x_cur*x_cur + paint.b * x_cur + paint.c;

        if (y[i] < y_min)
            y_min = y[i];
        if (y[i] > y_max)
            y_max = y[i];
    }

    if ((y_max - y_min) < E) {
        y_min -= 1;
        y_max += 1;
    }

    double step_y = (y_max - y_min) / (HEIGHT -1);

    for (int row = 0; row < HEIGHT; row++) {
        double y_row = y_max - step_y * row;
        double y_row_nxt = y_max - step_y * (row + 1);

        for (int col = 0; col < WIDTH; col++) {

            double x_col = x_min + col * step_x;
            double y_cur = y[col];

            int in = 0;
            if (y_cur >= y_row_nxt && y_cur <= y_row)
                in = 1;
            if (in)
                printf(".");
            else {
                int x_c = fabs(y_row) < step_y / 2;
                int y_c = fabs(x_col) < step_x / 2;

                if (x_c && y_c)
                    printf("+");
                else if (x_c)
                    printf("-");
                else if (y_c)
                    printf("|");
                else
                    printf(" ");
            }
        }
        printf("\n");
    }

}

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
    int nrootsref;
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
int RunOneTest(struct Test_Case); //
void RunTests(); //проверка
int exit_before_start(); // проверяет хочет ли пользователь завершить программу в самом начале ввода


int main(void)
{
    srand((unsigned)time(NULL));
    RunTests();

    double a = 0, b = 0, c = 0;
    double x1 = 0, x2 = 0;
    int nroots = 0;
    if (!exit_before_start();)
        return 0;
    do {
        input(&a, &b, &c);
        nroots = Solvesq(a, b, c, &x1, &x2);
        output(nroots, x1, x2);
        } while (continuE() == TRUE);

    return 0;
}

int exit_before_start() {

    printf("Хотите завершить программу?\n");
    char ch = '\0';

    if (ch = getchar() == 'q') {
        printf("Программа завершена");
        return FALSE;
    }
    ungetc(ch, stdin);
    return TRUE;
}

int abc_(char s, double* pt_s) {

    assert(pt_s != NULL);

    /* printf("\nВведите коэффициент %c:\n", s);

    if (scanf("%lf", pt_s) && getchar() == '\n');
            return TRUE;
    else {
        clear_buffer();
        printf("Ошибка ввода, заново введите коэффициенты\n");
        return FALSE;
    } */
    printf("Введите коэффициент %c:\n", s);
    char ch = 0;
    while (TRUE) {
    int k = scanf("%lf", pt_s);
        if (k == 1) {
            while (isspace(ch = getchar())) {
                if (ch == '\n')
                    return TRUE;
            }
                clear_buffer();
                printf("Ошибка ввода, заново введите коэффициент %c\n", s);
                continue;
        }
        clear_buffer();
            printf("Ошибка ввода, заново введите коэффициент %c\n", s);
            continue;
    }

}

int input(double * a, double * b, double * c) {
    assert(a != NULL);
    assert(b != NULL);
    assert(c != NULL);

    printf("Введите коэффициенты квадратного уравнения\n");


    /*while (!abc_('a', a)) ;
    while (!abc_('b', b)) ;
    while (!abc_('c', c)) ;

    return TRUE;
    */
    abc_('a', a);
    abc_('b', b);
    abc_('c', c);

    return TRUE;
}

void discriminant(double a, double b, double c, double* pt_D) {

    assert(pt_D != NULL);

    *pt_D = b*b - 4*a*c;

}

int Solvesq(double a, double b, double c, double* x1, double* x2) {

    assert(x1 != NULL);
    assert(x2 != NULL);
    double D = 0;
    discriminant(a, b, c, &D);

    if (is_zero(a)) {
        if (is_zero(b)) {
            if (is_zero(c)) {
                *x1 = NAN;
                *x2 = NAN;
                return -1;
            }
            else {
                *x1 = *x2 = NAN;
                return 0;
            }
        }

        else {
            *x2 = NAN;
            *x1 = -c / b;
            return 1;
        }
    }

    else {
        if (D < 0)
            return 0;
        else if (is_zero(D)) {
            *x2 = NAN;
            *x1 = -b / (2*a);
            return 1;
        }

        else {
        *x1 = (sqrt(D) - b) / (2 * a);
        *x2 = (-sqrt(D) - b) / (2 * a);
            return 2;
        }
    }

}

void output(int nroots, double x1, double x2) {

        switch(nroots) {
            case -1:
                printf("Бесконечно много корней\n");
                break;
            case 0:
                printf("Действительных корней нет\n");
                break;
            case 1:
                printf("Один корень:   x = %lg\n", x1);
                break;
            case 2:
                printf("Два корня:  x1 = %lg, x2 = %lg\n", x1, x2);
                break;
            default:
                printf("Ошибка числ корней\n");
        }


}
int continuE(void) {

    printf("Хотите продолжить?\n"
    "Введите 1 для продолжения или 0 для завершения\n");

    while (TRUE) {

        int ch = -1;
        scanf("%d", &ch);
        int flag = 0;

        if (ch == 0) {
            while((ch = getchar()) != '\n') {
                if (isspace(ch))
                continue;

                else {
                    clear_buffer();
                    printf("Ошибка ввода, введите 0 или 1\n");
                    flag++;
                    break;
                }
            }
            if (flag == 0) {
                printf("Программа завершена");
                return FALSE;
            }
            else
                continue;
        }

        if (ch == 1) {
            while((ch = getchar()) != '\n') {
                if (isspace(ch))
                continue;

                else {
                    clear_buffer();
                    printf("Ошибка ввода, введите 0 или 1\n");
                    flag++;
                    break;
                }
            }
            if (flag == 0)
                return TRUE;

            else
                continue;
        }
        else
            clear_buffer();
            printf("Ошибка ввода, введите 0 или 1\n");
            continue;
    }

    }

bool is_zero(double s1) {

    if (fabs(s1) < E)
        return true;

    else return false;

}

void clear_buffer(void) {

    while (getchar() != '\n')
        ;
}

int is_root(double a, double b, double c, double x) {

    double result = a*x*x + b*x + c;
    return (is_zero(result)) ? 1 : 0;

}

int RunOneTest(struct Test_Case test, int num) {

    double x1 = 0, x2 = 0;
    int nroots = Solvesq(test.a, test.b, test.c, &x1, &x2);

    if (nroots == test.nrootsref && is_root(1, -3, 2, x1) && is_root(1, -3, 2, x2) && fabs(x1-x2) > E) {
        printf("\nТест %d пройден\n", num);
    }
    else {
        printf("\nТест %d FAILED\na = %lg, b = %lg, c = %lg\n"
        "Expected: %d roots, x1ref = %lg, x2ref = %lg\n"
        "got:      %d roots, x1    = %lg, x2    = %lg\n",
        num, test.a, test.b, test.c, test.nrootsref, test.x1ref, test.x2ref, nroots, x1, x2);
    }
}
void RunTests() {

    int passed = 0, total = 0;
    printf("     ТЕСТЫ\n");

    struct Test_Case test1 = {.a = 1, .b = -3, .c = 2, .nrootsref = 2, .x1ref = 2, .x2ref = 1};
    RunOneTest(test1, 1);

    struct Test_Case test2 = {.a = 0, .b = 0, .c = 1, .nrootsref = 0, .x1ref = NAN, .x2ref = NAN};
    RunOneTest(test2, 2);

    struct Test_Case test3 = {.a = 0, .b = 0, .c = 2, .nrootsref = 0, .x1ref = NAN, .x2ref = NAN};
    RunOneTest(test3, 3);

    struct Test_Case test4 = {.a = 0, .b = 1, .c = 1, .nrootsref = 1, .x1ref = -1, .x2ref = NAN};
    RunOneTest(test4, 4);


    printf("\nПройдено %d из %d тестов\n", passed, total);
}







/*
void RandomTest() {
    for (int i = 0; i < TESTS; i++) {
            a = rand() % 10000 - 10000;
            b = rand() % 10000 - 10000;
            c = rand() % 10000 - 10000;

            nroots = Solvesq(a, b, c, &x1, &x2);
            int flag = 1;
            if (nroots == 1 || nroots == 2) {
                if(!is_root(a, b, c, x1))
                    flag = 0;
                if (nroots == 2 && !is_root(a, b, c, x2))
                    flag = 0;
            }
            if (flag)
                passed++;

            total++;
    }
}
*/

    /* nroots = Solvesq(1, -3, 2, &x1, &x2);
    total++;



    nroots = Solvesq(0, 0, 0, &x1, &x2);
    total++;

    if (nroots == -1) {
        passed++;
        printf("Тест 2 пройден\n");
    }
    else
        printf("Тест 2 провален\n");

    nroots = Solvesq(0, 0, 2, &x1, &x2);
    total++;

    if (nroots == 0) {
        passed++;
        printf("Тест 3 пройден\n");
    }
    else
        printf("Тест 3 провален\n");

    nroots = Solvesq(0, 1, 1, &x1, &x2);
    total++;

    if (nroots == 1 && is_root(0, 1, 1, x1)) {
        passed++;
        printf("Тест 4 пройден\n");
    }
    else
        printf("Тест 4 провален\n"); */



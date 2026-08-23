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

int main(void)
{
    srand((unsigned)time(NULL));
    RunTests();
    RandomTest();
    double a = 0, b = 0, c = 0;
    double x1 = 0, x2 = 0;
    int nroots = 0;
    if (exit_before_start() == FALSE)
        return 0;
    do {
        input(&a, &b, &c);
        nroots = Solvesq(a, b, c, &x1, &x2);
        output(nroots, x1, x2);
        } while (continuE() == TRUE);

    return 0;
}

int exit_before_start() {

    printf("Хотите завершить программу?\n"
    "Если да - введите q, если нет - что угодно\n");
    char ch = '\0';

    if (ch = getchar() == 'q') {
        printf("Программа завершена");
        return FALSE;
    }
    clear_buffer();
    return TRUE;
    /*printf("Хотите завершить программу?\n"
    "Если да - введите q, если нет - что угодно\n");

    char ch = '\0';
    while (isspace(ch = getchar())) ;
    ungetc(ch, stdin);
        if (ch == 'q') {
    while (isspace(ch = getchar()) && ch != '\n') ;
        if (ch == '\n') {
            printf("Программа завершена");
            return FALSE;
        }
        }
        else {
            clear_buffer();
            return TRUE;
        }
        */
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


void print_struct(struct Test_Case test) {

    printf("%lg, %lg, %lg, %d, %lg, %lg\n", test.a, test.b, test.c, test.nrootsRef, test.x1ref, test.x2ref);
}


int RunOneTest(struct Test_Case test, int num, int* passed, int* total) {

    double x1 = 0, x2 = 0;
    int nroots = Solvesq(test.a, test.b, test.c, &x1, &x2);
    if (!isnan(x1) && !isnan(x2)) {
        if (nroots == test.nrootsRef && is_root(test.a, test.b, test.c, x1) && is_root(test.a, test.b, test.c, x2) && fabs(x1-x2) > E) {
            printf("\n\nТест %d пройден\n", num);
            (*total)++;
            (*passed)++;
        /* if (nroots == test.nrootsRef && is_root(1, -3, 2, x1) && is_root(1, -3, 2, x2) && fabs(x1-x2) > E) {
            printf("\n\nТест %d пройден\n", num);
            (*total)++;
            (*passed)++;

        if (nroots == test.nrootsRef && x1 == test.x1ref && x2 == test.x2ref) {
            printf("\nТест %d пройден\n", num); */

        }
        else {
            printf("\n\nТест %d FAILED\na = %lg, b = %lg, c = %lg\n"
            "Expected: %d roots, x1ref = %lg, x2ref = %lg\n"
            "got:      %d roots, x1    = %lg, x2    = %lg\n",
            num, test.a, test.b, test.c, test.nrootsRef, test.x1ref, test.x2ref, nroots, x1, x2);
            (*total)++;
        }
    }
    else if (isnan(x1) && !isnan(x2)) {
        if (nroots == test.nrootsRef && is_root(test.a, test.b, test.c, x2)) {
            printf("\n\nТест %d пройден\n", num);
            (*total)++;
            (*passed)++;
        }
        else {
            printf("\n\nТест %d FAILED\na = %lg, b = %lg, c = %lg\n"
            "Expected: %d roots, x1ref = %lg, x2ref = %lg\n"
            "got:      %d roots, x1    = %lg, x2    = %lg\n",
            num, test.a, test.b, test.c, test.nrootsRef, test.x1ref, test.x2ref, nroots, x1, x2);
            (*total)++;
        }
    }
    else if (isnan(x2) && !isnan(x1)) {
        if (nroots == test.nrootsRef && is_root(test.a, test.b, test.c, x1)) {
            printf("\n\nТест %d пройден\n", num);
            (*total)++;
            (*passed)++;
        }
        else {
            printf("\n\nТест %d FAILED\na = %lg, b = %lg, c = %lg\n"
            "Expected: %d roots, x1ref = %lg, x2ref = %lg\n"
            "got:      %d roots, x1    = %lg, x2    = %lg\n",
            num, test.a, test.b, test.c, test.nrootsRef, test.x1ref, test.x2ref, nroots, x1, x2);
            (*total)++;
        }
    }
    else {
        if (nroots == test.nrootsRef) {
            printf("\n\nТест %d пройден\n", num);
            (*total)++;
            (*passed)++;
        }
        else {
            printf("\n\nТест %d FAILED\na = %lg, b = %lg, c = %lg\n"
            "Expected: %d roots, x1ref = %lg, x2ref = %lg\n"
            "got:      %d roots, x1    = %lg, x2    = %lg\n",
            num, test.a, test.b, test.c, test.nrootsRef, test.x1ref, test.x2ref, nroots, x1, x2);
            (*total)++;
        }
    }

}
void RunTests() {

    int passed = 0, total = 0;
    printf("     ТЕСТЫ\n");

    struct Test_Case test1 = {.a = 1, .b = -3, .c = 2, .nrootsRef = 2, .x1ref = 2, .x2ref = 1};
    RunOneTest(test1, 1, &passed, &total);
    print_struct(test1);

    struct Test_Case test2 = {.a = 0, .b = 0, .c = 1, .nrootsRef = 0, .x1ref = NAN, .x2ref = NAN};
    RunOneTest(test2, 2, &passed, &total);
    print_struct(test2);

    struct Test_Case test3 = {.a = 0, .b = 0, .c = 2, .nrootsRef = 0, .x1ref = NAN, .x2ref = NAN};
    RunOneTest(test3, 3, &passed, &total);
     print_struct(test3);

    struct Test_Case test4 = {.a = 0, .b = 1, .c = 1, .nrootsRef = 1, .x1ref = -1, .x2ref = NAN};
    RunOneTest(test4, 4, &passed, &total);
    print_struct(test4);

    struct Test_Case test5 = {.a = 0, .b = 0, .c = 0, .nrootsRef = -1, .x1ref = NAN, .x2ref = NAN};
    RunOneTest(test5, 5, &passed, &total);
    print_struct(test5);


    printf("\nПройдено %d из %d тестов\n", passed, total);
}


void RandomTest() {
    int total = 0;
    int passed = 0;
    double a = 0, b = 0, c = 0;
    int nroots = NAN;
    double x1 = NAN, x2 = NAN;

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
    printf("\n      РАНДОМ ТЕСТЫ\n");
    printf("Пройдено %d из %d рандом тестов\n", passed, total);
}


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



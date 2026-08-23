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

struct kv_ {
    double a, b, c;
    double x1, x2;
    double D;
    int nroots;
};

struct Test_Case {
    double a, b, c;
    int nrootsRef;
    double x1ref,  x2ref;
};


int abc_(char, double*); // чтение коэффициентов
int input(struct kv_ *); //обработка ввода
void discriminant(struct kv_ *); // вычисление дискриминанта
void Solvesq(struct kv_ *); // счет корней
void output(const struct kv_ *); // вывод корней
int continuE(void); //хочет ли пользователь продолжить
bool is_zero(double); //является ли число нулем
void clear_buffer(void); //очистка мусорной части ввода
int is_root(const struct kv_ *, double); //является ли х корнем
void RunOneTest(struct Test_Case, int, int*, int*); // ручные тесты
void RunTests(); // запуск тестов
int exit_before_start(); // проверяет хочет ли пользователь завершить программу в самом начале ввода
void print_struct(struct Test_Case); // печать содержимого структуры
void RandomTest();

int main(void)
{
    struct kv_ kv = {};
    srand((unsigned)time(NULL));
    RunTests();
    RandomTest();

    if (exit_before_start() == FALSE)
        return 0;
    do {
        input(&kv);
        Solvesq(&kv);
        output(&kv);
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
}
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

int input(struct kv_ *pt) {

    assert(pt != NULL);


    printf("Введите коэффициенты квадратного уравнения\n");


    abc_('a', &pt->a);
    abc_('b', &pt->b);
    abc_('c', &pt->c);

    return TRUE;
}

void discriminant(struct kv_ *pt) {

    assert(pt != NULL);

    pt->D = pt->b*pt->b - 4*pt->a*pt->c;

}

void Solvesq(struct kv_ *pt) {

    assert(pt != NULL);


    discriminant(pt);

    if (is_zero(pt->a)) {
        if (is_zero(pt->b)) {
            if (is_zero(pt->c)) {
                pt->x1 = NAN;
                pt->x2 = NAN;
                pt->nroots = -1;
            }
            else {
                pt->x1 = pt->x2 = NAN;
                pt->nroots = 0;
            }
        }

        else {
            pt->x2 = NAN;
            pt->x1 = -pt->c / pt->b;
            pt->nroots = 1;
        }
    }

    else {
        if (pt->D < 0) {
            pt->x1 = pt->x2 = NAN;
            pt->nroots = 0;
        }
        else if (is_zero(pt->D)) {
            pt->x2 = NAN;
            pt->x1 = -pt->b / (2*pt->a);
            pt->nroots = 1;
        }

        else {
        pt->x1 = (sqrt(pt->D) - pt->b) / (2 * pt->a);
        pt->x2 = (-sqrt(pt->D) - pt->b) / (2 * pt->a);
        pt->nroots = 2;
        }
    }

}

void output(const struct kv_ *pt) {

        switch(pt->nroots) {
            case -1:
                printf("Бесконечно много корней\n");
                break;
            case 0:
                printf("Действительных корней нет\n");
                break;
            case 1:
                printf("Один корень:   x = %lg\n", pt->x1);
                break;
            case 2:
                printf("Два корня:  x1 = %lg, x2 = %lg\n", pt->x1, pt->x2);
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

int is_root(const struct kv_ *pt, double x) {

    double result = pt->a*x*x + pt->b*x + pt->c;
    return (is_zero(result)) ? 1 : 0;
}


void print_struct(struct Test_Case test) {

    printf("%lg, %lg, %lg, %d, %lg, %lg\n", test.a, test.b, test.c, test.nrootsRef, test.x1ref, test.x2ref);
}


void RunOneTest(struct Test_Case test, int num, int* passed, int* total) {

    struct kv_ pt;
    pt.a = test.a;
    pt.b = test.b;
    pt.c = test.c;
    Solvesq(&pt);
    int nroots = pt.nroots;
    double x1 = pt.x1;
    double x2 = pt.x2;
    if (!isnan(x1) && !isnan(x2)) {
        if (nroots == test.nrootsRef && is_root(&pt, x1) && is_root(&pt, x2) && fabs(x1-x2) > E) {
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
    else if (isnan(x1) && !isnan(x2)) {
        if (nroots == test.nrootsRef && is_root(&pt, x2)) {
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
        if (nroots == test.nrootsRef && is_root(&pt, x1)) {
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

    for (int i = 0; i < TESTS; i++) {

            struct kv_ pt;
            pt.a = rand() % 20001 - 10000;
            pt.b = rand() % 20001 - 10000;
            pt.c = rand() % 20001 - 10000;

            Solvesq(&pt);

            int flag = 1;

            if (pt.nroots == 1 || pt.nroots == 2) {
                if(!is_root(&pt, pt.x1))
                    flag = 0;
                if (pt.nroots == 2 && !is_root(&pt, pt.x2))
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



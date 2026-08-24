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

// TODO: kv_eq -> KvEq
struct KvEq {
    double a, b, c;
    double x1, x2;
    double D;
    int nroots;
};

// TODO: TestCase
struct TestCase {
    double a, b, c;
    int nrootsRef;
    double x1ref,  x2ref;
};

// lowercase
int abc_(char, double*); // чтение коэффициентов
int input(struct KvEq *); //обработка ввода
void discriminant(struct KvEq *); // вычисление дискриминанта
void solve_sq(struct KvEq *); // счет корней
void output(const struct KvEq *); // вывод корней
int continuE(void); //хочет ли пользователь продолжить
bool is_zero(double); //является ли число нулем
void clear_buffer(void); //очистка мусорной части ввода
int is_root(const struct KvEq *, double); //является ли х корнем
int RunOneTest(struct TestCase, int, int*, int*); // ручные тесты
int RunTests(); // запуск тестов
int exit_before_start(); // проверяет хочет ли пользователь завершить программу в самом начале ввода
void print_struct(struct TestCase); // печать содержимого структуры
void RandomTest(); //рандом тесты
void what_test_failed(int); //какой тест провалился

int main(void)
{
    struct KvEq kv = {};

    srand((unsigned)time(NULL));

    if (!RunTests()) {
        printf("Программа завершена");
        return 0;
    }

    if (exit_before_start() == FALSE)
        return 0;
    do {
        input(&kv);
        solve_sq(&kv);
        output(&kv);
    } while (continuE() == TRUE);

    return 0;
}

int exit_before_start() {

    /* printf("\nХотите завершить программу?\n"
    "Если да - введите q, если нет - что угодно\n");
    char ch = '\0';

    if (ch = getchar() == 'q') {
        printf("Программа завершена");
        return FALSE;
    }
    clear_buffer();
    return TRUE; */


    printf("\nХотите завершить программу?\n"
    "Если да - введите q, если нет - что угодно\n");

    char ch = '\0';
    while (isspace(ch = getchar())) {
        if (ch == '\n') {
             printf("Программа завершена");
            return FALSE;
        }
    }
    ungetc(ch, stdin);
    // printf("%c", getchar());
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
    clear_buffer();
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

int input(struct KvEq *pt) {

    assert(pt != NULL);

    printf("Введите коэффициенты квадратного уравнения\n");

    abc_('a', &pt->a);
    abc_('b', &pt->b);
    abc_('c', &pt->c);

    return TRUE;
}

void discriminant(struct KvEq *pt) {

    assert(pt != NULL);

    pt->D = pt->b*pt->b - 4*pt->a*pt->c;

}

void solve_sq(struct KvEq *pt) {

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

        if (is_zero(pt->D)) {
            pt->x2 = NAN;
            pt->x1 = -pt->b / (2*pt->a);
            pt->nroots = 1;
        }

        else if (pt->D < 0) {
            pt->x1 = pt->x2 = NAN;
            pt->nroots = 0;
        }

        else {
        pt->x1 = (sqrt(pt->D) - pt->b) / (2 * pt->a);
        pt->x2 = (-sqrt(pt->D) - pt->b) / (2 * pt->a);
        pt->nroots = 2;
        }
    }

}

void output(const struct KvEq *pt) {

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

int is_root(const struct KvEq *pt, double x) {

    double result = pt->a*x*x + pt->b*x + pt->c;
    return (is_zero(result)) ? 1 : 0;
}


void print_struct(struct TestCase test) {

    printf("%lg, %lg, %lg, %d, %lg, %lg\n", test.a, test.b, test.c, test.nrootsRef, test.x1ref, test.x2ref);
}


int RunOneTest(struct TestCase test, int num, int* passed, int* total) {

    struct KvEq pt;
    pt.a = test.a;
    pt.b = test.b;
    pt.c = test.c;


    solve_sq(&pt);
    int nroots = pt.nroots;
    double x1 = pt.x1;
    double x2 = pt.x2;


    if ((!isnan(x1) && !isnan(x2) && nroots == test.nrootsRef && is_root(&pt, x1) && is_root(&pt, x2) && fabs(x1-x2) > E) ||

    (isnan(x1) && !isnan(x2) && nroots == test.nrootsRef && is_root(&pt, x2)) ||

    (isnan(x2) && !isnan(x1) && nroots == test.nrootsRef && is_root(&pt, x1)) ||

    (nroots == test.nrootsRef))
    {
        printf("\n\nТест %d пройден\n", num);
        (*total)++;
        (*passed)++;
        return TRUE;
    }

    else {
            printf("\n\nТест %d FAILED\na = %lg, b = %lg, c = %lg\n"
            "Expected: %d roots, x1ref = %lg, x2ref = %lg\n"
            "got:      %d roots, x1    = %lg, x2    = %lg\n",
            num, test.a, test.b, test.c, test.nrootsRef, test.x1ref, test.x2ref, nroots, x1, x2);
            (*total)++;
            return FALSE;
        }
}

    /*if (!isnan(x1) && !isnan(x2)) {

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
            return 0;
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
            return 0;
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
            return 0;
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
            return 0;
        }
    }
    return 1;
}
*/

void what_test_failed(int num) {

    printf("\nTEST %d FAILED\n(information higher)\n\n", num);

}

int RunTests() {

    int passed = 0, total = 0, flag = 1;
    printf("     ТЕСТЫ\n");

    struct TestCase arr[] = {  {.a = 1, .b = -3, .c = 2, .nrootsRef = 2, .x1ref = 2, .x2ref = 1},
                               {.a = 0, .b = 0, .c = 1, .nrootsRef = 0, .x1ref = NAN, .x2ref = NAN},
                               {.a = 0, .b = 0, .c = 2, .nrootsRef = 0, .x1ref = NAN, .x2ref = NAN},
                               {.a = 0, .b = 1, .c = 1, .nrootsRef = 1, .x1ref = -1, .x2ref = NAN},
                               {.a = 0, .b = 0, .c = 0, .nrootsRef = -1, .x1ref = NAN, .x2ref = NAN},
                               {.a = 1, .b = 2, .c = 1, .nrootsRef = 1, .x1ref = -1, .x2ref = NAN},
                               {.a = 1, .b = 2, .c = 3, .nrootsRef = 0, .x1ref = NAN, .x2ref = NAN},
                               {.a = 1, .b = 4, .c = 4, .nrootsRef = 1, .x1ref = -2, .x2ref = NAN},
                               {.a = 25, .b = 5, .c = 2, .nrootsRef = 0, .x1ref = NAN, .x2ref = NAN},
                               {.a = 0, .b = 5, .c = 1, .nrootsRef = 1, .x1ref = -0.2, .x2ref = NAN}

    };

    const int size = sizeof(arr)/sizeof(arr[0]);
    int tests_failed[size+1] = {};

    for (int i = 0; i < size; i++) {
        if (!RunOneTest(arr[i], i+1, &passed, &total)) {
            tests_failed[i] = i+1;
            flag = 0;
        }
        print_struct(arr[i]);
    }
    if (flag == 0) {
        printf("\nNOT ALL TESTS PASSED:\n");

        for (int i = 0; i < size; i++) {
            if (tests_failed[i] != 0)
                what_test_failed(tests_failed[i]);
        }
        return FALSE;
    }
    return TRUE;
}


    // TODO: подумать как упроcтить логику
    /* int i = 0;
    while (i < size) {
         if (!RunOneTest(arr[i], i+1, &passed, &total)) {
            flag = 0;
            tests_failed[i] = i+1;
         }
         print_struct(arr[i]);
         i++;
    }

    if (flag == 0) {
        printf("\nNOT ALL TESTS PASSED:\n");
        int i = 0;
        while (i < size) {
            if (tests_failed[i] != 0)
                what_test_failed(tests_failed[i]);
            i++;
        }
        return FALSE;
    }
    else return TRUE;
} */


void RandomTest() {

    int total = 0;
    int passed = 0;

    for (int i = 0; i < TESTS; i++) {

            struct KvEq pt;
            pt.a = rand() % 20001 - 10000;
            pt.b = rand() % 20001 - 10000;
            pt.c = rand() % 20001 - 10000;

            solve_sq(&pt);

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



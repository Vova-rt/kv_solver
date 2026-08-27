
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
int equal(double, double); // проверяет равны ли х1 и х2
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


    printf(BLUE "\nХотите завершить программу?\n"
    "Если да - введите q, если нет - что угодно" RESET "\n");

    int ch = '\0';

    while (isspace(ch = getchar())) {
        if (ch == '\n')
            return TRUE;
    }

    if (ch != 'q') {
        clear_buffer();
        return TRUE;
    }
    while (isspace(ch = getchar())) {
        if (ch == '\n') {
            printf(BLACK "Программа завершена" RESET);
            return FALSE;
        }
    }
    // printf("s");
    clear_buffer();
    return TRUE;
}

int input(struct KvEq *pt) {

    assert(pt != NULL);

    printf(PURPLE "Введите уравнение(до второй степени)" RESET "\n");
    char str[BUFF];
    char clean[BUFF];
    while (TRUE) {

        fgets(str, sizeof(str), stdin);
        unsigned int size = sizeof(str);
        int j = 0;
        int flag = 1;

        for (unsigned int i = 0; str[i]; i++) {

            assert(i < size);

            if (!isdigit(str[i]) && (str[i] != '^') && (str[i] != '+') && (str[i] != '-') &&
            (str[i] != '=') && (!isspace(str[i])) && (str[i] != 'x')) {

                    printf(RED "Ошибка ввода уравнения, попробуйте еще раз" RESET "\n");
                    flag = 0;
                    break;
                }

            if (!isspace(str[i]))
                clean[j++] = str[i];
        }

        if (flag == 0)
            continue;

        clean[j] = '\0';
        break;
    }
    int sign = 1;
    int i = 0;
    int flag_a  = 0, flag_b = 0, flag_c = 0;
    //printf("%lg", pt->a);

    while (clean[i]) {

        if (clean[i] == '+' || clean[i] == '-') {
            sign = (clean[i] == '+') ? 1 : -1;
            i++;
            // continue;
        }
        int start_num = i;

        while (clean[i] && clean[i] != '+' && clean[i] != '-')
            i++;

        char str_num[BUFF_NUM];
        strncpy(str_num, clean + start_num, i - start_num);
        str_num[i - start_num] = '\0';
        // printf("%lg\n", pt->a);

        if (strstr(str_num, "x^2")) {
            flag_a = 1;
            char* pt1 = strstr(str_num, "x^2");
            char num[BUFF_NUM];
            int len = pt1 - str_num;
            strncpy(num, str_num, len);
            num[len] = '\0';

            if (strlen(num) == 0)
                pt->a = 1.0 * sign;

            else
                pt->a = atof(num)*sign;
        }
        else if (strstr(str_num, "x")) {

            flag_b = 1;
            char* pt1 = strstr(str_num, "x");
            char num[BUFF_NUM];
            int len = pt1 - str_num;
            strncpy(num, str_num, len);
            num[len] = '\0';

            if (strlen(num) == 0)
               pt->b = 1.0*sign;
            /* else if (strcmp(num, "-") == 0)
                pt->b = -1.0;
            else if (strcmp(num, "+") == 0)
                pt->b = 1.0; */
            else
                pt->b = atof(num)*sign;
        }
        else {
            flag_c = 1;
            pt->c = atof(str_num)*sign;
        }
        if (flag_a == 0)
            //printf("%lg", pt->a);
            pt->a = 0;
        if (flag_b ==0)
            pt->b = 0;
        if (flag_c == 0)
            pt->c = 0;
    }
    printf(YELLOW "a = %lg ", pt->a);
    printf("b = %lg ", pt->b);
    printf("c = %lg" RESET "\n", pt->c);
    return TRUE;
}


/* int abc_(char s, double* pt_s) {

    assert(pt_s != NULL);

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
} */

void discriminant(struct KvEq *pt) {

    assert(pt != NULL);

    pt->D = pt->b*pt->b - 4*pt->a*pt->c;

}

void solve_eq(struct KvEq *pt) {

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
            if (is_zero(pt->x1))
                pt->x1 = 0;
            pt->nroots = 1;
        }
    }

    else {

        if (is_zero(pt->D)) {
            pt->x2 = NAN;
            pt->x1 = -pt->b / (2*pt->a);
            if (is_zero(pt->x1))
                pt->x1 = 0;
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

    assert(pt != NULL);
        switch(pt->nroots) {
            case -1:
                printf(ORANGE "Бесконечно много корней" RESET "\n");
                break;
            case 0:
                printf(ORANGE "Действительных корней нет" RESET "\n");
                break;
            case 1:
                printf(ORANGE "Один корень:   x = %lg" RESET "\n", pt->x1);
                break;
            case 2:
                printf(ORANGE "Два корня:  x1 = %lg, x2 = %lg" RESET "\n", pt->x1, pt->x2);
                break;
            default:
                printf(RED "Ошибка числ корней" RESET "\n");
        }

}
int continuE(void) {

    printf(PURPLE "Хотите продолжить?\n"
    "Введите 1 для продолжения или 0 для завершения" RESET "\n");

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
                    printf(RED "Ошибка ввода, введите 0 или 1" RESET "\n");
                    flag++;
                    break;
                }
            }
            if (flag == 0) {
                printf(BLACK "Программа завершена" RESET "\n");
                return FALSE;
            }
            else
                continue;
        }

        else if (ch == 1) {
            while((ch = getchar()) != '\n') {
                if (isspace(ch))
                    continue;

                else {
                    clear_buffer();
                    printf(RED "Ошибка ввода, введите 0 или 1" RESET "\n");
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
            printf(RED "Ошибка ввода, введите 0 или 1\n" RESET "\n");
            continue;
    }

    }

bool is_zero(double s1) {

    if (fabs(s1) < E)
        return true;

    else
        return false;

}

void clear_buffer(void) {

    while (getchar() != '\n')
        ;
}

int is_root(const struct KvEq *pt, double x) {

    assert(pt != NULL);
    double result = pt->a*x*x + pt->b*x + pt->c;
    return (is_zero(result)) ? 1 : 0;
}

int equal(double x1, double x2) {

    if (isnan(x1) && isnan(x2))
        return TRUE;
    if(isnan(x1) || isnan(x2))
        return FALSE;
    else
        return fabs(x1-x2) < E;
}

void print_struct(struct TestCase test) {

    printf("%lg, %lg, %lg, %d, %lg, %lg\n", test.a, test.b, test.c, test.nrootsRef, test.x1ref, test.x2ref);

}


int RunOneTest(struct TestCase test, int num, int* passed, int* total) {

    assert(passed != NULL);
    assert(total != NULL);

    struct KvEq hand_test;
    hand_test.a = test.a;
    hand_test.b = test.b;
    hand_test.c = test.c;

    solve_eq(&hand_test);
    int nroots = hand_test.nroots;
    double x1 = hand_test.x1;
    double x2 = hand_test.x2;

    bool eql;

    if (nroots == 2) {
        bool direct = equal(x1, test.x1ref) && equal(x2, test.x2ref);
        bool indirect = equal(x2, test.x1ref) && equal(x1, test.x2ref);
        eql = direct || indirect;
        }
    else if (nroots == 1) {
        eql = equal(x1, test.x1ref);
        }
    else
        eql = true;

    if (eql && nroots == test.nrootsRef) {
        printf("\n\n" ONLY_GREEN "Тест %d пройден" RESET "\n", num);
        (*passed)++;
        (*total)++;
        return TRUE;
    }

    else {
            printf(RED "\n\nТест %d FAILED\na = %lg, b = %lg, c = %lg\n"
            "Expected: %d roots, x1ref = %lg, x2ref = %lg\n"
            "got:      %d roots, x1    = %lg, x2    = %lg" RESET "\n",
            num, test.a, test.b, test.c, test.nrootsRef, test.x1ref, test.x2ref, nroots, x1, x2);
            (*total)++;
            return FALSE;
    }

}

void what_test_failed(int num) {

    printf(RED "\nTEST %d FAILED\n(information higher)" RESET "\n\n", num);

}

int RunTests() {

    /*struct TestCase arr[] = {  {.a = 1, .b = -3, .c = 2, .nrootsRef = 2, .x1ref = 2, .x2ref = 1},
                               {.a = 0, .b = 0, .c = 1, .nrootsRef = 0, .x1ref = NAN, .x2ref = NAN},
                               {.a = 0, .b = 0, .c = 2, .nrootsRef = 0, .x1ref = NAN, .x2ref = NAN},
                               {.a = 0, .b = 1, .c = 1, .nrootsRef = 1, .x1ref = -1, .x2ref = NAN},
                               {.a = 0, .b = 0, .c = 0, .nrootsRef = -1, .x1ref = NAN, .x2ref = NAN},
                               {.a = 1, .b = 2, .c = 1, .nrootsRef = 1, .x1ref = -1, .x2ref = NAN},
                               {.a = 1, .b = 2, .c = 3, .nrootsRef = 0, .x1ref = NAN, .x2ref = NAN},
                               {.a = 1, .b = 4, .c = 4, .nrootsRef = 1, .x1ref = -2, .x2ref = NAN},
                               {.a = 25, .b = 5, .c = 2, .nrootsRef = 0, .x1ref = NAN, .x2ref = NAN},
                               {.a = 0, .b = 5, .c = 1, .nrootsRef = 1, .x1ref = -0.2, .x2ref = NAN}
    };*/
    FILE *fp = fopen("hand_tests.txt", "r");
    if(!fp) {
        printf("Ошибка, не удалось открыть файл\n");
        return FALSE;
    }

    TestCase arr[MAX_TESTS] = {};
    int num_test = 0;
    char line[BUFF];

    while (fgets(line, sizeof(line), fp) && num_test < MAX_TESTS) {

        double a = 0, b = 0, c = 0;
        int nrootsRef = 0;
        char x1_str[BUFF_NUM], x2_str[BUFF_NUM];

        int n = sscanf(line, "%lf %lf %lf %d %s %s", &a, &b, &c, &nrootsRef, x1_str, x2_str);
        if (n != 6) {
            printf("Некорректная строка(была пропущена): %s\n", line);
            continue;
        }
        arr[num_test].a = a;
        arr[num_test].b = b;
        arr[num_test].c = c;
        arr[num_test].nrootsRef = nrootsRef;
        if ((strcmp(x1_str, "nan") || strcmp(x1_str, "NAN")) == 0)
            arr[num_test].x1ref = NAN;
        else
            arr[num_test].x1ref = atof(x1_str);
        if ((strcmp(x2_str, "nan") || strcmp(x2_str, "NAN")) == 0)
            arr[num_test].x2ref = NAN;
        else
            arr[num_test].x2ref = atof(x2_str);

        num_test++;
    }
    fclose(fp);

    int passed = 0, total = 0, flag = 1;
    printf("\n" "\033[38;2;220;80;0;47m" "    ТЕСТЫ     " RESET);

    // const int size = sizeof(arr)/sizeof(arr[0]);
    int tests_failed[num_test+1];
    for (int k = 0; k < num_test + 1; k++)
        tests_failed[k] = 0;

    for (int i = 0; i < num_test; i++) {
        if (!RunOneTest(arr[i], i+1, &passed, &total)) {
            tests_failed[i] = i+1;
            flag = 0;
        }
        print_struct(arr[i]);
    }

    if (flag == 0) {
        printf(BLACK "\nNOT ALL TESTS PASSED:" RESET "\n");

        for (int i = 0; i < num_test; i++) {
            if (tests_failed[i] != 0)
                what_test_failed(tests_failed[i]);
        }
        return FALSE;
    }
    else {
        printf("\n" GREEN "ВСЕ ТЕСТЫ ПРОЙДЕНЫ" RESET "\n");
        return TRUE;
    }

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


void RandomTests() {

    int total = 0;
    int passed = 0;

    for (int i = 0; i < TESTS; i++) {
            struct KvEq random;
            random.a = rand() % 20000 - 10000;
            random.b = rand() % 20000 - 10000;
            random.c = rand() % 20000 - 10000;

            solve_eq(&random);

            int flag = 1;

             if (random.nroots == 1 || random.nroots == 2) {
                if(!is_root(&random, random.x1))
                    flag = 0;
                if (random.nroots == 2 && !is_root(&random, random.x2))
                    flag = 0;
            }
            if (flag)
                passed++;

            total++;
            /* if ((random.nroots == 1 || random.nroots == 2) && (!is_root(&random, random.x1)) ||
            (random.nroots == 2 && !is_root(&random, random.x2)))

                    flag = 0;
            if (flag)
                passed++;
            total++; */

    }
    printf(ORANGE "\n      РАНДОМ ТЕСТЫ" RESET "\n");
    printf(GREEN "Пройдено %d из %d рандом тестов" RESET "\n", passed, total);

}






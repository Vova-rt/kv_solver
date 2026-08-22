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


int abc_(char, double*); // чтение коэффициентов
void input(double *, double *, double *); //обработка ввода
void discriminant(double , double , double, double*); // вычисление дискриминанта
int Solvesq(double, double, double, double*, double*); // счет корней
void output(int, double, double); // вывод корней
int continuE(void); //хочет ли пользователь продолжить
bool is_zero(double); //является ли число нулем
void clear_buffer(void); //очистка мусорной части ввода
int is_root(double, double, double, double); //является ли х корнем
void RunTests(); //проверка

int main(void)
{
    srand((unsigned)time(NULL));
    RunTests();

    double a = 0, b = 0, c = 0;
    double x1 = 0, x2 = 0;
    int nroots = 0;

    do {
        input(&a, &b, &c);
        nroots = Solvesq(a, b, c, &x1, &x2);
        output(nroots, x1, x2);
        } while (continuE() == TRUE);

    return 0;
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

void input(double * a, double * b, double * c) {
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
            if (is_zero(c))
                return -1;
            else
                return 0;
        }

        else {
            *x1 = -c / b;
            return 1;
        }
    }

    else {
        if (D < 0)
            return 0;
        else if (is_zero(D)) {
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
            if (flag == 0)
                return FALSE;
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

void RunTests() {

    double a, b, c, x1, x2;
    int nroots;
    int passed = 0;
    int total = 0;

    printf("     ТЕСТЫ\n");

    nroots = Solvesq(1, -3, 2, &x1, &x2);
    total++;

    if (nroots == 2 && is_root(1, -3, 2, x1) && is_root(1, -3, 2, x2) && fabs(x1-x2) > E) {
        passed++;
        printf("Тест 1 пройден\n");
    }
    else
        printf("Тест 1 провален\n");

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
        printf("Тест 4 провален\n");


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
    printf("Пройдено %d из %d тестов\n", passed, total);
}




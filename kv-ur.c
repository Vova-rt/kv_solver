#include <TXLib.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>


#define TRUE 1
#define FALSE 0
#define E 0.000001



int input(double *, double *, double *); //обработка ввода
void discriminant(double *, double *, double *, double*); // вычисление дискриминанта
int solver(double *, double *, double *, double *); //счет и вывод корней
int continuE(void); //хочет ли пользователь продолжить
bool is_zero(double*); //является ли число нулем
void clear_buffer(void); //очистка мусорной части ввода



int main(void)
{


    double a = 0, b = 0, c = 0;
    double D = 0;
    int flag = 0;


    while (true) {
        flag = input(&a, &b, &c);
        if (flag == FALSE) {
            printf("Программа завершена");
            break;
        }

        else if (flag == TRUE) {
            discriminant(&a, &b, &c, &D);
            solver(&a, &b, &c, &D);

            int j = continuE();
            if (j == TRUE)
                continue;

            else if (j == FALSE) {
                printf("Программа завершена");
                return 0;
            }

        }
    }
    return 0;
}

int input(double * a, double * b, double * c) {


    assert(a != NULL);
    assert(b != NULL);
    assert(c != NULL);


    printf("Введите коэффициенты квадратного уравнения\n");


    while(TRUE)
    {
        char ch;
        printf("\nВведите коэффициент а:\n");
        if (scanf("%lf%c", a, &ch) == 2 && isspace(ch));
        else {
            clear_buffer();
            printf("Ошибка ввода, заново введите коэффициенты\n");
            continue;
        }


        printf("\nВведите коэффициент b:\n");
        if (scanf("%lf%c", b, &ch) == 2 && isspace(ch));
        else {
            clear_buffer();
            printf("Ошибка ввода, заново введите коэффициенты\n");
            continue;
        }



        printf("\nВведите коэффициент c:\n");
        if (scanf("%lf%c", c, &ch) == 2 && isspace(ch));
        else {
            clear_buffer();
            printf("Ошибка ввода, заново введите коэффициенты\n");
            continue;
        }
        return TRUE;


    }




}



void discriminant(double* pt_a, double* pt_b, double* pt_c, double* pt_D) {

    assert(pt_a != NULL);
    assert(pt_b != NULL);
    assert(pt_c != NULL);
    assert(pt_D != NULL);

    double a = *pt_a;
    double b = *pt_b;
    double c = *pt_c;
    *pt_D = b*b - 4*a*c;

}

int solver(double* pt_a, double* pt_b, double* pt_c, double* pt_D) {


    assert(pt_a != NULL);
    assert(pt_b != NULL);
    assert(pt_c != NULL);
    assert(pt_D != NULL);

    double a = *pt_a;
    double b = *pt_b;
    double c = *pt_c;
    double D = *pt_D;

    if (is_zero(&a)) {

        if (is_zero(&b)) {

            if (is_zero(&c))
                printf("Бесконечно много корней\n");
            else
                printf("корней  нет\n");
        return 0;
        }
        else printf("это линейное уравнение, корень x0 = %lg\n", -c/b);
        return 0;

    }

    else if (is_zero(&D))
        printf("совпадающий корень: %lf\n", -b/(2*a));

    else if (D < 0)
        printf("действительных корней нет\n");

    else printf("два корня - x1 = %lg,  x2 =  %lg\n", (sqrt(D) - b) / (2 * a), (-sqrt(D) - b) / (2 * a));

    return 0;
}

int continuE(void) {

    printf("Хотите продолжить?\n"
    "Введите 1 для продолжения или 0 для завершения\n");

    while (true) {


        char ch, ch1;
        int k = scanf("%c%c", &ch, &ch1);


        if (k == 2 && ch1=='\n') {
            if (ch == '1')
                return TRUE;
             if (ch == '0')
                return FALSE;
        }
        printf("Ошибка ввода, введите 0 или 1\n");
        clear_buffer();
        continue;


    }

    }

bool is_zero(double * ptr) {

    assert(ptr != NULL);

    if (fabs(*ptr) < E)
        return true;

    else return false;
}

void clear_buffer(void) {

    while (getchar() != '\n')
        ;
}




#include <TXLib.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>


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

    printf("Введите коэффициенты квадратного уравнения\n");
    printf("Для завершения программы введите q в начале ввода\n");
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
            if (j == TRUE) {
                printf("Введите коэффициенты\n");
                continue;
            }
            else if (j == FALSE) {
                printf("Программа завершена");
                return 0;
            }

        }
    }
    return 0;
}

int input(double *pt_a, double *pt_b, double *pt_c) {

    while(true) {

        int result = 0;
        result = scanf("%lf %lf %lf", pt_a, pt_b, pt_c);

        if (result == 0 && getchar() == 'q')
            return FALSE;



        if (result == 3)
            return TRUE;

        else {
            printf("Ошибка ввода, заново введите коэффициенты\n");
            clear_buffer()
                ;
                 return 0;

        }


    }

}

void discriminant(double* pt_a, double* pt_b, double* pt_c, double* pt_D) {

    double a = *pt_a;
    double b = *pt_b;
    double c = *pt_c;
    *pt_D = b*b - 4*a*c;
}

int solver(double* pt_a, double* pt_b, double* pt_c, double* pt_D) {

    double a = *pt_a;
    double b = *pt_b;
    double c = *pt_c;
    double D = *pt_D;

    if (is_zero(&a)) {
        if (is_zero(&b))
            printf("корней  нет\n");
        else printf("это линейное уравнение, корень x0 = %lg\n", -c/b);
        return 0;

    }

    if (is_zero(&D))
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

        int flag = 0;
        scanf("%d", &flag);

        if (flag == 0 && getchar() == 'q')
            return FALSE;

        if (!isspace(getchar())) {
            clear_buffer();
            printf("Введите только 1 или 0\n");
            continue;
        }

        if (flag == 1)
            return TRUE;

        else return FALSE;

    }

    }

bool is_zero(double * ptr) {

    if (fabs(*ptr) < E)
        return true;

    else return false;
}

void clear_buffer(void) {
    while (getchar() != '\n')
        ;
}



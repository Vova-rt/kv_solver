#include "header.h"
#include "funcs.c"

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


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

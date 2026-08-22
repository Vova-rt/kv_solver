int abc_(char s, double* pt_s) {

    assert(pt_s != NULL);

    printf("\nВведите коэффициент %c:\n", s);

    /*if (scanf("%lf", pt_s) && getchar() == '\n');
    else {
        clear_buffer();
        printf("Ошибка ввода, заново введите коэффициенты\n");
        return FALSE;
    }
    return TRUE; */
    int flag = 0;
    char ch = -1;
    while (TRUE) {
        if (scanf("%lg", pt_s)) {
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
        else {
        clear_buffer();
        printf("Ошибка ввода, заново введите коэффициенты\n");
        return FALSE;
        }

    }
}

int input(double * a, double * b, double * c) {
    assert(a != NULL);
    assert(b != NULL);
    assert(c != NULL);

    printf("Введите коэффициенты квадратного уравнения\n");

    while (!abc_('a', a)) ;
    while (!abc_('b', b)) ;
    while (!abc_('c', c)) ;

    return TRUE;
}



void discriminant(double a, double b, double c, double* pt_D) {

    assert(pt_D != NULL);

    *pt_D = b*b - 4*a*c;

}

int solver(double a, double b, double c, double D) {

    if (is_zero(a)) {

        if (is_zero(b)) {

            if (is_zero(c))
                printf("Бесконечно много корней\n");
            else
                printf("корней  нет\n");
        return 0;
        }
        else printf("это линейное уравнение, корень x0 = %lg\n", -c/b);
        return 0;

    }

    else if (is_zero(D))
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

        char ch = -1;
        scanf("%c", &ch);
        int flag = 0;

        if (ch == '0') {
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

        if (ch == '1') {
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


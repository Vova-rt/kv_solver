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


    printf(PURPLE "\nХотите завершить программу?\n"
    "Если да - введите q, если нет - что угодно" RESET "\n");

    char ch = '\0';

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

    printf(PURPLE "Введите квадратное уравнение" RESET "\n");
    char clean[100];
    while (TRUE) {

        char str[100];
        fgets(str, sizeof(str), stdin);
        int j = 0;
        int flag = 1;

        for (unsigned int i = 0; i < strlen(str); i++) {
            if (!isdigit(str[i])) {
                if ((str[i] != '^') && (str[i] != '+') && (str[i] != '-') && (str[i] != '=') && (!isspace(str[i])) && (str[i] != 'x')) {
                    printf(RED "Ошибка ввода уравнения, попробуйте еще раз" RESET "\n");
                    flag = 0;
                    break;
                }
            }
            if (str[i] != ' ')
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
            continue;
        }
        int start_num = i;

        while (clean[i] && clean[i] != '+' && clean[i] != '-')
            i++;

        char str_num[60];
        strncpy(str_num, clean + start_num, i - start_num);
        str_num[i - start_num] = '\0';
        // printf("%lg\n", pt->a);
        if (strstr(str_num, "x^2")) {

            flag_a = 1;
            char* pt1 = strstr(str_num, "x^2");
            char num[60];
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
            char num[60];
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

        if (ch == 1) {
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

    else return false;

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

int is_root(double a, double b, double c, double x) {

    double result = a*x*x + b*x + c;
    return (is_zero(result)) ? 1 : 0;

}


void print_struct(struct Test_Case test) {

    printf("%lg, %lg, %lg, %d, %lg, %lg\n", test.a, test.b, test.c, test.nrootsRef, test.x1ref, test.x2ref);
}


int RunOneTest(struct Test_Case test, int num, int* passed, int* total) {

    double x1 = 0, x2 = 0;
    int nroots = Solvesq(test.a, test.b, test.c, &x1, &x2);
    if (!isnan(x1) && !isnan(x2)) {
        if (nroots == test.nrootsRef && is_root(test.a, test.b, test.c, x1) && is_root(test.a, test.b, test.c, x2) && fabs(x1-x2) > E) {
            printf("\n\nТест %d пройден\n", num);
            (*total)++;
            (*passed)++;
        /* if (nroots == test.nrootsRef && is_root(1, -3, 2, x1) && is_root(1, -3, 2, x2) && fabs(x1-x2) > E) {
            printf("\n\nТест %d пройден\n", num);
            (*total)++;
            (*passed)++;

        if (nroots == test.nrootsRef && x1 == test.x1ref && x2 == test.x2ref) {
            printf("\nТест %d пройден\n", num); */

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
        if (nroots == test.nrootsRef && is_root(test.a, test.b, test.c, x2)) {
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
        if (nroots == test.nrootsRef && is_root(test.a, test.b, test.c, x1)) {
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
    double a = 0, b = 0, c = 0;
    int nroots = NAN;
    double x1 = NAN, x2 = NAN;

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

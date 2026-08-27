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


void print_struct(struct TestCase test) {

    printf("%lg, %lg, %lg, %d, %lg, %lg\n", test.a, test.b, test.c, test.nrootsRef, test.x1ref, test.x2ref);
}


int RunOneTest(struct TestCase test, int num, int* passed, int* total) {

    assert(passed != NULL);
    assert(total != NULL);

    struct KvEq pt;
    pt.a = test.a;
    pt.b = test.b;
    pt.c = test.c;

    solve_sq(&pt);
    int nroots = pt.nroots;
    double x1 = pt.x1;
    double x2 = pt.x2;

    if ((!isnan(x1) && !isnan(x2) && nroots == test.nrootsRef && is_root(&pt, x1) && is_root(&pt, x2) && fabs(x1-x2) > E) ||

    (isnan(x1) && !isnan(x2) && nroots == test.nrootsRef && is_root(&pt, x2)) ||

    (isnan(x2) && !isnan(x1) && nroots == test.nrootsRef && is_root(&pt, x1)) ||

    (nroots == test.nrootsRef))
    {
        printf("\n\n" ONLY_GREEN "Тест %d пройден" RESET "\n", num);
        (*total)++;
        (*passed)++;
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

    /*if (!isnan(x1) && !isnan(x2)) {

        if (nroots == test.nrootsRef && is_root(&pt, x1) && is_root(&pt, x2) && fabs(x1-x2) > E) {
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
            return 0;
        }
    }
    else if (isnan(x1) && !isnan(x2)) {

        if (nroots == test.nrootsRef && is_root(&pt, x2)) {
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
            return 0;
        }
    }
    else if (isnan(x2) && !isnan(x1)) {

        if (nroots == test.nrootsRef && is_root(&pt, x1)) {
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
            return 0;
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
            return 0;
        }
    }
    return 1;
}
*/

void what_test_failed(int num) {

    printf(RED "\nTEST %d FAILED\n(information higher)" RESET "\n\n", num);

}

int RunTests() {

    struct TestCase arr[] = {  {.a = 1, .b = -3, .c = 2, .nrootsRef = 2, .x1ref = 2, .x2ref = 1},
                               {.a = 0, .b = 0, .c = 1, .nrootsRef = 0, .x1ref = NAN, .x2ref = NAN},
                               {.a = 0, .b = 0, .c = 2, .nrootsRef = 0, .x1ref = NAN, .x2ref = NAN},
                               {.a = 0, .b = 1, .c = 1, .nrootsRef = 1, .x1ref = -1, .x2ref = NAN},
                               {.a = 0, .b = 0, .c = 0, .nrootsRef = -1, .x1ref = NAN, .x2ref = NAN},
                               {.a = 1, .b = 2, .c = 1, .nrootsRef = 1, .x1ref = -1, .x2ref = NAN},
                               {.a = 1, .b = 2, .c = 3, .nrootsRef = 0, .x1ref = NAN, .x2ref = NAN},
                               {.a = 1, .b = 4, .c = 4, .nrootsRef = 1, .x1ref = -2, .x2ref = NAN},
                               {.a = 25, .b = 5, .c = 2, .nrootsRef = 0, .x1ref = NAN, .x2ref = NAN},
                               {.a = 0, .b = 5, .c = 1, .nrootsRef = 1, .x1ref = -0.2, .x2ref = NAN}
    };

    int passed = 0, total = 0, flag = 1;
    printf("\n" "\033[38;2;220;80;0;47m" "    ТЕСТЫ     " RESET);

    const int size = sizeof(arr)/sizeof(arr[0]);
    int tests_failed[size+1] = {};

    for (int i = 0; i < size; i++) {
        if (!RunOneTest(arr[i], i+1, &passed, &total)) {
            tests_failed[i] = i+1;
            flag = 0;
        }
        print_struct(arr[i]);
    }
    if (flag == 0) {
        printf(BLACK "\nNOT ALL TESTS PASSED:" RESET "\n");

        for (int i = 0; i < size; i++) {
            if (tests_failed[i] != 0)
                what_test_failed(tests_failed[i]);
        }
        return FALSE;
    }
    else
    printf("\n" GREEN "ВСЕ ТЕСТЫ ПРОЙДЕНЫ" RESET "\n");
    return TRUE;
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


void RandomTest() {

    int total = 0;
    int passed = 0;

    for (int i = 0; i < TESTS; i++) {
            struct KvEq random;
            random.a = rand() % 20000 - 10000;
            random.b = rand() % 20000 - 10000;
            random.c = rand() % 20000 - 10000;

            solve_sq(&random);

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


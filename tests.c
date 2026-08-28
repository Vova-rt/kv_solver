int equal(double x1, double x2) {

    if (isnan(x1) && isnan(x2))
        return TRUE;
    if (isnan(x1) || isnan(x2))
        return FALSE;
    else
        return (fabs(x1-x2) < E);
}

int is_str_number(char *str) {

    if (strcmp(str, "nan") == 0 || strcmp(str, "NAN") == 0)
        return TRUE;

    char *pt;
    strtod(str, &pt);
    if (pt != str && *pt == '\0')
        return TRUE;

    return FALSE;
}
void print_struct(struct TestCase test) {

    printf("%lg, %lg, %lg, %d, %lg, %lg\n", test.a, test.b, test.c, test.nrootsRef, test.x1ref, test.x2ref);

}

void what_test_failed(int num) {

    printf(RED "\nTEST %d FAILED\n(information higher)" RESET "\n\n", num);

}

void what_line_skipped(int num) {

    printf(RED "\nLINE %d WAS SKIPPED\n(information higher)" RESET "\n\n", num);

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
        eql = (direct || indirect);
        }

    else if (nroots == 1) {
        if (!isnan(x1))
            eql = equal(x1, test.x1ref) || equal(x1, test.x2ref);
        else
            eql = equal(x2, test.x1ref) || equal(x2, test.x2ref);
        }

    else
        eql = true;

    if (eql && (nroots == test.nrootsRef)) {
        printf("\n\n" ONLY_GREEN "Òåñò %d ïğîéäåí" RESET "\n", num);
        (*passed)++;
        (*total)++;
        return TRUE;
    }

    else {
            printf(RED "\n\nÒåñò %d FAILED\na = %lg, b = %lg, c = %lg\n"
            "Expected: %d roots, x1ref = %lg, x2ref = %lg\n"
            "got:      %d roots, x1    = %lg, x2    = %lg" RESET "\n",
            num, test.a, test.b, test.c, test.nrootsRef, test.x1ref, test.x2ref, nroots, x1, x2);
            (*total)++;
            return FALSE;
    }

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
        printf("Îøèáêà, íå óäàëîñü îòêğûòü ôàéë\n");
        return FALSE;
    }

    TestCase arr[MAX_TESTS] = {};
    int num_test = 0;
    char line[BUFF];
    int line_counter = 0;
    int flag = 1, skip_lines = 0;
    int lines_skipped[MAX_TESTS] = {};

    while (fgets(line, sizeof(line), fp) && num_test < MAX_TESTS) {

        line_counter++;
        double a = 0, b = 0, c = 0;
        int nrootsRef = 0;
        char x1_str[BUFF_NUM] = {}, x2_str[BUFF_NUM] = {};

        int n = sscanf(line, "%lf %lf %lf %d %s %s", &a, &b, &c, &nrootsRef, x1_str, x2_str);

        //printf("%s %d %c\n", x1_str, strlen(x1_str), x1_str[3]);
        //printf("%s\n\n", x2_str);
        if (n != 6 || !is_str_number(x1_str) || !is_str_number(x2_str)) {
            printf(ORANGE "Íåêîğğåêòíàÿ ñòğîêà, íîìåğ %d: %s(áûëà ïğîïóùåíà)" RESET "\n", line_counter, line);
            lines_skipped[skip_lines] = line_counter;
            // printf("%d", lines_skipped[skip_lines]);
            num_test++;
            skip_lines++;
            continue;
        }

        arr[num_test].a = a;
        arr[num_test].b = b;
        arr[num_test].c = c;
        arr[num_test].nrootsRef = nrootsRef;

        if ((strstr(x1_str, "nan") != NULL) || (strstr(x1_str, "NAN")) != NULL)
            arr[num_test].x1ref = NAN;
        else
            arr[num_test].x1ref = atof(x1_str);
        if ((strstr(x2_str, "nan") != NULL) || (strstr(x2_str, "NAN")) != NULL)
            arr[num_test].x2ref = NAN;
        else
            arr[num_test].x2ref = atof(x2_str);

        //printf("%lf\n", arr[num_test].x1ref);
        //printf("%lf\n\n", arr[num_test].x2ref);
        num_test++;
    }
    fclose(fp);

    /* while (fgets(line, sizeof(line), fp) && num_test < MAX_TESTS) {

        double a = 0, b = 0, c = 0, x1ref = 0, x2ref = 0;
        int nrootsRef = 0;

        int n = sscanf(line, "%lf %lf %lf %d %lf %lf", &a, &b, &c, &nrootsRef, &x1ref, &x2ref);

        printf("%lf\n", x1ref);
        printf("%lf\n\n", x2ref);
        if (n != 6) {
            flag = 0;
            printf("Íåêîğğåêòíàÿ ñòğîêà(áûëà ïğîïóùåíà): %s\n", line);
            continue;
        }
        arr[num_test].a = a;
        arr[num_test].b = b;
        arr[num_test].c = c;
        arr[num_test].nrootsRef = nrootsRef;
        arr[num_test].x1ref = x1ref;
        arr[num_test].x2ref = x2ref;

        printf("%lf\n", arr[num_test].x1ref);
        printf("%lf\n\n", arr[num_test].x2ref);
        num_test++;
    }
    fclose(fp); */


    int passed = 0, total = 0;
    printf("\n" "\033[38;2;220;80;0;47m" "    ÒÅÑÒÛ     " RESET);
    int tests_failed[MAX_TESTS] = {};

    for (int i = 0; i < num_test; i++) {
        if (!RunOneTest(arr[i], i+1, &passed, &total)) {
            tests_failed[i] = i+1;
            flag = 0;
        }
        print_struct(arr[i]);
    }

    if (!flag && !skip_lines) {
        printf(BLACK "\nNOT ALL TESTS PASSED:" RESET "\n");

        for (int i = 0; i < num_test; i++) {
            if (tests_failed[i] != 0)
                what_test_failed(tests_failed[i]);
        }
        return FALSE;
    }


    else if (flag && skip_lines) {
        printf(BLACK "\nNOT ALL TESTS PASSED due to incorrect lines in file" RESET "\n");

        for (int i = 0; i < num_test; i++) {
            if (lines_skipped[i] != 0)
                what_line_skipped(lines_skipped[i]);
        }
        return TRUE;
    }


    else if (!flag && skip_lines) {
        printf(BLACK "\nNOT ALL TESTS PASSED and there were incorrect lines in file" RESET "\n");

        for (int i = 0; i < num_test; i++) {
            if (lines_skipped[i] != 0)
                what_line_skipped(lines_skipped[i]);

            if (tests_failed[i] != 0)
                what_test_failed(tests_failed[i]);
        }
        return FALSE;


    }
    else {
        printf("\n" GREEN "ÂÑÅ ÒÅÑÒÛ ÏĞÎÉÄÅÍÛ (ÂÑÅ ÑÒĞÎÊÈ ÁÛËÈ Ñ×ÈÒÀÍÛ)" RESET "\n");
        return TRUE;
    }

}


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

    }
    printf(ORANGE "\n      ĞÀÍÄÎÌ ÒÅÑÒÛ" RESET "\n");
    printf(GREEN "Ïğîéäåíî %d èç %d ğàíäîì òåñòîâ" RESET "\n", passed, total);

}


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

    printf(YELLOW "ÄÀÍÍÛÅ ÒÅÑÒÀ %d:" RESET "\n" "%lg, %lg, %lg, %d, %lg, %lg\n\n", test.line_number, test.a, test.b, test.c,
                                                                                    test.nrootsRef, test.x1ref, test.x2ref);

}

void what_test_failed(int num) {

    printf(RED "\nTEST %d FAILED\n" RESET YELLOW "(information higher)" RESET "\n\n", num);

}

void what_line_skipped(int num) {

    printf(RED "\nLINE %d WAS SKIPPED\n" RESET YELLOW "(information higher)" RESET "\n\n", num);

}

int RunOneTest(struct TestCase test, int num, int* passed) {

    assert(passed != NULL);

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
        printf( ONLY_GREEN "Òåñò %d ïğîéäåí" RESET "\n", num);
        (*passed)++;
        return TRUE;
    }

    else {
            printf(RED "\n\nÒåñò %d FAILED:\na = %lg, b = %lg, c = %lg\n"
            "Expected: %d roots, x1ref = %lg, x2ref = %lg\n"
            "got:      %d roots, x1    = %lg, x2    = %lg" RESET "\n",
            num, test.a, test.b, test.c, test.nrootsRef, test.x1ref, test.x2ref, nroots, x1, x2);
            return FALSE;
    }

}

int RunTests() { // make function smaller + print failed random tests

    printf("\n              " "\033[38;2;220;80;0;47m" "    ÒÅÑÒÛ     " RESET);
    printf("\n" YELLOW "(íîìåğ òåñòà - íîìåğ ñòğîêè â ôàéëå òåñòîâ)\n\n" RESET);
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
            printf(ORANGE "Íåêîğğåêòíàÿ ñòğîêà, íîìåğ %d:   " RESET RED "%s" RESET ORANGE "(áûëà ïğîïóùåíà)\n" RESET
            "\n", line_counter, line);
            lines_skipped[skip_lines] = line_counter;
            // printf("%d", lines_skipped[skip_lines]);
            skip_lines++;
            continue;
        }

        arr[num_test].a = a;
        arr[num_test].b = b;
        arr[num_test].c = c;
        arr[num_test].nrootsRef = nrootsRef;
        arr[num_test].line_number = line_counter;

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
    int passed = 0;
    int tests_failed[MAX_TESTS] = {};

    for (int i = 0; i < num_test; i++) {
        if (lines_skipped[i] != i+1) {
            if (!RunOneTest(arr[i], arr[i].line_number, &passed)) {
                tests_failed[i] = i+1;
                flag = 0;
            }
        }
        print_struct(arr[i]);
    }

    printf(ORANGE "ÏĞÎÉÄÅÍÎ %d ÈÇ %d ĞÓ×ÍÛÕ ÒÅÑÒÎÂ ÈÇ ÔÀÉËÀ" RESET "\n", passed, line_counter);

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
        printf(BLACK "\nNOT ALL TESTS PASSED and there were incorrect lines in test file" RESET "\n");

        for (int i = 0; i < num_test; i++) {
            if (lines_skipped[i] != 0)
                what_line_skipped(lines_skipped[i]);

            if (tests_failed[i] != 0)
                what_test_failed(tests_failed[i]);
        }
        return FALSE;
    }
    else {
        printf("\n" GREEN "ÂÑÅ ÒÅÑÒÛ ÏĞÎÉÄÅÍÛ (ÂÑÅ ÑÒĞÎÊÈ ÒÅÑÒÎÂ ÈÇ ÔÀÉËÀ ÁÛËÈ Ñ×ÈÒÀÍÛ)" RESET "\n");
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
                if(!is_root(&random, random.x1)) {
                    printf("*\n");
                    flag = 0;
                }
                if (random.nroots == 2 && !is_root(&random, random.x2))
                    flag = 0;
            }
            total++;

            if (flag)
                passed++;

            else {
                printf(RED "\n\nÒåñò %d FAILED:\na = %lg, b = %lg, c = %lg\n"
                "got:      %d roots, x1    = %lg, x2    = %lg" RESET "\n",
                total, random.a, random.b, random.c, random.nroots, random.x1, random.x2);
            }

    }
    printf(ORANGE "\n      ĞÀÍÄÎÌ ÒÅÑÒÛ" RESET "\n");
    printf(GREEN "Ïğîéäåíî %d èç %d ğàíäîì òåñòîâ" RESET "\n", passed, total);

}


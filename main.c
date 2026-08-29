#include "header.h"
int main(void)
{
    struct KvEq main_kv ={};
    RandomTests();
    srand((unsigned)time(NULL));

    if (!RunTests()) {
        printf(BLACK "Программа завершена" RESET);
        return 0;
    }
    // RandomTests();
    if (exit_before_start() == FALSE)
        return 0;
    do {
        input(&main_kv);
        solve_eq(&main_kv);
        output(&main_kv);
    } while (continuE() == TRUE);

    return 0;
}
#include "kvadratka.c"
#include "tests.c"

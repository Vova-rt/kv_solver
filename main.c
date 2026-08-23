int main(void)
{
    srand((unsigned)time(NULL));
    RunTests();
    RandomTest();

    double a = 0, b = 0, c = 0;
    double x1 = 0, x2 = 0;
    int nroots = 0;

    if (exit_before_start() == FALSE)
        return 0;
    do {
        input(&a, &b, &c);
        nroots = Solvesq(a, b, c, &x1, &x2);
        output(nroots, x1, x2);
        } while (continuE() == TRUE);

    return 0;
}

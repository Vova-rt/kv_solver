void paint_func(struct KvEq paint) {

    double x_min = 0, x_max = 0;
    if (is_zero(paint.a)) {
        x_min = -15;
        x_max = 15;
    }
    else if (paint.D >= 0) {
        x_min = fmin(paint.x1, paint.x2) - 5;
        x_max = fmax(paint.x1, paint.x2) + 5;

        if (x_max - x_min < 1) {
            x_min -= 1;
            x_max += 1;
        }
    }

    else {
        double height = -paint.b/(2*paint.a);
        double i = 3 / (fabs(paint.a));
        if (i > 30)
            i = 30;
        if (i < 1)
            i = 1;
        x_min = height - i;
        x_max = height + i;
    }

    double step_x = (x_max-x_min) / (WIDTH - 1);
    double y[WIDTH];
    double y_min = 100000;
    double y_max = -100000;

    for (int i = 0; i < WIDTH; i++) {

        double x_cur = x_min + i * step_x;
        y[i] = paint.a * x_cur*x_cur + paint.b * x_cur + paint.c;

        if (y[i] < y_min)
            y_min = y[i];
        if (y[i] > y_max)
            y_max = y[i];
    }

    if ((y_max - y_min) < E) {
        y_min -= 1;
        y_max += 1;
    }

    double step_y = (y_max - y_min) / (HEIGHT -1);

    for (int row = 0; row < HEIGHT; row++) {

        double y_row = y_max - step_y * row;
        double y_row_nxt = y_max - step_y * (row + 1);

        for (int col = 0; col < WIDTH; col++) {

            double x_cur = x_min + col * step_x;
            double y_cur = y[col];

            int in = 0;
            if (y_cur >= y_row_nxt && y_cur <= y_row)
                in = 1;
            if (in)
                printf("*");
            else {
                int x_c = fabs(y_row) < step_y / 2;
                int y_c = fabs(x_cur) < step_x / 2;

                if (x_c && y_c)
                    printf("+");
                else if (x_c)
                    printf("-");
                else if (y_c)
                    printf("|");
                else
                    printf(" ");
            }
        }
        printf("\n");
    }
}

#include "../headers/euler.h"

void euler_cauchy(void (*fun)(double t1, double *y1, double *dy1),
                  int n, double h, double *y, double t) {
    auto *dy0 = new double[n];
    fun(t - h, y, dy0);
    //считаем точки со звездочкой (первичное вычисление)
    auto *dy1 = new double[n];
    for (int i = 0; i < n; ++i) {
        dy1[i] = y[i] + h * dy0[i];
    }
    //Уточняем результат
    auto *dy2 = new double[n];
    fun(t, dy1, dy2);
    for (int i = 0; i < n; ++i) {
        y[i] = y[i] + h / 2 * (dy0[i] + dy2[i]);
    }
    delete[] dy0;
    delete[] dy1;
    delete[] dy2;
}

void improved_euler(void (*fun)(double t1, double *y1, double *dy1),
                    int n, double h, double *y, double t) {
    auto *dy0 = new double[n];
    fun(t - h, y, dy0);
    //считаем точки со звездочкой (первичное вычисление)
    auto *dy1 = new double[n];
    for (int i = 0; i < n; ++i) {
        dy1[i] = y[i] + h / 2 * dy0[i];
    }
    //Уточняем результат
    fun(t - h / 2, dy1, dy0);
    for (int i = 0; i < n; ++i) {
        y[i] = y[i] + h * dy0[i];
    }
    delete[] dy0;
    delete[] dy1;
}

void euler(void (*fun)(double t1, double *y1, double *dy1),
           int n, double h, double *y, double t, int &iflag, int mode) {
    if (iflag != 1) {
        if (mode == EULER_CAUCHY) {
            euler_cauchy(fun, n, h, y, t);
        } else if (mode == IMPROVED) {
            improved_euler(fun, n, h, y, t);
        }
    } else {
        iflag = 0;
    }
}
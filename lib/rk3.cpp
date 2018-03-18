//
// Created by Malik Hiraev on 11.03.2018.
//

#include "../headers/rk3.h"

void rk3(void (*fun)(double t1, double *y1, double *dy1),
         int n, double h, double *y, double t, int &iflag) {
    if (iflag != 1) {
        auto *dy0 = new double[n], *dy1 = new double[n];
        auto *k1 = new double[n], *k2 = new double[n], *k3 = new double[n];
        fun(t - h, y, dy0);
        for (int i = 0; i < n; ++i) {
            k1[i] = h * dy0[i];
            //вектор-сумма для следующего вызова функции
            dy0[i] = y[i] + k1[i] / 2;
        }
        fun(t - h / 2, dy0, dy1);
        for (int i = 0; i < n; ++i) {
            k2[i] = h * dy1[i];
            //вектор-сумма для следующего вызова функции
            dy0[i] = y[i] - k1[i] + 2 * k2[i];
        }
        fun(t, dy0, dy1);
        for (int i = 0; i < n; ++i) {
            k3[i] = h * dy1[i];
            y[i] = y[i] + ((k1[i] + 4 * k2[i] + k3[i]) / 6);
        }

        delete[] dy0;
        delete[] dy1;
        delete[] k1;
        delete[] k2;
        delete[] k3;
    } else {
        iflag = 0;
    }
}
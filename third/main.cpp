#include <iostream>
#include <math.h>
#include "../headers/rkf45.h"
#include "../headers/euler.h"

double h, bottom, up, y[2], tOut, error, errors;
int iflag = 1;
double work[15];

int iwork[30], n = 2;
double accurate[11], re = 1e-8, ae = 1e-8;

char line[] = "=================================================================";

void fun(double t, double *y, double *dy) {
    dy[0] = y[1];
    dy[1] = -y[1] / 2 * t;
}

double rightFun(double t) {
    return 2*sqrt(t);
}


void setupDefaultTerms() {
    h = 0.1, bottom = 1, up = 2, tOut = bottom;
    y[0] = 0, y[1] = 1, iflag = 1, errors = 0;
}

void printEr(double tOut, int i) {
    error = abs(accurate[i] - y[0]);
    errors += error;
    printf("%.1f \t%.15f\t%.15f\t%.15f\n", tOut, y[0], accurate[i], error);
}

int main() {
    setupDefaultTerms();
    printf(" h  \t%-20s%-20s%s\n", "RKF45", "Accurate", "Errors");
    for (int i = 0; i < 11; ++i) {
        tOut = i * h;
        accurate[i] = rightFun(tOut);
        RKF45(fun, n, y, &bottom, &tOut, &re, &ae, &iflag, work, iwork);
        printEr(tOut, i);
    }
    printf("\t\t%-40s%.15f\n%s\n", "Sum of errors:", errors, line);


    setupDefaultTerms();
    printf(" h  \t%-20s%-20s%s\n", "Euler-Cauchy", "Accurate", "Errors");
    for (int i = 0; i < 11; ++i) {
        tOut = i * h;
        euler(fun, n, h, y, tOut, iflag, EULER_CAUCHY);
        printEr(tOut, i);
    }
    printf("\t\t%-40s%.15f\n%s\n", "Sum of errors:", errors, line);

}
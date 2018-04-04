#include <iostream>
#include <math.h>
#include "../headers/rkf45.h"
#include "../headers/rk3.h"

//ПАРАМЕТРЫ
double h, bottom, up, y[2], pointsNumber, tOut, error, errors, re = 1e-8, ae = 1e-8;
int iflag = 1, n = 2;

double work[15];
int iwork[30];
double accurate[11]; //Точное решение
char line[] = "=========================================================================";

//Полученная аналитическим методом систему двух ДУ 1-ого порядка
void fun(double t, double *y, double *dy) {
    dy[0] = y[1];
    dy[1] = (6*y[0])/(pow(t, 2));
}

//УСТАНОВКА ПАРАМЕТРОВ
void setup() {
    h = 0.1, bottom = 1, up = 2, tOut = bottom;
    y[0] = 1, y[1] = 3, iflag = 1, errors = 0;
    pointsNumber = (up - bottom) / h + 1;
}

//ВЫЧИСЛЕНИЕ ТОЧНОГО РЕШЕНИЯ
double rightFun(double t) {
    return pow(t, 3);
}

//ВЫВОД ПОГРЕШНОСТИ
void printEr(double tOut, int i) {
    error = abs(accurate[i] - y[0]);
    errors += error;
    printf("%.1f \t%.15f\t%.15f\t%.15f\n", tOut, y[0], accurate[i], error);
}

int main() {
    setup();

    //СЧИТАЕМ ТОЧНОЕ РЕШЕНИЕ
    for (int i = 0; i < pointsNumber; ++i) {
        tOut = i * h + 1;
        accurate[i] = rightFun(tOut);
    }

    //СЧИТАЕМ ЧЕРЕЗ RKF-45
    printf(" h  \t%-24s%-24s%s\n", "RKF-45", "Accurate", "Errors");
    for (int i = 0; i < pointsNumber; ++i) {
        tOut = i * h + 1;
        RKF45(fun, n, y, &bottom, &tOut, &re, &ae, &iflag, work, iwork);
        printEr(tOut, i);
    }
    printf("\t\t%-40s%.15f\n%s\n", "Sum of errors:", errors, line);


    setup();

    //СЧИТАЕМ ЧЕРЕЗ RK-3
    printf(" h  \t%-24s%-24s%s\n", "RK-3", "Accurate", "Errors");
    for (int i = 0; i < pointsNumber; ++i) {
        tOut = i * h + 1;
        rk3(fun, n, h, y, tOut, iflag);
        printEr(tOut, i);
    }
    printf("\t\t%-40s%.15f\n%s\n", "Sum of errors:", errors, line);
}
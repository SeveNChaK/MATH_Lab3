#include <iostream>
#include <math.h>
#include "../headers/rkf45.h"
#include "../headers/euler.h"

//Параметры
double h, bottom, up, y[2], pointsNumber, tOut, error, errors, re = 1e-8, ae = 1e-8;
int iflag = 1, n = 2;

//Рабочие массивы
double work[15];
int iwork[30];
double accurate[11];
char line[] = "=========================================================================";

//Полученная аналитическим методом систему двух ДУ 1-ого порядка
void fun(double t, double *y, double *dy) {
    dy[0] = y[1];
    dy[1] = -y[1] / (2 * t);
}

//Установка параметров
void setup() {
    h = 0.1, bottom = 1, up = 2, tOut = bottom;
    y[0] = 2, y[1] = 1, iflag = 1, errors = 0;
    pointsNumber = (up - bottom) / h + 1;

}

//Точное решение
double rightFun(double t) {
    return 2 * sqrt(t);
}

//Функция, выводящая в консоль погрешность полученного решения, относительно точного решения
void printEr(double tOut, int i) {
    error = abs(accurate[i] - y[0]);
    errors += error;
    printf("%.1f \t%.15f\t%.15f\t%.15f\n", tOut, y[0], accurate[i], error);
}

int main() {
    setup();
    for (int i = 0; i < pointsNumber; ++i) {
        tOut = i * h + 1;
        accurate[i] = rightFun(tOut);
    }

    //Считаем через RKF45
    printf(" h  \t%-24s%-24s%s\n", "RKF45", "Accurate", "Errors");
    for (int i = 0; i < pointsNumber; ++i) {
        tOut = i * h + 1;
        RKF45(fun, n, y, &bottom, &tOut, &re, &ae, &iflag, work, iwork);
        printEr(tOut, i);
    }
    printf("\t\t%-40s%.15f\n%s\n", "Sum of errors:", errors, line);


    setup();
    //Считаем методом Эйлера-Коши
    printf(" h  \t%-24s%-24s%s\n", "Euler-Cauchy", "Accurate", "Errors");
    for (int i = 0; i < pointsNumber; ++i) {
        tOut = i * h + 1;
        euler(fun, n, h, y, tOut, iflag, EULER_CAUCHY);
        printEr(tOut, i);
    }
    printf("\t\t%-40s%.15f\n%s\n", "Sum of errors:", errors, line);

}
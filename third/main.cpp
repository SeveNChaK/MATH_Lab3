#include <iostream>
#include <math.h>
#include "../headers/rkf45.h"
#include "../headers/rk3.h"

//ÏÀĞÀÌÅÒĞÛ
double h, bottom, bottom2, up, y[2], y2[2], pointsNumber, tOut, error, error2, errors, errors2, re = 1e-8, ae = 1e-8;
int iflag = 1, iflag2 = 1, n = 2;

double work[15], work2[15];
int iwork[30], iwork2[30];
double accurate[11]; //Òî÷íîå ğåøåíèå
char line[] = "=========================================================================";

//Ïîëó÷åííàÿ àíàëèòè÷åñêèì ìåòîäîì ñèñòåìó äâóõ ÄÓ 1-îãî ïîğÿäêà
void fun(double t, double *y, double *dy) {
    dy[0] = y[1];
    dy[1] = (6 * y[0]) / (pow(t, 2));
}

//ÓÑÒÀÍÎÂÊÀ ÏÀĞÀÌÅÒĞÎÂ
void setup() {
    h = 0.1, bottom = 1, up = 2, tOut = bottom;
    bottom2 = 1;
    y[0] = 1, y[1] = 3, iflag = 1, errors = 0;
    y2[0] = 1, y2[1] = 3, iflag2 = 1, errors2 = 0;
    pointsNumber = (up - bottom) / h + 1;
}

//ÂÛ×ÈÑËÅÍÈÅ ÒÎ×ÍÎÃÎ ĞÅØÅÍÈß
double rightFun(double t) {
    return pow(t, 3);
}

//ÂÛÂÎÄ ÃËÎÁÀËÜÍÎÉ ÏÎÃĞÅØÍÎÑÒÈ
void printEr(double tOut, int i) {
    error = accurate[i] - y[0];
    errors += abs(error);
    printf("%.1f \t%.15f\t%.15f\t%.25f\t", tOut, y[0], accurate[i], error);
}

//ÂÛÂÎÄ ËÎÊÀËÜÍÎÉ ÏÎÃĞÅØÍÎÑÒÈ
void printLoc(int i) {
    error2 = accurate[i] - y2[0];
    printf("%.15f %i\n", error2, iflag2);
}

int main() {
    setup();

    //Ñ×ÈÒÀÅÌ ÒÎ×ÍÎÅ ĞÅØÅÍÈÅ
    for (int i = 0; i < pointsNumber; i++) {
        tOut = i * h + 1;
        accurate[i] = rightFun(tOut);
    }

    //Ñ×ÈÒÀÅÌ ×ÅĞÅÇ RKF-45
    printf(" h  \t%-24s%-24s%-24s%s\n", "RKF-45", "Accurate", "Global Errors", "Local Errors");
    for (int i = 0; i < pointsNumber; ++i) {
        tOut = i * h + 1;
        RKF45(fun, n, y, &bottom, &tOut, &re, &ae, &iflag, work, iwork);
        if (iflag2 == 2) {
            y2[0] = accurate[i - 1];
            y2[1] = accurate[i - 1];
        }
        RKF45(fun, n, y2, &bottom2, &tOut, &re, &ae, &iflag2, work2, iwork2);
        printEr(tOut, i);
        printLoc(i);
    }
    printf("\n");

    setup();

    //Ñ×ÈÒÀÅÌ ×ÅĞÅÇ RK-3
    printf(" h  \t%-24s%-24s%-24s%s\n", "RK-3", "Accurate", "Global Errors", "Local Errors");
    for (int i = 0; i < pointsNumber; i++) {
        tOut = i * h + 1;
        rk3(fun, n, h, y, tOut, iflag);
        if (iflag2 == 0) {
            y2[0] = accurate[i - 1];
            y2[1] = accurate[i - 1];
        }
        rk3(fun, n, h, y2, tOut, iflag2);
        printEr(tOut, i);
        printLoc(i);
    }
}
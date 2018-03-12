// тестовая программа trkf45_1
//интегрирование сду, описывающей две интегрирующие цепочки,  
//включенные последовательно с постоянными Т=1сек
// вход - единичный перепад,переменые состояния - напряжения на
//конденсаторах
#include "rkf45.h"
#include <cmath>
#include <iostream>
#include <clocale>
#include <fstream>
#include <iomanip>
#include "Euler.h"
#include "Euler_Koshi.h"
#include <stdio.h>

#include <iomanip>

using namespace std;

void MyFunc(double t, double *y, double *dy) {
    dy[0] = y[1];
    dy[1] = -y[1] / 2 * t;

    return;
}

int main() {
    double RKFY0[100];
    double RKFY1[100];
    double EULERY0[100];
    double EULERY1[100];
    double EULER_KOSHI_Y0[100];
    double EULER_KOSHI_Y1[100];
    int Negn = 2;
    int iwork[30];
    double work[15];
    double Y0[] = {5.0, 4.0};
    double T0 = 2.0;
    double RE = 1e-8;
    double AE = 1e-8;
    int iflag = 1;
    double tout = 2.0;
    double h = 0.1;


    cout << "\nRKF45\n";
    cout.precision(10);
    for (int i = 0; i <= 10; i++) {
        RKF45(MyFunc, Negn, Y0, &T0, &tout, &RE, &AE, &iflag, work, iwork);
        cout << "\t" << setw(8) << left << "Y0[0] = " << Y0[0] << "\t\t" << "Y0[1]=" << Y0[1] << "\t\t" << "iflag="
             << iflag << endl;
        RKFY0[i] = Y0[0];
        RKFY1[i] = Y0[1];
        tout += h;
    }

    cout << "\r\n Method of Eiler \n";
    //Тут будет усовершенствованный метод кривых Эйлера
    //********************************************
    T0 = 2.0;
    tout = 2.0;
    Y0[0] = 5.0;
    Y0[1] = 4.0;
    for (int i = 0; i <= 10; i++) {
        euler(MyFunc, Negn, h, Y0, T0, tout);
        cout << "\t " << setw(8) << left << "Y0[0] = " << setw(15) << left << Y0[0] << "Y0[1] = " << Y0[1] << endl;
        EULERY0[i] = Y0[0];
        EULERY1[i] = Y0[1];
        tout += h;
        Y0[0] = 5.0;
        Y0[1] = 4.0;
    }

    cout << "\r\n Method of Eiler-Koshi \n";
    //Тут будет усовершенствованный метод кривых Эйлера
    //********************************************
    T0 = 2.0;
    tout = 2.0;
    Y0[0] = 5.0;
    Y0[1] = 4.0;
    for (int i = 0; i <= 10; i++) {
        euler_koshi(MyFunc, Negn, h, Y0, T0, tout);
        cout << "\t " << setw(8) << left << "Y0[0] = " << setw(15) << left << Y0[0] << "Y0[1] = " << Y0[1] << endl;
        EULER_KOSHI_Y0[i] = Y0[0];
        EULER_KOSHI_Y1[i] = Y0[1];
        tout += h;
        Y0[0] = 5.0;
        Y0[1] = 4.0;
    }


    //********************************************
    //Точное решение
    cout.precision(10);
    cout << "\n Certain solution \n";
    T0 = 2.0;
    h = 0.1;

    double resultY0[11], resultY1[11];
    for (int i = 0; i <= 10; i++) {
        resultY0[i] = (T0 * T0 + 1);
        resultY1[i] = (2 * T0);
        T0 += h;
    }
    for (int i = 0; i <= 10; i++) {
        cout << "\t" << setw(8) << left << "Y0[0] = " << setw(20) << resultY0[i] << "Y0[1] = " << resultY1[i] << endl;
    }

    cout << "Pogrescnosti:" << endl;
    for (int i = 0; i <= 10; i++)
        cout << "\t" << setw(10) << left << "Er RKFY0 = " << setw(20) << abs(RKFY0[i]) - abs(resultY0[i])
             << "Er RKFY1 = " << abs(RKFY1[i]) - abs(resultY1[i]) << endl;

    cout << endl;

    for (int i = 0; i <= 10; i++)
        cout << "\t" << setw(10) << left << "Er EULERY0 = " << setw(20) << abs(EULERY0[i]) - abs(resultY0[i])
             << "Er EULERY1 = " << abs(EULERY1[i]) - abs(resultY1[i]) << endl;

    cout << endl;

    for (int i = 0; i <= 10; i++)
        cout << "\t" << setw(10) << left << "Er EULER_KOSHI_Y0 = " << setw(20)
             << abs(EULER_KOSHI_Y0[i]) - abs(resultY0[i])
             << "Er EULER_KOSHI_Y1 = " << abs(EULER_KOSHI_Y1[i]) - abs(resultY1[i]) << endl;

    cout << endl;


    return 0;


}
// rkf45.h

#ifndef _RKF45
#define _RKF45

/**
 *
 * @param F 		функция F(T, X, DX)
 * @param NEQN 		кол-во интегрируемых уравнений
 * @param Y 		вектор решения размерностью N
 * @param T 		начальное значение независимой переменной (при нормальном выходе это TOUT)
 * @param TOUT 		точка выхода по независимой переменной
 * @param RELERR 	граница относительной погрешности
 * @param ABSERR 	граница абсолютной погрешности
 * @param IFLAG 	указатель режима интегрирования. При первом обращении - 1.
 * 					При послеующих обращениях - 2. Нормальное выходное значение - 2.
 * 					Другие значения при выходе говорят о возникшей ошибке.
 * @param WORK 		рабочий вещественный массив размерность 6NEQN + 3
 * @param IWORK 	рабочий массив, размерности не менее 5
 */


void RKF45(void (*F)(double t1, double *y1, double *dy1),
           int NEQN, double *Y, double *T, double *TOUT,
           double *RELERR, double *ABSERR,
           int *IFLAG, double *WORK, int *IWORK);

#endif


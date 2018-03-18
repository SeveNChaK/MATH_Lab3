//
// Created by Malik Hiraev on 11.03.2018.
//

#ifndef CALC_TRAPEZOIDAL_H
#define CALC_TRAPEZOIDAL_H
#define EULER_CAUCHY 0
#define IMPROVED 1

/** МЕТОД ЭЙЛЕРА-КОШИ И УЛУЧШЕННЫЙ МЕТОД
 *  РЕШЕНИЯ ОБЫКНОВЕННЫХ
 *  ДИФФЕРЕНЦИАЛЬНЫХ УРАВНЕНИЙ.
 *
 * @param fun - функция, работающая с векторами
 * @param n - кол-во уравнений
 * @param h - шаг
 * @param y - при первом вызове - начальные условния,
 *            при последующих - результат предыдущего вызова euler/trapezoidal/improved_euler
 * @param t - точка, в которой происходяит вычисление
 * @param iflag - если расчет начинается с точки, где
 *                определены начальные условия,
 *                то 1 (после первого же вызова значение автоматически поменяется),
 *                если расчет идет не с токи, где определены начальные условия, то
 *                любое другое число
 * @param mode - режим, если 0, то будет использоват метод трапеций (Эйлера-Коши),
 *               если 1, то будет использован улучшенный метод ломаных Эйлера
 *
 *
 * Можно также вызывать самостоятельно trapezoidal и improved_euler
 */

void euler(void (*fun)(double t1, double *y1, double *dy1),
           int n, double h, double *y, double t, int &iflag, int mode);

void euler_cauchy(void (*fun)(double t1, double *y1, double *dy1),
                  int n, double h, double *y, double t);

void improved_euler(void (*fun)(double t1, double *y1, double *dy1),
                    int n, double h, double *y, double t);

#endif //CALC_TRAPEZOIDAL_H

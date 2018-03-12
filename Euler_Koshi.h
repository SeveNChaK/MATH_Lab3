#ifndef _EULER_KOSHI
#define _EULER_KOSHI

void euler_koshi(void(*F)(double t1,double* y1, double* dy1), int n, double h, double * y, double t, double tout);

#endif

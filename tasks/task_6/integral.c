#include "integral.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static double trapezoidal(double (*f)(double), double a, double b, double eps) {
    int n = 2;
    double h = (b - a) / n;
    double prev = 0.0, curr;

    double sum = (f(a) + f(b)) / 2.0;
    for (int i = 1; i < n; i++) sum += f(a + i * h);
    prev = sum * h;

    while (1) {
        n *= 2;
        h = (b - a) / n;
        sum = 0.0;
        for (int i = 1; i < n; i += 2) sum += f(a + i * h);
        curr = prev / 2.0 + h * sum;

        if (fabs(curr - prev) < eps) break;
        prev = curr;
    }

    return curr;
}

// ln(1+x)/x dx
static double f_a(double x) {
    if (x == 0.0) return 1.0;
    return log(1 + x) / x;
}
u_status_t integral_a(double eps, double *res) {
    if (!res) return U_INVALID_FORMAT;
    if (eps <= 0) return U_NEGATIVE_NOT_ALLOWED;
    *res = trapezoidal(f_a, 0.0, 1.0, eps);
    return U_OK;
}

// e^(-x²/2) dx
static double f_b(double x) {
    return exp(-x * x / 2.0);
}
u_status_t integral_b(double eps, double *res) {
    if (!res) return U_INVALID_FORMAT;
    if (eps <= 0) return U_NEGATIVE_NOT_ALLOWED;
    *res = trapezoidal(f_b, 0.0, 1.0, eps);
    return U_OK;
}

// ln(1/(1-x)) dx = -ln(1-x) dx
static double f_c(double x) {
    if (x == 1.0) return INFINITY;
    return -log(1 - x);
}
u_status_t integral_c(double eps, double *res) {
    if (!res) return U_INVALID_FORMAT;
    if (eps <= 0) return U_NEGATIVE_NOT_ALLOWED;
    double delta = 1e-8;
    *res = trapezoidal(f_c, 0.0, 1.0 - delta, eps);
    return U_OK;
}


// x^x dx
static double f_d(double x) {
    if (x == 0.0) return 1.0;
    return pow(x, x);
}
u_status_t integral_d(double eps, double *res) {
    if (!res) return U_INVALID_FORMAT;
    if (eps <= 0) return U_NEGATIVE_NOT_ALLOWED;
    *res = trapezoidal(f_d, 0.0, 1.0, eps);
    return U_OK;
}

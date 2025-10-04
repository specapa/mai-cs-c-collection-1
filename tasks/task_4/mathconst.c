#include "mathconst.h"
#include <math.h>
#include <stdlib.h>


double e_in_x_pow(double x, double eps) {
    double sum = 1.0;
    double term = 1.0;
    int n = 1;
    while (fabs(term) > eps) {
        term *= x / n;   // x^n / n!
        sum += term;
        n++;
        if (n > 1000000) {
            break;
        }
    }
    return sum;
}

static inline u_status_t overflow(double eps, double val, double *res, double *res_eps) {
    *res = val;
    *res_eps = eps;
    return U_OVERFLOW;
}

//  число e 

// предел (1+1/n)^n
u_status_t compute_e_limit(double eps, double *res, double *res_eps) {
    if (!res) return U_INVALID_FORMAT;
    double prev = 0.0;
    double val = 0.0;
    for (long n = 1; ; n++) {
        val = pow(1.0 + 1.0/n, n);
        if (fabs(val - prev) < eps) break;
        if (n > 1e10) return overflow(fabs(val - prev), val, res, res_eps);
        prev = val;
    }
    *res = val;
    *res_eps = eps;
    return U_OK;
}

// ряд 1/n!
u_status_t compute_e_series(double eps, double *res, double *res_eps) {
    if (!res) return U_INVALID_FORMAT;
    double sum = 1.0;
    double term = 1.0;
    for (int n = 1; ; n++) {
        term /= n;
        if (term < eps) break;
        if (n > 1e10) return overflow(term, sum, res, res_eps);
        sum += term;
    }
    *res = sum;
    *res_eps = eps;
    return U_OK;
}

// уравнение ln(x) = 1, решаем методом ньютона
u_status_t compute_e_equation(double eps, double *res,  double *res_eps) {
    if (!res) return U_INVALID_FORMAT;
    double x = 2.0;
    for (int i = 0; ; i++) {
        double fx = log(x) - 1.0;
        double dfx = 1.0/x;
        double x1 = x - fx/dfx;
        if (fabs(x1 - x) < eps) {
            *res = x1;
            *res_eps = eps;
            return U_OK;
        }
        if (i > 1e10) return overflow(fabs(x1 - x), x1, res, res_eps);
        x = x1;
    }
    return U_OVERFLOW;
}

//  число pi 

u_status_t compute_pi_limit(double eps, double *res,  double *res_eps) {
    if (!res) return U_INVALID_FORMAT;
    double prev = 0.0;
    double val = 0.0;

    for (int n = 1; ; n++) {
        double num = pow(2.0, n) * tgamma(n + 1);   // 2^n * n!
        num = pow(num, 4);                          // (2^n * n!)^4
        double denom = n * pow(tgamma(2*n + 1), 2); // n * ((2n)!)^2
        val = num / denom;
        if (fabs(val - prev) < eps) break;
        if (n > 47) return overflow(fabs(val - prev), val, res, res_eps);
        prev = val;
    }

    *res = val;
    *res_eps = eps;
    return U_OK;
}

// предел для числа пи через логарифмы
u_status_t compute_pi_limit_ln(double eps, double *res, double *res_eps) {
    if (!res) return U_INVALID_FORMAT;
    double prev = 0.0;
    double val = 0.0;

    for (int n = 2; ; n++) {
        double log_num = 4.0 * (n * log(2.0) + lgamma(n + 1.0));
        double log_denom = log((double)n) + 2.0 * lgamma(2.0 * n + 1.0);
        double log_val = log_num - log_denom;
        val = e_in_x_pow(log_val, eps);
        if (fabs(val - prev) < eps) break;
        if (n > 1e6) return overflow(fabs(val - prev), val, res, res_eps);
        prev = val;
    }
    *res = val;
    *res_eps = eps;
    return U_OK;
}

// ряд 4 * sum((-1)^(n-1)/(2n-1))
u_status_t compute_pi_series(double eps, double *res, double *res_eps) {
    if (!res) return U_INVALID_FORMAT;
    double sum = 0.0;
    for (int n = 1; ; n++) {
        double term = 4.0 * ( (n%2 ? 1.0 : -1.0) / (2.0*n - 1.0));
        sum += term;
        if (fabs(term) < eps) break;
        if (n > 1e6) return overflow(fabs(term), sum, res, res_eps);;
    }
    *res = sum;
    *res_eps = eps;
    return U_OK;
}

// уравнение cos(x) = -1
u_status_t compute_pi_equation(double eps, double *res, double *res_eps) {
    if (!res) return U_INVALID_FORMAT;
    double x = 3.0;
    for (int i = 0; ; i++) {
        double fx = cos(x) + 1.0;
        double dfx = -sin(x);
        double x1 = x - fx/dfx;
        if (fabs(x1 - x) < eps) {
            *res = x1;
            *res_eps = eps;
            return U_OK;
        }
        if (i > 1e10) return overflow(fabs(x1 - x), x, res, res_eps);;
        x = x1;
    }
}

//  ln2 

// предел n*(2^(1/n)-1)
u_status_t compute_ln2_limit(double eps, double *res, double *res_eps) {
    if (!res) return U_INVALID_FORMAT;
    double prev = 0.0;
    double val = 0.0;
    for (int n = 1; ; n++) {
        val = n * (pow(2.0, 1.0/n) - 1.0);
        if (fabs(val - prev) < eps) break;
        if (n > 1e10) return overflow(fabs(val - prev), val, res, res_eps);;
        prev = val;
    }
    *res = val;
    *res_eps = eps;
    return U_OK;
}

// ряд sum((-1)^(n-1)/n)
u_status_t compute_ln2_series(double eps, double *res, double *res_eps) {
    if (!res) return U_INVALID_FORMAT;
    double sum = 0.0;
    for (int n = 1; ; n++) {
        double term = ( (n%2 ? 1.0 : -1.0) / (double)n );
        sum += term;
        if (fabs(term) < eps) break;
        if (n > 1e10) return overflow(fabs(term), sum, res, res_eps);
    }
    *res = sum;
    *res_eps = eps;
    return U_OK;
}

// уравнение e^x = 2
u_status_t compute_ln2_equation(double eps, double *res, double *res_eps) {
    if (!res) return U_INVALID_FORMAT;
    double x = 1.0;
    for (int i = 0; ; i++) {
        double fx = e_in_x_pow(x, eps) - 2.0;
        double dfx = e_in_x_pow(x, eps);
        double x1 = x - fx/dfx;
        if (fabs(x1 - x) < eps) {
            *res = x1;
            *res_eps = eps;
            return U_OK;
        }
        if (i > 10e6) return overflow(fabs(x1 - x), x1, res, res_eps);
        x = x1;
    }
    return U_OVERFLOW;
}

//  sqrt2 

// предел x_{n+1} = x_n - x_n^2/2 + 1
u_status_t compute_sqrt2_limit(double eps, double *res, double *res_eps) {
    if (!res) return U_INVALID_FORMAT;
    double x = 0.5;
    for (int i = 0; i < 100000; i++) {
        double x1 = x - (x*x)/2.0 + 1.0;
        if (fabs(x1 - x) < eps) {
            *res = x1;
            *res_eps = eps;
            return U_OK;
        }
        if (i > 10e6) return overflow(fabs(x1 - x), x1, res, res_eps);
        x = x1;
    }
    return U_OVERFLOW;
}

// ряд product 2^(2^-k)
u_status_t compute_sqrt2_series(double eps, double *res, double *res_eps) {
    if (!res) return U_INVALID_FORMAT;
    double prod = 1.0;
    for (int k = 2; ; k++) {
        double factor = pow(2.0, pow(2.0, -k));
        prod *= factor;
        if (fabs(factor - 1.0) < eps) break;
        if (k > 1e10) return overflow(fabs(factor - 1), prod, res, res_eps);
    }
    *res = prod;
    *res_eps = eps;
    return U_OK;
}

// уравнение x^2 = 2
u_status_t compute_sqrt2_equation(double eps, double *res, double *res_eps) {
    if (!res) return U_INVALID_FORMAT;
    double x = 1.0;
    for (int i = 0; ; i++) {
        double fx = x*x - 2.0;
        double dfx = 2.0*x;
        double x1 = x - fx/dfx;
        if (fabs(x1 - x) < eps) {
            *res = x1;
            *res_eps = eps;
            return U_OK;
        }
        if (i > 10e6) return overflow(fabs(x1 - x), x1, res, res_eps);
        x = x1;
    }
    return U_OVERFLOW;
}

//  gamma 

// предел sum(1/k) - ln(m)
u_status_t compute_gamma_limit(double eps, double *res, double *res_eps) {
    if (!res) return U_INVALID_FORMAT;
    double sum = 0.0;
    double val = 0.0;
    double prev = 0.0;
    for (int m = 1; ; m++) {
        sum += 1.0/m;
        val = sum - log((double)m);
        if (fabs(val - prev) < eps) break;
        if (m > 1e10) return overflow(fabs(val - prev), val, res, res_eps);
        prev = val;
    }
    *res = val;
    *res_eps = eps;
    return U_OK;
}

// gamma = -pi^2/6 + sum_{k=2..inf} ( 1/floor(sqrt(k))^2 - 1/k )
u_status_t compute_gamma_series(double eps, double *res, double *res_eps, double pi) {
    if (!res) return U_INVALID_FORMAT;
    double sum = - (pi * pi) / 6.0;
    double prev_block_sum = sum;
    int k = 2;
    const int S_MAX = 46340; // (s+1)^2 не переполнило int
    for (int s = 1; ; ++s) {
        int start_k = s * s;
        if (start_k < 2) start_k = 2; // ряд начинается с k = 2
        int end_k = (s + 1) * (s + 1) - 1; // конец блока для данного s
        if (k < start_k) k = start_k;
        for (; k <= end_k; ++k) {
            double term = 1.0 / ((double)s * (double)s) - 1.0 / (double)k;
            sum += term;
            if (k > 10e7) return U_OVERFLOW;
        }
        if (fabs(sum - prev_block_sum) < eps) {
            *res = sum;
            *res_eps = eps;
            return U_OK;
        }
        if (s > S_MAX - 1) return overflow(fabs(sum - prev_block_sum), sum, res, res_eps);
        prev_block_sum = sum;
    }
    return U_OVERFLOW;
}

// e^-x = lim ln t * product((p-1)/p)
// решаем относительно x
u_status_t compute_gamma_equation(double eps, double *res, double *res_eps) {
    if (!res) return U_INVALID_FORMAT;
    double val = 0.0;
    double prev = 0.0;
    for (int t = 10; ; t *= 2) {
        // считаем произведение по простым до t
        double prod = 1.0;
        for (int p = 2; p <= t; p++) {
            int prime = 1;
            for (int d = 2; d*d <= p; d++) {
                if (p % d == 0) { prime = 0; break; }
            }
            if (prime) {
                prod *= (double)(p-1)/p;
            }
        }
        val = log((double)t) * prod;
        double x = -log(val); // решаем e^-x = val
        if (fabs(x - prev) < eps) {
            break;
        }
        if (t > 1e6) return overflow(fabs(x - prev), val, res, res_eps);
        prev = x;
    }
    *res = val;
    *res_eps = eps;
    return U_OK;
}


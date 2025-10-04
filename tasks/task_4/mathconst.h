#ifndef MATHCONST_H
#define MATHCONST_H

#include <stddef.h>
#include "../../include/utils.h"

// функции для числа e
u_status_t compute_e_limit(double eps, double *res, double *res_eps);
u_status_t compute_e_series(double eps, double *res, double *res_eps);
u_status_t compute_e_equation(double eps, double *res, double *res_eps);

// функции для числа pi
u_status_t compute_pi_limit(double eps, double *res, double *res_eps);
u_status_t compute_pi_limit_ln(double eps, double *res, double *res_eps);
u_status_t compute_pi_series(double eps, double *res, double *res_eps);
u_status_t compute_pi_equation(double eps, double *res, double *res_eps);

// функции для ln2
u_status_t compute_ln2_limit(double eps, double *res, double *res_eps);
u_status_t compute_ln2_series(double eps, double *res, double *res_eps);
u_status_t compute_ln2_equation(double eps, double *res, double *res_eps);

// функции для sqrt2
u_status_t compute_sqrt2_limit(double eps, double *res, double *res_eps);
u_status_t compute_sqrt2_series(double eps, double *res, double *res_eps);
u_status_t compute_sqrt2_equation(double eps, double *res, double *res_eps);

// функции для gamma
u_status_t compute_gamma_limit(double eps, double *res, double *res_eps);
u_status_t compute_gamma_series(double eps, double *res, double *res_eps, double pi);
u_status_t compute_gamma_equation(double eps, double *res, double *res_eps);

#endif

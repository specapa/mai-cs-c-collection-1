#ifndef MATH_OPS_H
#define MATH_OPS_H

#include <stddef.h>
#include <stdio.h>

typedef enum {
    STATUS_OK = 0,
    STATUS_INVALID_ARGUMENT,
    STATUS_OVERFLOW,
    STATUS_MEMORY_ERROR,
    STATUS_RANGE_ERROR
} status_t;

/*  -h: вывести в поток натуральные числа в пределах 100 включительно, кратные x
    - Returns STATUS_OK or STATUS_INVALID_ARGUMENT.
    - Output to provided FILE*.
*/
status_t op_multiples_up_to_100(long long x, FILE *out);

/*  -p: определить, является ли число x простым; является ли x составным
    - For x <= 1: return STATUS_INVALID_ARGUMENT (1 and non-positive are neither prime nor composite).
    - result: is_prime (1) / is_composite (2) return out_kind: 1 prime, 2 composite.
    - Output to provided FILE*.
*/
status_t op_prime_test(long long x, int *out_kind);

/*  -s: разделить число x на отдельные цифры системы счисления с основанием 
    16 и вывести отдельно каждую цифру числа, разделяя их пробелом, от 
    старших разрядов к младшим, без ведущих нулей в строковом 
    представлении; 
    For negative x prints leading '-' then digits.
    - Output to provided FILE*.
*/
status_t op_split_hex_digits(long long x, FILE *out);

/*  -e: вывести таблицу степеней (для всех показателей в диапазоне от 1 до x) 
    оснований от 1 до 10; для этого флага работает ограничение на вводимое 
    число: x должен быть не больше 10; 
    - Output to provided FILE*.
*/
status_t op_print_power_table(int x, FILE *out);

/*  -a: вычислить сумму всех натуральных чисел от 1 до x и вывести полученное 
    значение в консоль;  
    - Output to provided FILE*.
*/
status_t op_sum_1_to_x(long long x, unsigned long long *out_sum);

/* -f: вычислить факториал x и вывести полученное значение в консоль.
   Return factorial via out_fact or STATUS_OVERFLOW.
*/
status_t op_factorial(long long x, unsigned long long *out_fact);

#endif /* MATH_OPS_H */
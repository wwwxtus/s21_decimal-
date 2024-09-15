#ifndef DECIMAL_H
#define DECIMAL_H

#include <stdio.h>
#include <stdlib.h>

typedef struct decimal{
    int bits[4];
} s21_decimal;


void info_decimal(s21_decimal decimal);

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int get_sign(s21_decimal value);

int s21_negate(s21_decimal value, s21_decimal *result);

void set_opposite_sign(s21_decimal *value, int pos_or_neg);


#endif
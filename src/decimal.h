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

int get_complement(s21_decimal value, s21_decimal *result);

void set_opposite_sign(s21_decimal *value, int pos_or_neg);

void pause(void);

void set_sign_pos(s21_decimal *value);

void set_sign_neg(s21_decimal *value);



#endif
#ifndef DECIMAL_H
#define DECIMAL_H

#include <stdio.h>
#include <stdlib.h>

#define POSITIVE 0
#define NEGATIVE 1

typedef struct decimal {
    int bits[4];
} s21_decimal;

void info_decimal(s21_decimal decimal);

int add_binary(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int get_sign(s21_decimal value);

int get_complement(s21_decimal value, s21_decimal *result);

void set_opposite_sign(s21_decimal *value, int pos_or_neg);

void pause(void);

void set_sign_pos(s21_decimal *value);

void set_sign_neg(s21_decimal *value);

void shift_decimal_left(s21_decimal *value, int shift);

void level_exponent(s21_decimal *value_1, s21_decimal *value_2);

int get_exponent(s21_decimal value);

void get_zero(s21_decimal *value);

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

void printDecimal(const s21_decimal *dec);

void s21_clear_decimal(s21_decimal *decimal);

s21_decimal s21_decimal_get_one(void);

int s21_negate(s21_decimal value, s21_decimal *result);

void shift_decimal_right(s21_decimal *value, int shift);

void set_exponent(s21_decimal *value, int exp);

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_is_equal(s21_decimal value_1, s21_decimal value_2);

#endif
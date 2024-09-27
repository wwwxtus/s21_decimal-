#ifndef DECIMAL_H
#define DECIMAL_H

#include <stdio.h>
#include <stdlib.h>

#define POSITIVE 0
#define NEGATIVE 1


typedef struct decimal {
    int bits[4];
} s21_decimal;

enum errors{
    OK = 0,
    TOO_LARGE = 1,
    TOO_SMALL = 2,
    DIVISION_BY_ZERO = 3,
};

//Хз что за функции
void set_opposite_sign(s21_decimal *value, int pos_or_neg);
void get_zero(s21_decimal *value);
void s21_clear_decimal(s21_decimal *decimal);
s21_decimal s21_decimal_get_one(void);


//Дебаг
void pause(void);
void info_decimal(s21_decimal decimal);
void printDecimal(const s21_decimal *dec);

//Получение значений из децимала
int get_sign(s21_decimal value);
int get_complement(s21_decimal value, s21_decimal *result);
int get_exponent(s21_decimal value);

//Сдвиги
void shift_decimal_right(s21_decimal *value, int shift);
void shift_decimal_left(s21_decimal *value, int shift);

//Функции арифметики
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int add_binary(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
void level_exponent(s21_decimal *value_1, s21_decimal *value_2);
void set_exponent(s21_decimal *value, int exp);
void set_sign_pos(s21_decimal *value);
void set_sign_neg(s21_decimal *value);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int whole_division(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
void s21_truncate (s21_decimal value, s21_decimal *result);

//Функции для сравнения чисел
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_helper(s21_decimal value_1, s21_decimal value_2);
int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
int get_bit(s21_decimal decimal, int bit_position);
int bitwise_comparison(s21_decimal value_1, s21_decimal value_2);

//Функции преобразования из/в другие типы данных
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);


//Округление
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);

//Подру-у-у-учны-ы-ы-ы-й
void get_float_part(s21_decimal value, s21_decimal *float_part);
int is_even(s21_decimal value);

#endif
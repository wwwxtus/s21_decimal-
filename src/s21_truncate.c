#include "decimal.h"

void s21_truncate(s21_decimal value, s21_decimal *result){
    int exponent = get_exponent(value);
    int y = exponent - 1;

    s21_decimal TEN = {0xA, 0x0, 0x0, 0x0};
    set_exponent(&TEN, exponent - y);
    level_exponent(&value, &TEN);
    long_division(value, TEN, result);

    set_exponent(result, 0);
}

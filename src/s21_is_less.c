#include "decimal.h"

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
    int flag = 0;
    if (s21_is_less_helper(value_1, value_2) == 2) {
        flag = 1;
    } else {
        flag = 0;
    }

    return flag;
}
#include "decimal.h"

int bitwise_comparison(s21_decimal value_1, s21_decimal value_2) {
    int flag = 0;
    int bit1 = 0;
    int bit2 = 0;
    for (int i = 95; !flag && i >= 0; --i) {
        bit1 = get_bit(value_1, i);
        bit2 = get_bit(value_2, i);
        if (bit1 > bit2) {
            flag = 1;
        } else if (bit1 < bit2) {
            flag = 2;
        }
    }

    return flag;
}


int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
    int flag = 0;
    if (s21_is_less_helper(value_1, value_2) == 2) {
        flag = 1;
    } else {
        flag = 0;
    }

    return flag;
}
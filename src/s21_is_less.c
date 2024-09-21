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

int s21_is_less_helper(s21_decimal value_1, s21_decimal value_2) {
    int result = 0;
    int value_sign_1 = get_sign(value_1);
    int value_sign_2 = get_sign(value_2);
    
    if (value_sign_1 == NEGATIVE && value_sign_2 == POSITIVE) {
        result = 2;
    } else if (value_sign_1 == POSITIVE && value_sign_2 == NEGATIVE) {
        result = 0;
    } else if (value_sign_1 == POSITIVE && value_sign_2 == POSITIVE){
        result = bitwise_comparison(value_1, value_2);
    } else if (value_sign_1 == NEGATIVE && value_sign_2 == NEGATIVE) {
        result = bitwise_comparison(value_1, value_2);
        if (result == 1) {
            result = 2;
        } else if (result == 2) {
            result = 1;
        }
    } else if (value_1.bits[0] == 0 && value_1.bits[1] == 0 && value_1.bits[2] == 0 && 
    value_2.bits[0] == 0 && value_2.bits[1] == 0 && value_2.bits[2] == 0) {
        result = 0;
    }

    return result;
}

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
    if (s21_is_less_helper(value_1, value_2) == 2) {
        return 1;
    } else {
        return 0;
    }
}
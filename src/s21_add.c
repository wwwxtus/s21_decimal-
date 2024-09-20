#include "decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int err_code = 0;
    int value_sign_1 = get_sign(value_1);
    int value_sign_2 = get_sign(value_2);

    if (value_sign_1 == POSITIVE && value_sign_2 == POSITIVE) {
        add_binary(value_1, value_2, result);
    } else if (value_sign_1 == POSITIVE && value_sign_2 == NEGATIVE) {
        s21_sub(value_1, value_2, result);
    } else if (value_sign_1 == NEGATIVE && value_sign_2 == NEGATIVE) {
        s21_sub(value_2, value_1, result);
    } else if (value_sign_1 == NEGATIVE && value_sign_2 == NEGATIVE) {
        set_sign_pos(&value_1);
        set_sign_pos(&value_2);
        add_binary(value_1, value_2, result);
        set_sign_neg(result);
    }

    return err_code;
}
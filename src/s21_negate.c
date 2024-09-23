#include "decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
    if (get_sign(value) == 0) {
        set_sign_neg(result);
    }

    if (get_sign(value) == 1) {
        set_sign_pos(result);
    }
}
#include "decimal.h"

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
    if (get_sign(value_1) != get_sign(value_2)) {
        return 0;
    }

    for (int i = 0; i < 3; ++i) {
        if ((value_1.bits[i] ^ value_2.bits[i]) != 0) {
            return 0;
        } 
    }

    return 1;
}
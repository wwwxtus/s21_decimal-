#include "decimal.h"

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
    int result = 0;
    int value_sign_1 = get_sign(value_1);
    int value_sign_2 = get_sign(value_2);
    
    if (value_sign_1 == 1 && value_sign_2 == 0) {
        result = 1;
    } else if (value_sign_1 == 1 && value_sign_2 == 0) {
        result = 0;
    } else {
        for (int i = 3; i > 0; --i) {

        }
    }
}
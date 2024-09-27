#include "decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {

    int value_sign = get_sign(value);

    s21_decimal ZERO = {0x0, 0x0, 0x0, 0x0};
    s21_decimal ONE = {0x1, 0x0, 0x0, 0x0};
    s21_decimal HALF = {0x5, 0x0, 0x0, 0x00010000};
    s21_decimal whole_part = {0x0, 0x0, 0x0, 0x0};
    s21_decimal whole_part_temp = {0x0, 0x0, 0x0, 0x0};
    s21_decimal float_part = {0x0, 0x0, 0x0, 0x0};

    set_sign_pos(&value);
    s21_truncate(value, &whole_part);
    get_float_part(value, &float_part);

    level_exponent(&float_part, &HALF);
    
    if(s21_is_equal(float_part, HALF)){
        if(is_even(whole_part)){
            
        }else{
            s21_add(whole_part, ONE, &whole_part);
        }
    }else if(s21_is_greater(float_part, HALF)){
        s21_add(whole_part, ONE, &whole_part);
    }

    *result = whole_part;

    if(value_sign && !s21_is_equal(whole_part, ZERO)){
        set_sign_neg(result);
    }
}

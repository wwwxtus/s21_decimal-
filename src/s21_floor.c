#include "decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
    
    int value_sign = get_sign(value);

    s21_decimal ZERO = {0x0, 0x0, 0x0, 0x0};
    s21_decimal ONE = {0x1, 0x0, 0x0, 0x0};
    s21_decimal whole_part = {0x0, 0x0, 0x0, 0x0};
    s21_decimal whole_part_temp = {0x0, 0x0, 0x0, 0x0};
    s21_decimal float_part = {0x0, 0x0, 0x0, 0x0};

    if(!value_sign){
        s21_truncate(value, result);
    }

    if(value_sign){

        set_sign_pos(&value);
        s21_truncate(value, &whole_part);
        get_float_part(value, &float_part);


        if(s21_is_greater(float_part, ZERO)){
            s21_add(whole_part, ONE, &whole_part);
        }

        s21_add(*result, whole_part, result);

        s21_negate(*result, result);
    }


}

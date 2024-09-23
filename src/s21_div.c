#include "decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result){

    s21_decimal ONE = {0x1, 0x0, 0x0, 0x0};

    s21_decimal dividend = value_1;
    s21_decimal divisor = value_2;

    int dividend_sign = get_sign(dividend);
    int divisor_sign = get_sign(divisor);
    set_sign_pos(&dividend);
    set_sign_pos(&divisor);

    set_exponent(&ONE, get_exponent(dividend));
    set_exponent(result, get_exponent(dividend));

    while(s21_is_greater_or_equal(dividend, divisor)){
        s21_sub(dividend, divisor, &dividend);
        s21_add(*result, ONE, result);
    }


    if(dividend_sign != divisor_sign){
        set_sign_neg(result);
    }else if(dividend_sign && divisor_sign){
        set_sign_pos(result);
    }


}

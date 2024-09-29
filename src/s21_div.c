#include "decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result){

    s21_decimal ONE = {0x1, 0x0, 0x0, 0x0};
    s21_decimal ZERO = {0x0, 0x0, 0x0, 0x0};
    s21_decimal EXPONENT_UTIL = {0x0, 0x0, 0x0, 0x0};

    s21_decimal dividend = value_1;
    s21_decimal divisor = value_2;

    int dividend_sign = get_sign(dividend);
    int divisor_sign = get_sign(divisor);
    set_sign_pos(&dividend);
    set_sign_pos(&divisor);

    set_exponent(&ONE, get_exponent(dividend));
    set_exponent(result, get_exponent(dividend));
    set_exponent(&ZERO, get_exponent(dividend));

    set_exponent(&EXPONENT_UTIL, 15);

    level_exponent(&dividend, &EXPONENT_UTIL);


    while(s21_is_greater_or_equal(dividend, divisor)){
        s21_sub(dividend, divisor, &dividend);
        s21_add(*result, ONE, result);
    }


    // s21_decimal remainder = dividend;
    // set_exponent(&EXPONENT_UTIL, 5);
    // level_exponent(&remainder, &EXPONENT_UTIL);
    // level_exponent(result, &EXPONENT_UTIL);
    // level_exponent(&divisor, &EXPONENT_UTIL);

    // while(s21_is_greater_or_equal(remainder, divisor)){
    //     s21_sub(remainder, divisor, &remainder);
    //     s21_add(*result, ONE, result);
    // }


    if(dividend_sign != divisor_sign){
        set_sign_neg(result);
    }else if(dividend_sign && divisor_sign){
        set_sign_pos(result);
    }
}

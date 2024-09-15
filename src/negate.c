#include "decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result){

    
    s21_decimal one = {0x0, 0x0, 0x0, 0x1};
    
    int sign = get_sign(value);

    if(sign == 0){
        result->bits[0] = value.bits[0];
        result->bits[1] = ~value.bits[1];
        result->bits[2] = ~value.bits[2];
        result->bits[3] = ~value.bits[3];
        
        result->bits[0] = ~(result->bits[0]) ^ 2147483647U;
        s21_add(*result, one, result);
    }else if (sign == 1){

        s21_decimal one_inverted;
        one_inverted.bits[0] = one.bits[0]; 
        one_inverted.bits[1] = ~one.bits[1];
        one_inverted.bits[2] = ~one.bits[2];
        one_inverted.bits[3] = ~one.bits[3];

        s21_add(one_inverted, one, &one_inverted);

        result->bits[0] = value.bits[0];
        result->bits[1] = ~value.bits[1];
        result->bits[2] = ~value.bits[2];
        result->bits[3] = ~value.bits[3];

        result->bits[0] = result->bits[0] & 2147483647U;
        s21_add(*result, one, result);
    }



}
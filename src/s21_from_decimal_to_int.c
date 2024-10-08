#include "decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {

    int err_code = 0;

    if(get_exponent(src) > 0){
            s21_decimal truncated;
            get_zero(&truncated);
            s21_truncate(src, &truncated);
            src = truncated;
        }

    if(src.bits[2] == 0 && src.bits[1] == 0){

        int src_sign = get_sign(src);
        
        if(src_sign){
            *dst = ~(src.bits[0]) + 1;
        }else{
            *dst = src.bits[0];
        }

    }else{
        err_code = 1;
    }

    return err_code;

}
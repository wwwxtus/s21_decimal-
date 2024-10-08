#include "decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst){
    get_zero(dst);

    int INT_MAX = 0x7FFFFFFF;
    int INT_MIN = 0x80000000;

    int src_sign = src < 0 ? 1 : 0;
    
    dst->bits[0] = src;

    if(src_sign){
        dst->bits[0] = ~dst->bits[0] + 1;
        set_sign_neg(dst);
    }

}

#include "decimal.h"

void binary_search_div(s21_decimal value1, s21_decimal value2, s21_decimal *result) { 

    set_sign_pos(result);
    set_sign_pos(&value1);
    set_sign_pos(&value2);

    s21_decimal dividend = value1;
    s21_decimal divisor = value2;

    s21_decimal low = {0x0, 0x0, 0x0, 0x0};
    s21_decimal high = dividend;
    s21_decimal mid = {0x0, 0x0, 0x0, 0x0};
    s21_decimal ONE = {0x1, 0x0, 0x0, 0x0};

    while(s21_is_less_or_equal(low, high)){

        // mid = (low + high) / 2;
        s21_decimal high_minus_low;
        s21_sub(high, low, &high_minus_low);
        shift_decimal_right(&high_minus_low, 1);
        s21_add(low, high_minus_low, &mid);
        //

        // mid_times_divisor = mid * divisor
        s21_decimal mid_times_divisor;
        s21_mul(mid, divisor, &mid_times_divisor);
        //

        if(s21_is_greater(mid_times_divisor, dividend)){
            // high = mid - 1
            s21_sub(mid, ONE, &high);
            //

        }else{
            
            *result = mid;
            // low = mid + 1
            s21_add(mid, ONE, &low);
            //
        }

        // info_decimal(low);
        // info_decimal(high);
        // info_decimal(mid);
        // pause();

    }


}

#include "decimal.h"

int is_correct_decimal(s21_decimal decimal) {
    if(get_exponent(decimal) > 0x7F || get_exponent(decimal) < 0x0) {
        return 0;
    }
    return 1;
}

int max_exp(s21_decimal value){
    s21_decimal EXPONENT_UTIL = {0x0, 0x0, 0x0, 0x0};
    s21_decimal value_copy = value;
    int num_len = get_normalized_len(value);
    set_exponent(&EXPONENT_UTIL, 28);

    int i_exponent = 28;
    while(level_exponent(&value_copy, &EXPONENT_UTIL)){
        i_exponent--;
        set_exponent(&EXPONENT_UTIL, i_exponent);
        value_copy = value;
    }

    return i_exponent;
}


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
        // mid = low + (high - low) / 2;
        s21_decimal high_minus_low;
        s21_sub(high, low, &high_minus_low);
        shift_decimal_right(&high_minus_low, 1);
        s21_add(low, high_minus_low, &mid);

        // mid_times_divisor = mid * divisor
        s21_decimal mid_times_divisor;
        s21_mul(mid, divisor, &mid_times_divisor);

        if(s21_is_greater(mid_times_divisor, dividend)){
            // high = mid - 1
            s21_sub(mid, ONE, &high);
        }else{
            *result = mid;
            // low = mid + 1
            s21_add(mid, ONE, &low);
        }

        // info_decimal(low);
        // info_decimal(high);
        // info_decimal(mid);
        // pause();
    }
}

int s21_div_remainder(s21_decimal value_1, s21_decimal value_2, s21_decimal *quotient, s21_decimal *remainder) {
    s21_decimal number = *quotient;
    s21_decimal tmp;
    s21_decimal tmp_remainder = *remainder;

    int count = 0;
    int check = max_exp(number);

    printf("check %d\n", check);

    s21_decimal ten = {0xA, 0x0, 0x0, 0x0};
    s21_decimal zero = {0x0, 0x0, 0x0, 0x0};

    s21_decimal check_remainder = *remainder;
    while (count < 28 && !s21_is_equal(tmp_remainder, zero)) {
        s21_decimal number_stored = number;
        s21_decimal remainder_stored = tmp_remainder; 

        s21_mul(number, ten, &number);
        s21_decimal help_rem;
        s21_mul(tmp_remainder, ten, &tmp_remainder);
        binary_search_div(tmp_remainder, value_2, &help_rem);
        s21_add(number, help_rem, &number);

        s21_decimal help;
        s21_mul(help_rem, value_2, &help);
        s21_sub(tmp_remainder, help, &tmp_remainder);

        if (!is_correct_decimal(number)) {
            number = number_stored;
            tmp_remainder = remainder_stored;
            break;
        }

        ++count;
        printf("Count: %d\n", count);
    }

    *quotient = number;
    *remainder = tmp_remainder;

    return count;
}

int s21_div_handle(s21_decimal value_2, s21_decimal res, s21_decimal remainder, s21_decimal *result) {
    int code = 0;
    int power1 = s21_div_remainder(value_2, value_2, &res, &remainder);

    s21_decimal tmp_res;
    get_zero(&tmp_res);
    int power2 = s21_div_remainder(value_2, value_2, &tmp_res, &remainder);

    return code;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int count = 0;
    get_zero(result);

    int sign1 = get_sign(value_1);
    int sign2 = get_sign(value_2);

    s21_decimal remainder;
    s21_decimal res;

    binary_search_div(value_1, value_2, &res);
    
    s21_decimal help;
    s21_mul(res, value_2, &help);
    s21_sub(value_1, help, &remainder);

    count = s21_div_remainder(value_1, value_2, &res, &remainder);
    *result = res;
    set_exponent(result, count);

    if (sign1 != sign2) {
        set_sign_neg(result);
    }
    
    return 0;
}
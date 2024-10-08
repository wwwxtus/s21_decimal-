#include "decimal.h"

int is_correct_decimal(s21_decimal decimal) {
    if (get_exponent(decimal) > 0x7F || get_exponent(decimal) < 0x0) {
        return 0;
    }
    return 1;
}

int max_exp(s21_decimal value) {
    s21_decimal EXPONENT_UTIL = {0x0, 0x0, 0x0, 0x0};
    s21_decimal value_copy = value;
    int num_len = get_normalized_len(value);
    set_exponent(&EXPONENT_UTIL, 28);

    int i_exponent = 28;
    while (level_exponent(&value_copy, &EXPONENT_UTIL)) {
        i_exponent--;
        set_exponent(&EXPONENT_UTIL, i_exponent);
        value_copy = value;
    }

    return i_exponent;
}

// void binary_search_div(s21_decimal value1, s21_decimal value2, s21_decimal *result) {
//     set_sign_pos(result);
//     set_sign_pos(&value1);
//     set_sign_pos(&value2);

//     s21_decimal dividend = value1;
//     s21_decimal divisor = value2;

//     s21_decimal low = {0x0, 0x0, 0x0, 0x0};
//     s21_decimal high = dividend;
//     s21_decimal mid = {0x0, 0x0, 0x0, 0x0};
//     s21_decimal ONE = {0x1, 0x0, 0x0, 0x0};

//     while (s21_is_less(low, high)) {
//         // mid = low + (high - low) / 2;
//         s21_decimal high_minus_low;
//         s21_sub(high, low, &high_minus_low);
//         shift_decimal_right(&high_minus_low, 1);
//         add_binary(low, high_minus_low, &mid);

//         info_decimal(mid);
//         pause();

//         // mid_times_divisor = mid * divisor
//         s21_decimal mid_times_divisor;

//         s21_mul(mid, divisor, &mid_times_divisor);


//         if (s21_is_greater(mid_times_divisor, dividend)) {
//             // high = mid - 1
//             s21_sub(mid, ONE, &high);
//         } else {
//             *result = mid;
//             // low = mid + 1
//             add_binary(mid, ONE, &low);
//         }

//         info_decimal(low);
//         info_decimal(high);
//         info_decimal(mid);
//         printf("EQUAL OR NOT: %d\n", s21_is_less_or_equal(low, high));
//         pause();
//     }
// }

int s21_div_remainder(s21_decimal value_1, s21_decimal value_2, s21_decimal *quotient,
                      s21_decimal *remainder) {
    s21_decimal number = *quotient;
    s21_decimal tmp;
    s21_decimal tmp_remainder = *remainder;
    s21_decimal ONE = {0x1, 0x0, 0x0, 0x0};
    s21_decimal ZERO = {0x0, 0x0, 0x0, 0x0};

    int count = 0;

    int check = s21_is_equal(number, ZERO) ? 0 : 28 - max_exp(number) + 1;

    // int check = 28 - max_exp(number) + 1;

    printf("check %d\n", check);

    s21_decimal ten = {0xA, 0x0, 0x0, 0x0};
    s21_decimal zero = {0x0, 0x0, 0x0, 0x0};

    s21_decimal check_remainder = *remainder;
    s21_decimal mid = {0x8, 0x0, 0x0, 0x0};
    while (count < 28 && !s21_is_equal(tmp_remainder, zero)) {
        s21_decimal res_tmp_remainder;
        get_zero(&res_tmp_remainder);

        s21_mul(number, ten, &number);
        s21_decimal help_rem;
        s21_mul(tmp_remainder, ten, &res_tmp_remainder);
        long_division(res_tmp_remainder, value_2, &help_rem);

        tmp_remainder = res_tmp_remainder;

        s21_decimal tmp_help_rem = help_rem;
        // info_decimal(help_rem);

        if (!s21_is_equal(help_rem, zero)) {
            check += (28 - max_exp(help_rem) + 1);
        }
        printf("check %d\n", check);

        s21_add(number, help_rem, &number);

        s21_decimal help;
        s21_mul(help_rem, value_2, &help);
        // info_decimal(help);

        if (!s21_is_equal(help, zero)) {
            s21_sub(tmp_remainder, help, &res_tmp_remainder);
            tmp_remainder = res_tmp_remainder;
        }

        
        // info_decimal(tmp_remainder);
        ++count;
        printf("Count: %d\n", count);

        if (check == 28) {
            s21_decimal res_tmp_remainder;
            get_zero(&res_tmp_remainder);

            s21_mul(tmp_remainder, ten, &res_tmp_remainder);
            long_division(res_tmp_remainder, value_2, &help_rem);
            if (s21_is_greater(help_rem, mid)) {
                s21_add(number, ONE, &number);
            }

            break;
        }
        if (check > 28) {
            break;
        }

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
    printf("Good result");
    printf("Good result");
    printf("Good result");
    printf("Good result");
    printf("Good result");

    s21_decimal zero;
    get_zero(&zero);

    if (s21_is_equal(zero, value_2)) {
        printf("Error: Division by zero\n");
        return 1;
    } else {
        int count = 0;
        get_zero(result);

        int sign1 = get_sign(value_1);
        int sign2 = get_sign(value_2);

        int exp1 = get_exponent(value_1);
        int exp2 = get_exponent(value_2);

        set_exponent(&value_1, 0);
        set_exponent(&value_2, 0);

        s21_decimal remainder;
        s21_decimal res;

        remainder = long_division(value_1, value_2, &res);

        // s21_decimal help;

        // get_zero(&help);

        // s21_mul(res, value_2, &help);

        // s21_sub(value_1, help, &remainder);

        count = s21_div_remainder(value_1, value_2, &res, &remainder);
        *result = res;
        if (exp1 == 0 && exp2 == 0) {
            set_exponent(result, count);
        } else {
            int exp_max = s21_max(exp1, exp2);
            int exp_min = s21_min(exp1, exp2);
            set_exponent(result, exp_max - exp_min + count);
        }
        if (sign1 != sign2) {
            set_sign_neg(result);
        }
    }

    return 0;
}


s21_decimal long_division(s21_decimal dividend, s21_decimal divisor, s21_decimal *result){
    s21_decimal Q = {0x0, 0x0, 0x0, 0x0};
    s21_decimal R = {0x0, 0x0, 0x0, 0x0};

    for(int i = 95; i >= 0; i--){
        shift_decimal_left(&R, 1);
        int dividend_bit = get_bit(dividend, i);
        R.bits[0] |= dividend_bit;

        if(s21_is_greater_or_equal(R, divisor)){
            
            s21_decimal temp_R;
            s21_sub(R, divisor, &temp_R);
            R = temp_R;

            s21_decimal ONE = {0x1, 0x0, 0x0, 0x0};

            shift_decimal_left(&ONE, i);
            Q.bits[0] |= ONE.bits[0];
            Q.bits[1] |= ONE.bits[1];
            Q.bits[2] |= ONE.bits[2];

        }
    }

    *result = Q;

    return R;
}
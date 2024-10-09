#include "decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int err_code = 0;
    int value_sign_1 = get_sign(value_1);
    int value_sign_2 = get_sign(value_2);

    if (value_sign_1 == POSITIVE && value_sign_2 == POSITIVE) {
        s21_decimal temp_res = {0, 0, 0, 0};
        s21_decimal value_temp = {0, 0, 0, 0};
        s21_decimal ten = {0xA, 0x0, 0x0, 0x0};

        int original_exponent_v1 = get_exponent(value_1);
        int original_exponent_v2 = get_exponent(value_2);

        int max_exp_v1 = max_exp(value_1);
        int max_exp_v2 = max_exp(value_2);

        if(max_exp_v1 > max_exp_v2 - get_normalized_len(value_2)){
            for(int i = 0; i <= max_exp_v1 - max_exp_v2; i++){
                long_division(value_1, ten, &value_1);
                original_exponent_v1 -= 1;
                set_exponent(&value_1, original_exponent_v1);
            }
        }

        if(max_exp_v2 > max_exp_v1){
            for(int i = 0; i <= max_exp_v2 - max_exp_v1 + 1; i++){
                long_division(value_2, ten, &value_2);
                original_exponent_v2 -= 1;
                set_exponent(&value_2, original_exponent_v2);
            }
        }

        info_decimal(value_1);
        info_decimal(value_2);
        pause();

        if(level_exponent(&value_1, &value_2)){
            printf("Error: Overflow\n");
        }

        info_decimal(value_1);
        info_decimal(value_2);
        pause();
        
        add_binary(value_1, value_2, result);
    } else if (value_sign_1 == POSITIVE && value_sign_2 == NEGATIVE) {
        set_sign_pos(&value_2);
        s21_sub(value_1, value_2, result);
    } else if (value_sign_1 == NEGATIVE && value_sign_2 == POSITIVE) {
        set_sign_pos(&value_1);
        s21_sub(value_2, value_1, result);
    } else if (value_sign_1 == NEGATIVE && value_sign_2 == NEGATIVE) {
        set_sign_pos(&value_1);
        set_sign_pos(&value_2);

        s21_decimal temp_res = {0, 0, 0, 0};
        s21_decimal value_temp = {0, 0, 0, 0};
        s21_decimal ten = {0xA, 0x0, 0x0, 0x0};

        int original_exponent_v1 = get_exponent(value_1);
        int original_exponent_v2 = get_exponent(value_2);

        int max_exp_v1 = max_exp(value_1);
        int max_exp_v2 = max_exp(value_2);

        if(s21_is_greater(value_1, value_2) ){
            for(int i = 0; i <= max_exp_v1 - max_exp_v2; i++){
                long_division(value_1, ten, &value_1);
                original_exponent_v1 -= 1;
                set_exponent(&value_1, original_exponent_v1);
            }
        }

        if(s21_is_greater(value_2, value_1) ){
            for(int i = 0; i <= max_exp_v2 - max_exp_v1; i++){
                long_division(value_2, ten, &value_2);
                original_exponent_v2 -= 1;
                set_exponent(&value_2, original_exponent_v2);
            }
        }

        add_binary(value_1, value_2, result);
        set_sign_neg(result);
    }

    return err_code;
}
#include "decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result){

    int value1_sign = get_sign(value_1);
    int value2_sign = get_sign(value_2);

    s21_decimal value_1n;
    s21_decimal value_2n;
    s21_decimal result_temp;

    set_sign_pos(&value_1);
    set_sign_pos(&value_2);
    
    get_zero(&value_1n);
    get_zero(&value_2n);
    get_zero(result);
    get_zero(&result_temp);

    set_exponent(&value_1n, get_exponent(value_1));
    set_exponent(&value_2n, get_exponent(value_1));
    set_exponent(result, get_exponent(value_1));
    set_exponent(&result_temp, get_exponent(value_1));

    for(int i = 0; i < 94; i += 2){

        //Первое промежуточное число после умножения
        value_1n.bits[0] = value_1.bits[0] & (get_bit(value_2, i) == 1 ? 0xFFFFFFFF : 0);
        value_1n.bits[1] = value_1.bits[1] & (get_bit(value_2, i) == 1 ? 0xFFFFFFFF : 0);
        value_1n.bits[2] = value_1.bits[2] & (get_bit(value_2, i) == 1 ? 0xFFFFFFFF : 0);

        //Второе промежуточное число после умножения

        value_2n.bits[0] = value_1.bits[0] & (get_bit(value_2, i + 1) == 1 ? 0xFFFFFFFF : 0);
        value_2n.bits[1] = value_1.bits[1] & (get_bit(value_2, i + 1) == 1 ? 0xFFFFFFFF : 0);
        value_2n.bits[2] = value_1.bits[2] & (get_bit(value_2, i + 1) == 1 ? 0xFFFFFFFF : 0);

        shift_decimal_left(&value_1n, i);
        shift_decimal_left(&value_2n, i + 1);
        s21_add(value_1n, value_2n, &result_temp);
        s21_add(*result, result_temp, result);
    
    }

    if(value1_sign != value2_sign){
        set_sign_neg(result);
    }

    return 0;
}

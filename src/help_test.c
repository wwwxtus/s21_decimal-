#include "decimal.h"



int main(void){

    // -201180194235 | Обратный код сразу сделал
    // s21_decimal decimal = {0xD, 0x0, 0x0, 0x00000000};
    
    // //  231180194235
    // s21_decimal decimal2 = {0x7, 0x0, 0x0, 0x80000000};
    
    // // 30000000000 | 6fc23ac00
    s21_decimal result = {0x0, 0x0, 0x0, 0x00000000};


    //s21_div(decimal, decimal2, &result);

    //info_decimal(result);

    
    // ДЕМОНСТРАЦИЯ СУММЫ

    // if(s21_is_less_or_equal(decimal, decimal2) == 1) {
    //     printf("YES");
    // } else {
    //     printf("NO");
    // }

    // info_decimal(decimal);
    // info_decimal(decimal2);
    // s21_add(decimal, decimal2, &result);
    // info_decimal(result);


    //ДЕМОНСТРАЦИЯ СДВИГА ВЛЕВО


    // s21_decimal decimal_shift = {0x1, 0x1, 0x1, 0x0};
    // info_decimal(decimal_shift);
    // shift_decimal_left(&decimal_shift, 4);
    // info_decimal(decimal_shift);

    // ДЕМОНСТРАЦИЯ СДВИГА ВПРАВО

    // s21_decimal decimal_shift = {0x1, 0x1, 0x1, 0x800F0000};
    // info_decimal(decimal_shift);
    // shift_decimal_right(&decimal_shift, 4);
    // info_decimal(decimal_shift);


    //ДЕМОНСТРАЦИЯ УРАВНИВАНИЯ ЭКСПОНЕНТЫ


    // s21_decimal level_test1 = {0x1, 0x0, 0x0, 0x00B0000};
    // s21_decimal level_test2 = {0x1, 0x0, 0x0, 0x00010000};
    // info_decimal(level_test1);
    // info_decimal(level_test2);
    // level_exponent(&level_test1, &level_test2);
    // info_decimal(level_test2);


    //ДЕМОНСТРАЦИЯ УМНОЖЕНИЯ

    // s21_decimal mul_test1 = {0x00029a18, 0xFFFF, 0x2, 0x0};
    // s21_decimal mul_test2 = {0x17, 0x0, 0x0, 0x0};
    // info_decimal(mul_test1);
    // info_decimal(mul_test2);    
    // s21_mul(mul_test1, mul_test2, &result);
    // info_decimal(result);

    // s21_decimal div_test1 = {0x15, 0x0, 0x0, 0x0};
    // s21_decimal div_test2 = {0x3, 0x0, 0x0, 0x0};
    // info_decimal(div_test1);
    // info_decimal(div_test2);
    // s21_div(div_test1, div_test2, &result);
    // info_decimal(result);


    // s21_decimal exp_test = {0x145, 0x0, 0x0, 0x0};
    // s21_decimal exponent = {0x0, 0x0, 0x0, 0x0};
    // set_exponent(&exponent, 27);
    // info_decimal(exp_test);
    // level_exponent(&exponent, &exp_test);
    // info_decimal(exp_test);

    //Truncate test

    // s21_decimal to_zero = {0x44DAB9, 0x0, 0x0, 0x00050000};
    // info_decimal(to_zero);
    // s21_truncate(to_zero, &result);
    // info_decimal(result);

    //FROM INT TEST

    // int test_int = 10923802;
    // s21_from_int_to_decimal(test_int, &result);
    // info_decimal(result);

    //FROM DECIMAL TO INT TEST

    // int test_int = 0;
    // s21_decimal to_int = {0x44DAB9, 0x0, 0x0, 0x80030000};
    // s21_from_decimal_to_int(to_int, &test_int);
    // printf("%d", test_int);


    //FLOOR TEST

    // s21_decimal value = {0x84210, 0x0, 0x0, 0x80020000};
    // s21_floor(value, &result);
    // info_decimal(result);

    //ROUND TEST

    // s21_decimal value = {0x5, 0x0, 0x0, 0x80020000};
    // s21_round(value, &result);
    // info_decimal(result);

    //BINARY DIV TEST
    // s21_decimal value =  0x0, 0x0, 0x80020000};
            
    // s21_decimal divisor = {0x9923738C, 0x4FFCABBD, 0x0000000A, 0x00040000};
    // s21_decimal value = {0x21D916BD, 0x0AFE266E, 0x0, 0x00110000};
    
    s21_decimal value = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x001C0000};
    s21_decimal divisor = {0xF444, 0xF55F, 0xF11F, 0x00060000};

    s21_decimal EXP_UTIL = {0, 0, 0, 0};

    // printf("LEN: %d\n", get_normalized_len(divisor));
    // pause();

    // set_exponent(&EXP_UTIL, 28);
    // level_exponent(&divisor, &EXP_UTIL);
    // info_decimal(divisor);

    s21_add(value, divisor, &result);
    info_decimal(value);
    info_decimal(divisor);
    info_decimal(result);


    //SHIFT RIGHT TEST

    // s21_decimal value = {0xFF, 0xF000000F, 0x21FF, 0x0};
    // info_decimal(value);
    // shift_decimal_right(&value, 1);
    // info_decimal(value);

    //SHIFT LEFT TEST

    // s21_decimal value = {0xF, 0x0, 0x0, 0x0};
    // info_decimal(value);
    // shift_decimal_left(&value, 90);
    // info_decimal(value);

    //LEN TEST

    // s21_decimal value = {0x63153, 0x0, 0x0, 0x00010000};
    // printf("%d", get_normalized_len(value));

    //MAX LEN TEST?

    // s21_decimal value = {0xBBBBB, 0x0, 0x0, 0x00000000};
    // s21_decimal EXP_UTIL = {0x0, 0x0, 0x0, 0x00000000};
    // s21_decimal value_2 = {0x65231, 0x0, 0x0, 0x00000000};

    // s21_decimal value = {0xBBBBB, 0x0, 0x0, 0x00000000};
    // s21_decimal value_2 = {0x65231, 0x0, 0x0, 0x00000000};
    // s21_decimal result = {0x0, 0x0, 0x0, 0x0};

    // s21_decimal MAX = {0x9999999A, 0x99999999, 0x19999999, 0x001B0000};
    // s21_decimal ONE = {0x1, 0x0, 0x0, 0x00000000};
    // level_exponent(&MAX, &ONE);
    // s21_add(MAX, ONE, &result);
    // info_decimal(result);

    // add_overflow_check(value, value_2, &result);
    // info_decimal(result);

    // int len = get_normalized_len(value);
    // info_decimal(value);
    // set_exponent(&EXP_UTIL, 28 - len + 1);
    // printf("OVERFLOW: %d\n", level_exponent(&value, &EXP_UTIL));

    return 0;
}
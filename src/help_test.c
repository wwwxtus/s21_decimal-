#include "decimal.h"



int main(void){

    // -201180194235 | Обратный код сразу сделал
    s21_decimal decimal = {0x7, 0x0, 0x0, 0x00000000};
    
    //  231180194235
    s21_decimal decimal2 = {0x7, 0x0, 0x0, 0x80000000};
    
    // 30000000000 | 6fc23ac00
    s21_decimal result = {0x0, 0x0, 0x0, 0x00000000};


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

    s21_decimal div_test1 = {0x54E39FE, 0x0, 0x0, 0x0};
    s21_decimal div_test2 = {0x14DE, 0x0, 0x0, 0x0};
    info_decimal(div_test1);
    info_decimal(div_test2);
    s21_div(div_test1, div_test2, &result);
    info_decimal(result);
    
    return 0;
}
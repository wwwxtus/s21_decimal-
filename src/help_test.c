#include "decimal.h"



int main(void){

    // -201180194235 | Обратный код сразу сделал
    s21_decimal decimal = {0x800F0000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFF6};
    
    //  231180194235
    s21_decimal decimal2 = {0x000F0000, 0x0, 0x0, 0x00000015};
    
    // 30000000000 | 6fc23ac00
    s21_decimal result = {0x000F0000, 0x0, 0x0, 0x0};


    // ДЕМОНСТРАЦИЯ СУММЫ


    info_decimal(decimal);
    info_decimal(decimal2);
    s21_add(decimal, decimal2, &result);
    info_decimal(result);


    // ДЕМОНСТРАЦИЯ СДВИГА


    // s21_decimal decimal_shift = {0x000F0000, 0xF002000F, 0xF001600F, 0xF000400F};
    // info_decimal(decimal_shift);
    // shift_decimal_left(&decimal_shift, 4);
    // info_decimal(decimal_shift);


    // ДЕМОНСТРАЦИЯ УРАВНИВАНИЯ ЭКСПОНЕНТЫ


    // s21_decimal level_test1 = {0x000F0000, 0x0, 0x0, 0x1};
    // s21_decimal level_test2 = {0x000D0000, 0x0, 0x0, 0x1};
    // info_decimal(level_test1);
    // info_decimal(level_test2);
    // level_exponent(&level_test1, &level_test2);
    // info_decimal(level_test2);
    
    return 0;
}
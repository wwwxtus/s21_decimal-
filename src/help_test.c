#include "decimal.h"



int main(void){


    s21_decimal decimal = {0x000F0000, 0x0, 0x0, 0x00000020};
    s21_decimal decimal2 = {0x000F0000, 0x0, 0xFFFFFFF1, 0xF0000000};
    s21_decimal result = {0x000F0000, 0x0, 0x0, 0x0};
    s21_decimal negate_result = {0x0, 0x0, 0x0, 0x0};
    info_decimal(decimal);
    s21_negate(decimal, &negate_result);
    info_decimal(negate_result);
    return 0;
}

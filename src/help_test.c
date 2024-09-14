#include "decimal.h"



int main(void){


    s21_decimal decimal = {0x000F0000, 0x0, 0xFFFFFFF1, 0x10000000};
    s21_decimal decimal2 = {0x000F0000, 0x0, 0xFFFFFFF1, 0xF0000000};
    s21_decimal result = {0x000F0000, 0x0, 0x0, 0x0};
    s21_add(decimal, decimal2, &result);
    info_decimal(decimal);
    info_decimal(decimal2);
    info_decimal(result);
    return 0;
}

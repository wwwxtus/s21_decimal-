#include "decimal.h"



int main(void){


    s21_decimal decimal = {0x800F0000, 0xFFFFFFFF, 0xFFFFFFCA, 0x2C962E45};
    s21_decimal decimal2 = {0x000F0000, 0x0, 0x67, 0xD74625BB};
    s21_decimal result = {0x000F0000, 0x0, 0x0, 0x0};
    s21_decimal negate_result = {0x0, 0x0, 0x0, 0x0};
    // info_decimal(decimal);
    // s21_negate(decimal, &negate_result);
    // info_decimal(negate_result);

    info_decimal(decimal);
    info_decimal(decimal2);
    s21_add(decimal, decimal2, &result);
    info_decimal(result);
    
    return 0;
}

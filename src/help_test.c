#include "decimal.h"

int main() {
    // Пример двух Decimal чисел
    // 26409387504754779197847983445
    s21_decimal decimal2 = {{0x00000000, 0x00000000, 0x00000000, 0x0000000A}};
    // 26409387
    s21_decimal decimal1 = {{0x80000000, 0x00000000, 0x00000000, 0x00000005}};
    // 26409387504754779197874392832
    s21_decimal check = {{0x00000000, 0x55555555, 0x55555555, 0x53C25BAA}};
    // alignScale(&decimal1, &decimal2);

    // Результат вычитания
    s21_decimal result;
    info_decimal(decimal1);
    info_decimal(decimal2);
    s21_sub(decimal1, decimal2, &result);
    // Печатаем результат
    printf("Result: ");
    printDecimal(&result);

    printf("check : ");
    printDecimal(&check);

    return 0;
}
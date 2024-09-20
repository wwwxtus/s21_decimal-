#include <stdio.h>

#include "decimal.h"

//Функция вывода decimal
void printDecimal(const s21_decimal *dec) {
    printf("0x%08X%08X%08X%08X\n", dec->bits[0], dec->bits[1], dec->bits[2], dec->bits[3]);
}

//Приравниваем decimal к единице
s21_decimal s21_decimal_get_one(void) {
    s21_decimal result;
    get_zero(&result);
    result.bits[3] = 1;

    return result;
}

//Разность двух decimal
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int err_code = 0;
    //Инициализирую результат нулями
    get_zero(result);

    //Узнаю какие знаки у чисел
    int value_1_sign = get_sign(value_1);
    int value_2_sign = get_sign(value_2);

    /* Два положительных - a - b
       Получить доп. код b => a + (-b)  
       Сложить a и b 
    */
    if (value_1_sign == POSITIVE && value_2_sign == POSITIVE) {
        s21_decimal value_2n;
        get_complement(value_2, &value_2n);
        set_sign_neg(&value_2n);
        
        s21_add(value_1, value_2n, result);

        if(get_sign(*result) == NEGATIVE) {
            get_complement(*result, result);
        }

    }
    /* a - положитеьное, b - отрицательное => a - (-b) => a + b
       Сложить a и b 
    */ 
    else if (value_1_sign == POSITIVE && value_2_sign == NEGATIVE) {
        s21_negate(value_2, &value_2);
        s21_add(value_1, value_2, result);
    } 
    /* a - отрицательное, b - положитеьное => -a - b => -(a + b)
       Сложить a и b
       Поменять знак результата 
    */ 
    else if (value_1_sign == NEGATIVE && value_2_sign == POSITIVE) {
        s21_negate(value_1, &value_1);
        s21_negate(value_2, &value_2);

        s21_add(value_1, value_2, result);
    } 
    /* a - отрицательное, b - отрицательное =>  -a - (-b) => -a + b
       Меньшее из a b число приводим к доп коду, далее a + b 
    */ 
    else if (value_1_sign == NEGATIVE && value_2_sign == NEGATIVE) {
        //Удалить потом
        printf("n n\n");
        
        s21_decimal value_1n;
        s21_decimal value_2n = value_2;
        s21_negate(value_2, &value_2n);
        get_complement(value_1, &value_1n);


        s21_add(value_2n, value_1n, result);

        if(get_sign(*result) == 1){
            get_complement(*result, result);
        }
    }

    return err_code;
}


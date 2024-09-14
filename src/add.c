#include "decimal.h"



int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result){

    for(int i = 3; i > 0; i--){

        unsigned int carry = value_1.bits[i] & value_2.bits[i];
        result->bits[i] = value_1.bits[i] ^ value_2.bits[i];

        while (carry != 0){

            //Перенос в следующий int если необходимо
            if((i != 1 && (carry >> 31 & 1) && (value_1.bits[i] >> 31 & 1)) || (i != 1 && (carry >> 31 & 1) && (value_2.bits[i] >> 31 & 1))){
                value_1.bits[i - 1] = value_1.bits[i - 1] + 1;
            }

            unsigned int siftedcarry = carry << 1;
            carry = result->bits[i] & siftedcarry;
            result->bits[i] ^= siftedcarry;
            
        }
    }

    return 0;

}


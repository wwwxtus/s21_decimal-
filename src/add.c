#include "decimal.h"



int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result){

    //leveling

    result->bits[1] = value_1.bits[1] ^ value_2.bits[1];
    result->bits[2] = value_1.bits[2] ^ value_2.bits[2];
    result->bits[3] = value_1.bits[3] ^ value_2.bits[3];

    

    int prob_sign_carry = 0;

    for(int i = 3; i > 0; i--){
        unsigned int carry = value_1.bits[i] & value_2.bits[i];
        

        while (carry != 0){
            //Перенос в следующий int если необходимо

            unsigned int siftedcarry = carry << 1;
            carry = result->bits[i] & siftedcarry;

            if((i != 1 && (siftedcarry >> 31 & 1) && (value_1.bits[i] >> 31 & 1)) || (i != 1 && (siftedcarry >> 31 & 1) && (value_2.bits[i] >> 31 & 1))){
                if(result->bits[i - 1] == 0xFFFFFFFF && i == 3){
                    result->bits[i - 2] += 1;
                }
                
                result->bits[i - 1] = result->bits[i - 1] + 1;
            }

            result->bits[i] ^= siftedcarry;

            if((i == 1 && (siftedcarry >> 31 & 1) && (value_1.bits[i] >> 31 & 1)) || (i != 1 && (siftedcarry >> 31 & 1) && (value_2.bits[i] >> 31 & 1))){
                prob_sign_carry = 1;
            }
        }
    }

    unsigned int value_1_sign = get_sign(value_1);
    unsigned int value_2_sign = get_sign(value_2);

    if((!value_1_sign && value_2_sign) || (value_1_sign && !value_2_sign)){
        value_1_sign = value_1_sign << 31;
        value_2_sign = value_2_sign << 31;
        prob_sign_carry = prob_sign_carry << 31;
            
        result->bits[0] ^= (value_1_sign ^ value_2_sign ^ prob_sign_carry);
    }

    if(value_1_sign && value_2_sign){
        set_sign_neg(result);
    }

    return 0;
}

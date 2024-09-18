#include "decimal.h"


void info_decimal(s21_decimal decimal) {

    int wrong_usage_flag = 0;
    int wrong_exponent_flag = 0;

    int sign_bit = decimal.bits[0] >> 31 & 1;
    unsigned int exponent = (decimal.bits[0] >> 16) & 255;

    if(exponent > 28){
        wrong_exponent_flag = 1;
    }

    

    printf("BINARY:\n");
    for(int i = 0; i < 4; i++){
        for(int j = 31; j>= 0; j--){
            if(i == 0){
                if(j == 31){
                    printf("\033[0;34m"); //BLUE SIGN
                }
                if((j <= 30 && j >= 24) || (j <= 15 && j >= 0)){
                    printf("\033[0;31m"); //RED UNUSABLE BITS
                    if(decimal.bits[i] >> j & 1){
                        wrong_usage_flag = 1;
                    }
                }
                if(j <= 23 && j >= 16){
                    printf("\033[0;33m"); //YELLOW EXPONENT
                }
                
            }else{
                printf("\033[0;32m"); //GREEN USABLE BITS
            }
        
            printf("%d", decimal.bits[i] >> j & 1);
            printf("\033[0m");
        }

        if(i == 0){
            if(wrong_usage_flag){
                printf("\033[0;31m - ХУЙНЯ. USED UNUSABLE BITS");
                printf("\033[0m");
            }
            if(!wrong_usage_flag){
                printf("\033[0;32m - OK");
                printf("\033[0m");
            }
        }
        printf("\n");
    }



    printf("HEX:\n");
    for(int i = 0; i < 4; i++){
        printf("%08x\n", decimal.bits[i]);
    }

    if(sign_bit == 0){
        printf("\033[0;34mSIGN:\033[0m%d - \033[0;32mПОЗИТИВНЫЙ\n", sign_bit);
    }else{
        printf("\033[0;34mSIGN:\033[0m%d - \033[0;31mНЕГАТИВНЫЙ\n", sign_bit);
    }
    
    printf("\033[0;33mEXPONENT:\033[0m%d", exponent);

    if(wrong_exponent_flag){
        printf(" - \033[0;31mХУЙНЯ EXPONENT\n");
        printf("\033[0m");
    }
    if(!wrong_exponent_flag){
        printf(" - \033[0;32mOK\n");
        printf("\033[0m");
    }


}

int get_sign(s21_decimal value){
    int sign_bit = value.bits[0] >> 31 & 1;
    return sign_bit;
}

void set_sign_pos(s21_decimal *value){
    value->bits[0] = value->bits[0] & 2147483647U;    
}

void set_sign_neg(s21_decimal *value){
    value->bits[0] = ~(value->bits[0]) ^ 2147483647U;
}

void pause(void)
{
    int c;

    do {
        c = getchar();
    } while ((c != '\n') && (c != EOF));
}


int get_complement(s21_decimal value, s21_decimal *result){

    
    s21_decimal one = {{0x0, 0x0, 0x0, 0x1}};
    
    result->bits[0] = value.bits[0];
    result->bits[1] = ~value.bits[1];
    result->bits[2] = ~value.bits[2];
    result->bits[3] = ~value.bits[3];
        
    s21_add(*result, one, result);



}

void shift_decimal_left(s21_decimal *value, int shift){

    unsigned int temp = 0;
    unsigned int temp2 = 0;

    unsigned int shift_temp = 32 - shift; 
    
    temp = (unsigned int)value->bits[3] >> shift_temp;
    value->bits[3] = (value->bits[3] << shift);

    temp2 = (unsigned int)value->bits[2] >> shift_temp;
    value->bits[2] = (value->bits[2] << shift) ^ temp;
    

    value->bits[1] = (value->bits[1] << shift) ^ temp2;

}

int get_exponent(s21_decimal value){
    unsigned int exponent = (value.bits[0] >> 16) & 255;
    return exponent;
}

void set_exponent(s21_decimal *value, int exp){

    value->bits[0] = (value->bits[0] & 0xFFFF0000) | (exp << 16);

}


void level_exponent(s21_decimal *value_1, s21_decimal *value_2){

    
    if(get_exponent(*value_1) < get_exponent(*value_2)){
        int exp_diff = get_exponent(*value_2) - get_exponent(*value_1);

        for(int i = 0; i < exp_diff; i++){

            s21_decimal valueN = *value_1;

            shift_decimal_left(value_1, 3);
            shift_decimal_left(&valueN, 1);
            s21_add(*value_1, valueN, value_1);

        }

        set_exponent(value_1, get_exponent(*value_2));
    }

    if(get_exponent(*value_1) > get_exponent(*value_2)){
        int exp_diff = get_exponent(*value_1) - get_exponent(*value_2);

        for(int i = 0; i < exp_diff; i++){

            s21_decimal valueN = *value_2;

            shift_decimal_left(value_2, 3);
            shift_decimal_left(&valueN, 1);
            s21_add(*value_2, valueN, value_2);
            
        }

        set_exponent(value_2, get_exponent(*value_1));
    }

}



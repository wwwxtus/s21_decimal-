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
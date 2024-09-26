#include "decimal.h"

#define REV(n) ((n << 24) | (((n>>16)<<24)>>16) |  (((n<<16)>>24)<<16) | (n>>24))

/* Выводим информацию о числе decimal, его двоичное представление, 16-ричное, 
его экспоненту в двоичном виде и проверяем её на корректность */
void info_decimal(s21_decimal decimal) {
    int wrong_usage_flag = 0;
    int wrong_exponent_flag = 0;

    int sign_bit = decimal.bits[3] >> 31 & 1;
    unsigned int exponent = (decimal.bits[3] >> 16) & 255;

    if (exponent > 28) {
        wrong_exponent_flag = 1;
    }

    printf("BINARY:\n");
    for (int i = 3; i >= 0; i--) {
        printf("\033[0;32mBITS [%d] ",  i);
        printf("\033[0m");
        for (int j = 31; j >= 0; j--) {
            
            if (i == 3) {
                if (j == 31) {
                    printf("\033[0;34m");  // BLUE SIGN
                }
                if ((j <= 30 && j >= 24) || (j <= 15 && j >= 0)) {
                    printf("\033[0;31m");  // RED UNUSABLE BITS
                    if (decimal.bits[i] >> j & 1) {
                        wrong_usage_flag = 1;
                    }
                }
                if (j <= 23 && j >= 16) {
                    printf("\033[0;33m");  // YELLOW EXPONENT
                }

            } else {
                printf("\033[0;32m");  // GREEN USABLE BITS
            }

            printf("%d", decimal.bits[i] >> j & 1);
            printf("\033[0m");
        }

        if (i == 3) {
            if (wrong_usage_flag) {
                printf("\033[0;31m - ХУЙНЯ. USED UNUSABLE BITS");
                printf("\033[0m");
            }
            if (!wrong_usage_flag) {
                printf("\033[0;32m - OK");
                printf("\033[0m");
            }
        }
        printf("\n");
    }

    printf("HEX:\n");
    for (int i = 3; i >= 0; i--) {
        printf("%08x\n", decimal.bits[i]);
    }

    if (sign_bit == 0) {
        printf("\033[0;34mSIGN:\033[0m%d - \033[0;32mПОЗИТИВНЫЙ\n", sign_bit);
    } else {
        printf("\033[0;34mSIGN:\033[0m%d - \033[0;31mНЕГАТИВНЫЙ\n", sign_bit);
    }

    printf("\033[0;33mEXPONENT:\033[0m%d", exponent);

    if (wrong_exponent_flag) {
        printf(" - \033[0;31mХУЙНЯ EXPONENT\n");
        printf("\033[0m");
    }
    if (!wrong_exponent_flag) {
        printf(" - \033[0;32mOK\n");
        printf("\033[0m");
    }
}

//Находим и определяем знаковый бит числа
int get_sign(s21_decimal value) {
    int sign_bit = value.bits[3] >> 31 & 1;
    return sign_bit;
}

void set_sign_pos(s21_decimal *value) { 
    value->bits[3] = value->bits[3] & 2147483647U; 
}

void set_sign_neg(s21_decimal *value) { 
    value->bits[3] = ~(value->bits[3]) ^ 2147483647U; 
}

void pause(void) {
    int c;

    do {
        c = getchar();
    } while ((c != '\n') && (c != EOF));
}

//Получаем доп. код числа 
int get_complement(s21_decimal value, s21_decimal *result) {
    s21_decimal one = {{0x1, 0x0, 0x0, 0x0}};


    result->bits[0] = ~value.bits[0];
    result->bits[1] = ~value.bits[1];
    result->bits[2] = ~value.bits[2];
    result->bits[3] = value.bits[3];

    add_binary(*result, one, result);

}

void shift_decimal_right(s21_decimal *value, int shift) {
    unsigned int temp = 0;
    unsigned int temp2 = 0;

    unsigned int shift_temp = 32 - shift;

    temp = (unsigned int)value->bits[2] << shift_temp;
    value->bits[2] = ((unsigned int)value->bits[2] >> shift);

    temp2 = (unsigned int)value->bits[1] << shift_temp;
    value->bits[1] = ((unsigned int)value->bits[1] >> shift) ^ temp;

    value->bits[0] = ((unsigned int)value->bits[0] >> shift) ^ temp2;
}

void shift_decimal_left(s21_decimal *value, int shift) {
    unsigned int temp = 0;
    unsigned int temp2 = 0;

    if(shift != 0){

        if(shift > 32){
            shift = 32;
        }

        unsigned int shift_temp = 32 - shift;

        temp = (unsigned int)value->bits[0] >> shift_temp;
        value->bits[0] = ((unsigned int)value->bits[0] << shift);

        temp2 = (unsigned int)value->bits[1] >> shift_temp;
        value->bits[1] = ((unsigned int)value->bits[1] << shift) ^ temp;

        value->bits[2] = ((unsigned int)value->bits[2] << shift) ^ temp2;
    }
    
}

int get_exponent(s21_decimal value) {
    unsigned int exponent = ((unsigned int)value.bits[3] >> 16) & 255;
    return exponent;
}

void set_exponent(s21_decimal *value, int exp) {
    int sign = get_sign(*value);
    value->bits[3] = (value->bits[3] & 0x00000000) ^ (exp << 16);

    if (sign == 1) {
        set_sign_neg(value);
    } else {
        set_sign_pos(value);
    }
}

void level_exponent(s21_decimal *value_1, s21_decimal *value_2) {

    s21_decimal resultN = {{0, 0, 0, 0}};
    
    if (get_exponent(*value_1) < get_exponent(*value_2)) {
        int exp_diff = get_exponent(*value_2) - get_exponent(*value_1);
        set_exponent(value_1, get_exponent(*value_2));
        set_exponent(&resultN, get_exponent(*value_2));

        for (int i = 0; i < exp_diff; i++) {
            s21_decimal valueN;
            valueN.bits[0] = value_1->bits[0];
            valueN.bits[1] = value_1->bits[1];
            valueN.bits[2] = value_1->bits[2];
            valueN.bits[3] = value_1->bits[3];

            shift_decimal_left(value_1, 3);
            shift_decimal_left(&valueN, 1);

            s21_add(*value_1, valueN, &resultN);

            value_1->bits[0] = resultN.bits[0];
            value_1->bits[1] = resultN.bits[1];
            value_1->bits[2] = resultN.bits[2];

        }
    }

    if (get_exponent(*value_1) > get_exponent(*value_2)) {

        int exp_diff = get_exponent(*value_1) - get_exponent(*value_2);
        set_exponent(value_2, get_exponent(*value_1));
        set_exponent(&resultN, get_exponent(*value_1));

        for (int i = 0; i < exp_diff; i++) {
            s21_decimal valueN;

            valueN.bits[0] = value_2->bits[0];
            valueN.bits[1] = value_2->bits[1];
            valueN.bits[2] = value_2->bits[2];
            valueN.bits[3] = value_2->bits[3];

            shift_decimal_left(value_2, 3);
            shift_decimal_left(&valueN, 1);

            s21_add(*value_2, valueN, &resultN);

            value_2->bits[0] = resultN.bits[0];
            value_2->bits[1] = resultN.bits[1];
            value_2->bits[2] = resultN.bits[2];

        }
    }
}

//Обнуляем все биты числа decimal
void get_zero(s21_decimal *value) {
    value->bits[0] = 0;
    value->bits[1] = 0;
    value->bits[2] = 0;
    value->bits[3] = 0;
}

int get_bit(s21_decimal decimal, int bit_position) {
    int index = bit_position / 32; // Определяем индекс в массиве bits
    int offset = bit_position % 32; // Определяем смещение внутри 32-битного числа
    return (decimal.bits[index] >> offset) & 1; // Сдвиг и маскирование для получения конкретного бита
}


int s21_is_less_helper(s21_decimal value_1, s21_decimal value_2) {
    int result = 0;
    int value_sign_1 = get_sign(value_1);
    int value_sign_2 = get_sign(value_2);
    
    if (value_sign_1 == NEGATIVE && value_sign_2 == POSITIVE) {
        result = 2;
    } else if (value_sign_1 == POSITIVE && value_sign_2 == NEGATIVE) {
        result = 1;
    } else if (value_sign_1 == POSITIVE && value_sign_2 == POSITIVE){
        result = bitwise_comparison(value_1, value_2);
    } else if (value_sign_1 == NEGATIVE && value_sign_2 == NEGATIVE) {
        result = bitwise_comparison(value_1, value_2);
        if (result == 1) {
            result = 2;
        } else if (result == 2) {
            result = 1;
        }
    } else if (value_1.bits[0] == 0 && value_1.bits[1] == 0 && value_1.bits[2] == 0 && 
    value_2.bits[0] == 0 && value_2.bits[1] == 0 && value_2.bits[2] == 0) {
        result = 0;
    }

    return result;
}

int bitwise_comparison(s21_decimal value_1, s21_decimal value_2) {
    int flag = 0;
    int bit1 = 0;
    int bit2 = 0;
    for (int i = 95; !flag && i >= 0; --i) {
        bit1 = get_bit(value_1, i);
        bit2 = get_bit(value_2, i);
        if (bit1 > bit2) {
            flag = 1;
        } else if (bit1 < bit2) {
            flag = 2;
        }
    }

    return flag;
}

int whole_division(s21_decimal value_1, s21_decimal value_2, s21_decimal *result){

    s21_decimal ONE = {0x1, 0x0, 0x0, 0x0};
    s21_decimal ZERO = {0x0, 0x0, 0x0, 0x0};

    s21_decimal dividend = value_1;
    s21_decimal divisor = value_2;

    int dividend_sign = get_sign(dividend);
    int divisor_sign = get_sign(divisor);
    set_sign_pos(&dividend);
    set_sign_pos(&divisor);

    set_exponent(&ONE, get_exponent(dividend));
    set_exponent(result, get_exponent(dividend));
    set_exponent(&ZERO, get_exponent(dividend));

    while(s21_is_greater_or_equal(dividend, divisor)){
        s21_sub(dividend, divisor, &dividend);
        s21_add(*result, ONE, result);
    }

    if(dividend_sign != divisor_sign){
        set_sign_neg(result);
    }else if(dividend_sign && divisor_sign){
        set_sign_pos(result);
    }


}

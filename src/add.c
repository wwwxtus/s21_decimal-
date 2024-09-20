#include "decimal.h"



int add_binary(s21_decimal value_1, s21_decimal value_2, s21_decimal *result){

    //Добавил строку ниже чтобы XOR на знаки сделать. Мы получаем маску для XOR на знак.
    
    result->bits[3] = ((unsigned int)(get_sign(value_1) ^ get_sign(value_2)) << 31);

    set_exponent(result, get_exponent(value_1));

    //Первый этап алгоритма суммы - XOR двух чисел.

    result->bits[0] = value_1.bits[0] ^ value_2.bits[0];
    result->bits[1] = value_1.bits[1] ^ value_2.bits[1];
    result->bits[2] = value_1.bits[2] ^ value_2.bits[2];

    int prob_sign_carry = 0;

    for (int i = 0; i < 3; i++) {
        unsigned int carry = value_1.bits[i] & value_2.bits[i];
        

        while (carry != 0){

            unsigned int siftedcarry = carry << 1;

            //Здесь идёт проверка на перенос.
            if((i != 2 && ((carry >> 31 & 1)) && (value_1.bits[i] >> 31 & 1)) 
            || (i != 2 && (carry >> 31 & 1) && (value_2.bits[i] >> 31 & 1))
            || (i != 2 && (carry >> 31 & 1) && (result->bits[i] >> 31 & 1))){
                //Если мы находимся на bits[3], а bits[2] = FFFFFFFF -> (I)
                if(result->bits[i + 1] == 0xFFFFFFFF && i == 0){

                    //добавил этот if. Если в bits[1] все биты забиты единицами, то значит будет перенос на знак.
                    //Почему нужна проверка? смотри (I)
                    if(result->bits[i + 2] == 0xFFFFFFFF){
                        prob_sign_carry = 1;
                    }
                    
                    //(I) то мы добавляем единицу в bits[1]
                    result->bits[i + 2] += 1;
                }
                
                if(i + 1 == 2){
                    if(result->bits[2] == 0xFFFFFFFF){
                        prob_sign_carry = 1;
                    }
                }

                //Если у нас прошла проверка на перенос, то в следующий bits добавить единицу.
                result->bits[i + 1] = result->bits[i + 1] + 1;
            }

            //Доп проверка на перенос знака. Надо это или нет - я хз. Но работает всё - не трогать. Тут если крайний левый бит 1 
            //и бит переноса 1, то соответственно перенос на знак.
            if((i == 2 && (carry >> 31 & 1) && (value_1.bits[i] >> 31 & 1)) 
            || (i == 2 && (carry >> 31 & 1) && (value_2.bits[i] >> 31 & 1))
            || (i == 2 && (carry >> 31 & 1) && (result->bits[i] >> 31 & 1))){
                prob_sign_carry = 1;
            }
            
            carry = result->bits[i] & siftedcarry;

            result->bits[i] ^= siftedcarry;

            
        }
    }

    unsigned int value_1_sign = get_sign(value_1);
    unsigned int value_2_sign = get_sign(value_2);


    //Всё снизу - блок определения знака.
    if((!value_1_sign && value_2_sign) || (value_1_sign && !value_2_sign) || (value_1_sign && value_2_sign)){
        //Переменная переноса либо 1 либо 0. Переносим это влево на 31 знак. То есть крайним левым делаем. Получается маска для XOR.
        prob_sign_carry = prob_sign_carry << 31;
        //Делаем XOR.
        result->bits[3] ^= prob_sign_carry;
    }

    //Пока функция возвращает только 0. Надо добавить проверки на ошибки.
    return 0;
}

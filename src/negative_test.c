#include <stdio.h>

int main() {
    int x = -8;
    for(int j = 31; j >= 0; j--){
        printf("%d", x >> j & 1);
    }
    printf("\n");
    return 0;
}
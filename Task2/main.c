#include <stdio.h>
#include <math.h>

// decToBin - decimal to binary conversion
// param: dec [unsigned long] - input decimal value
// return: bin [unsigned long] - output binary value
unsigned long decToBin(unsigned long dec) {

    unsigned long rest;
    unsigned long bin = 0;
    unsigned long position = 1;
    unsigned long temp = dec;

    while (temp > 0) {
        rest = temp%2;
        bin = position*rest + bin;
        temp /= 2;
        position *= 10;
    }
    return bin;
}

// binToDec - binary to decimal conversion
// param: bin [unsigned long] - input binary value
// return: decVal [unsigned long] - output decimal value
unsigned long binToDec(unsigned long bin) {

    unsigned long endVal;
    unsigned char counter = 0;
    unsigned long decVal = 0;
    unsigned long actVal = 0;
    unsigned long valTemp = bin;

    while (valTemp > 0) {
        endVal = valTemp % 10;
        valTemp /= 10;
        actVal += endVal * (unsigned long)pow(2, counter);
        decVal += actVal;
        counter++;
        actVal = 0;
    }
    return decVal;
}

// select - select mode
// param: sign [int] - mode
// param: val [unsigned long] - input value (dec or bin)
// return: newVal [unsigned long] - output value (dec or bin)
unsigned long select(int sign, unsigned long val) {

    unsigned long newVal = 0;

    if ((val > 1023 && sign == 1) ||
        (val > 1111111111 && sign == 2 )){
        sign = 3;
    }
    switch (sign) {
        case 1:
            newVal = decToBin(val);
            break;
        case 2:
            newVal = binToDec(val);
            break;
        default:
            printf("There is no such mode or number too large\n");
            break;
    }
    return newVal;
}

// Convert number to binary or decimal
// depending on the selected mode
// Range: 0 - 1023 (1111111111) /10 bits
int main(void) {

    unsigned long val;
    int sign;
    unsigned long newVal;

    printf("Modes:\n");
    printf("1) Conversion - decimal to binary - Choose 1.\n");
    printf("2) Conversion - binary to decimal - Choose 2.\n");
    printf("3) End - Choose letter.\n");

    printf("Select mode or quit \n");
    while (scanf("%d", &sign) == 1) {
        printf("Enter value \n");
        scanf("%d", &val);
        newVal = select(sign, val);
        printf("Converted value is %d \n", newVal);
        printf("Select mode or quit \n");
    }
    printf("End of conversion\n");
    return 0;
}
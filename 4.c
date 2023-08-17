#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

void print_binary_representation(double number) {
    union {
        double floating;
        uint64_t bits;
    } converter;
    converter.floating = number;

    printf("Number: %.6e\n", number);
    printf("Binary representation:\n");

    int spaceCount = 0;
    for (int i = 63; i >= 0; i--) {
        uint64_t bit = (converter.bits >> i) & 1;
        while (spaceCount < 3) {
            printf(" ");
            spaceCount++;
        }
        printf("%lu", bit);
        if (i == 63 || i == 52) {
            printf(" ");
        }
        spaceCount++;
    }

    printf("\n");
    printf("sign    exponent                                             mantissa\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "usage: %s <double>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    double num = strtod(argv[1], &endptr);

    if (*endptr != '\0') {
        fprintf(stderr, "ERROR: %s is not a valid double!\n", argv[1]);
        fprintf(stderr,"Extracted double component: %.6f\n", num);
         fprintf(stderr,"Remaining: %s\n",endptr);
                
        return EXIT_FAILURE;
    }

    print_binary_representation(num);

    return EXIT_SUCCESS;
}
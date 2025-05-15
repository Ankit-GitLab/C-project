#include <stdio.h>    // For printf and scanf
#include <stdlib.h>   // For rand and srand
#include <time.h>     // For time to seed the random number generator

int main() {
    int min, max, randomValue;

    // Seed the random number generator with current time
    srand(time(0));

    // Ask user for input
    printf("Welcome to the world of OTP Generate...\n");

    // Input the minimum value
    printf("Enter First Number: ");
    scanf("%d", &min);

    // Input the maximum value
    printf("Enter Second Number: ");
    scanf("%d", &max);

    // Generate a random number between min and max (inclusive)
    randomValue = (rand() % (max - min + 1)) + min;

    // Output the result
    printf("Random OTP between %d to %d: %d\n\n", min, max, randomValue);

    printf("\n Thanks for Playing.");


    return 0;
}

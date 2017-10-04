#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>

#define E   2.71828
#define PI  3.14159

void task_1(int x, int y, int z);
void task_2(int x, int y, int z);
void task_3(int x, int y, int z);
void task_4(int x, int y, int z);


int main(int argc, char *argv[]) {
    if (argc != 5) {
        printf("4 arguments expected.\n");
        return 1;
    }
    printf("Requested task %s.\n", argv[1]);

    int x = atoi(argv[2]);
    int y = atoi(argv[3]);
    int z = atoi(argv[4]);

    printf("Arguments: %d, %d, %d.\n", x, y, z);

    switch (atoi (argv[1])) {
        case 1:
            task_1(x, y, z);
            break;
        case 2:
            task_2(x, y, z);
            break;
        case 3:
            task_3(x, y, z);
            break;
        case 4:
            task_4(x, y, z);
            break;
        default:
            printf("Error: requested task invalid.\n");
            return(1);
    }

    return 0;
}


void task_1(int x, int y, int z) {
    float a = ((pow(x, 2) + pow(y, 3) - x*y*z) / (sqrt(abs(x - y)) + sqrt(abs(z + x)) + 1));
    float b = (x / y * atan(z + pow(E, x*y*z)));
    printf("Answer: %f %f\n", a, b);
}

void task_2(int x, int y, int z) {
    float a = (cos(pow(x, 2) + PI/3) + 3*pow(y, 2) - sin(z)) / (sqrt(fabs(sin(x)) + abs(y) + 3));
    float b = 4 - pow(E, x+y+z) / (pow(x, 2) + 1);
    printf("Answer: %f %f\n", a, b);
}

void task_3(int x, int y, int z) {
    float a = (sin(x + z) - cos(PI/4 + y)) / (6 + sqrt(fabs(atan(x)) + fabs(cos(y*z))));
    float b = pow(cos(atan(z*a*y) / (pow(x, 3) + 1)), 4);
    printf("Answer: %f %f\n", a, b);
}

void task_4(int x, int y, int z) {
    float a = log((sin(x*y + z) + 1) / (2 + sqrt(fabs(atan(x)) + fabs(cos(y*z)))));
    float b = 3 * pow(a, 3) + 4 * pow(x, 2) - a + 5;
    printf("Answer: %f %f\n", a, b);
}


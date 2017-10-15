#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>

#define E   2.71828
#define PI  3.14159

void task_1(float x, float y, float z);
void task_2(float x, float y, float z);
void task_3(float x, float y, float z);
void task_4(float x, float y, float z);


int main(int argc, char *argv[]) {
    if (argc != 5) {
        printf("4 arguments expected.\n");
        return 1;
    }
    printf("Requested task %s.\n", argv[1]);

    float x = atof(argv[2]);
    float y = atof(argv[3]);
    float z = atof(argv[4]);

    printf("Arguments: %12.3f, %12.3f, %12.3f.\n", x, y, z);

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


void task_1(float x, float y, float z) {
    float a = ((pow(x, 2) + pow(y, 3) - x*y*z) / (sqrt(fabs(x - y)) + sqrt(fabs(z + x)) + 1));
    float b = (x / y * atan(z + pow(E, x*y*z)));
    printf("Answer: %12.3f, %12.3f.\n", a, b);
}

void task_2(float x, float y, float z) {
    float a = ((cos(pow(x, 2) + PI/3)*PI/180) + 3*pow(y, 2) - sin(z*PI/180)) / (sqrt(fabs(sin(x*PI/180)) + fabs(y) + 3));
    float b = 4 - pow(E, x+y+z) / (pow(x, 2) + 1);
    printf("Answer: %12.3f, %12.3f.\n", a, b);
}

void task_3(float x, float y, float z) {
    float a = (sin((x + z)*PI/180) - cos((PI/4 + y)*PI/180)) / (6 + sqrt(fabs(atan(x)) + fabs(cos(y*z*PI/180))));
    float b = pow(cos((atan(z*a*y) / (pow(x, 3) + 1))*PI/180), 4);
    printf("Answer: %12.3f, %12.3f.\n", a, b);
}

void task_4(float x, float y, float z) {
    float a = log((sin((x*y + z)*PI/180) + 1) / (2 + sqrt(fabs(atan(x)) + fabs(cos(y*z*PI/180)))));
    float b = 3 * pow(a, 3) + 4 * pow(x, 2) - a + 5;
    printf("Answer: %12.3f, %12.3f.\n", a, b);
}


#include "cblas.h"
#include "network.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define LAYERS 5

float randFloat() {
    return (float)(rand())/(float)RAND_MAX;
}

float sigmoid(float x) {
    return 1/(1 + exp(-x));
}

int main() {
    srand(time(0));

    printf("%f", sigmoid(3));

    network n1;

    initilize_network(&n1, 5);
    create_add_layer(&n1, 2, &randFloat, &sigmoid);
    create_add_layer(&n1, 4, &randFloat, &sigmoid);
    create_add_layer(&n1, 4, &randFloat, &sigmoid);
    create_add_layer(&n1, 4, &randFloat, &sigmoid);
    create_add_layer(&n1, 4, &randFloat, &sigmoid);
    create_add_layer(&n1, 2, &randFloat, &sigmoid);

    n1.neurons[0][0] = 523;
    n1.neurons[0][1] = 146;

    printf(" ------------- BEFORE CALC ------------- \n");

    print_network(&n1);

    time_t now;
    now = time(0);
    for (int i = 0; i < 10000000; i++)
    {
        compute_network(&n1);
    }


    printf(" ------------- AFTER CALC ------------- \n");
    printf("\nTime taken: %d seconds\n", time(0) - now);
    print_network(&n1);

    delete_network(&n1);

    return 0;
}
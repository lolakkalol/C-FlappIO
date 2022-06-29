#include "cblas.h"
#include "network.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LAYERS 5

float randFloat() {
    return (float)(rand())/(float)RAND_MAX;
}

int main() {
    srand(time(0));

    network n1;

    initilize_network(&n1, 5);
    create_add_layer(&n1, 2, &randFloat);
    create_add_layer(&n1, 4, &randFloat);
    create_add_layer(&n1, 4, &randFloat);
    create_add_layer(&n1, 4, &randFloat);
    create_add_layer(&n1, 4, &randFloat);
    create_add_layer(&n1, 2, &randFloat);

    n1.neurons[0][0] = 523;
    n1.neurons[0][1] = 146;

    printf(" ------------- BEFORE CALC ------------- \n");

    print_network(&n1);
    compute_network(&n1);

    printf(" ------------- AFTER CALC ------------- \n");
    print_network(&n1);

    delete_network(&n1);

    return 0;
}
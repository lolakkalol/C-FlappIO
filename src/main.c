#include "cblas.h"
#include "network.h"
#include <stdio.h>
#include <stdlib.h>

#define LAYERS 5

int main() {

    u_int8_t map[] = {3, 4, 4, 4, 2};

    neuron input[] = {1, 1, 1};  
    weight w1[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    neuron h1[] = {0, 0, 0, 0};
    weight w2[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    neuron h2[] = {0, 0, 0, 0};
    weight w3[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    neuron h3[] = {0, 0, 0, 0};
    weight w4[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    neuron output[] = {0,0};

    network n1;
    initilize_network(&n1, 5);
    n1.map = map;

    n1.neurons[0] = input;
    n1.neurons[1] = h1;
    n1.neurons[2] = h2;
    n1.neurons[3] = h3;
    n1.neurons[4] = output;

    n1.weights[0] = w1;
    n1.weights[1] = w2;
    n1.weights[2] = w3;
    n1.weights[3] = w4;

    compute_layer(4, 3, w1, input, h1);
    compute_layer(4, 4, w2, h1, h2);
    compute_layer(4, 4, w2, h2, h3);
    compute_layer(2, 4, w2, h3, output);

    for (int i = 0; i < 2; i++) {
        printf(" %f", output[i]);
    }

    return 0;
}
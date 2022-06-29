#ifndef NETWORK_H
#define NETWORK_H
#include "cblas.h"
#include <stdlib.h>
#include <math.h>

typedef enum {
    FUNC_ERROR,
    FUNC_OK
} ERROR_ID;

typedef float neuron;
typedef float weight;

typedef struct
{
    u_int8_t init_size;
    u_int8_t populated_layers;
    u_int8_t* map;              // Is a map of layer sizes in the network
    float (**activation)(float);
    neuron** neurons;
    weight** weights;
} network;

void compute_layer(blasint m, blasint n, float* weights,
 float* input_layer, float* output_layer, float (*fun_activation)(float));
void compute_network(network* n);
void initilize_network(network* net, u_int8_t layers);
void add_layer(network* net, neuron* neuron_layer);
ERROR_ID create_add_layer(network* net,
 int size, float (*fun_rand)(), float (*fun_activation)(float));
void delete_network(network* net);
void print_network(network* net);

// Activation functions

float sigmoid(float x);
float binary_step(float x);
float ReLU(float x);
#endif
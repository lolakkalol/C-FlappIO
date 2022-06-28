#ifndef NETWORK_H
#define NETWORK_H
#include "cblas.h"
#include <stdlib.h>

typedef enum {
    FUNC_ERROR,
    FUNC_OK
} ERROR_ID;

typedef float neuron;
typedef float weight;

typedef struct
{
    u_int8_t populated_layers;
    u_int8_t* map;
    neuron** neurons;
    weight** weights;
} network;

void compute_layer(blasint m, blasint n, float* weights, float* input_layer, float* output_layer);
void compute_network(network n);
void initilize_network(network* net, u_int8_t layers);
void add_layer(network* net, neuron* neuron_layer);

#endif
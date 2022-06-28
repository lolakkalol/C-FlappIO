#include "network.h"
#include "cblas.h"

void initilize_network(network* net, u_int8_t layers) {
    net->populated_layers = 0;
    net->map = calloc( layers, sizeof(u_int8_t*) );
    net->neurons = malloc( sizeof(neuron*) * layers);
    net->weights = malloc( sizeof(weight*) * (layers-1));
}

void delete_network(network* net) {
    free(net->map);
    free(net->neurons);
    free(net->weights);
}

void add_layer(network* net, neuron* neuron_layer) {
    net->neurons[ net->populated_layers ];
}

void compute_network(network n) {
    for (int i = 0; i < 5; i++) {
        compute_layer(n.map[i+1], n.map[i], n.weights[i], n.neurons[i], n.neurons[i+1]);
    }
}

// M rows of matrix, output size
// N Columns of matrix, input size
void compute_layer(blasint m, blasint n, float* weights, float* input_layer, float* output_layer) {
    cblas_sgemv(CblasRowMajor, CblasNoTrans, m, n, 1, weights, n, input_layer, 1, 0, output_layer, 1);
}
#include "network.h"
#include "cblas.h"

/**
 * @brief Initilizes the network by allocating memmory needed for the 
 * specified layers. This is not to be run on a already initilized 
 * network since it will result in memory leaking.
 * 
 * @param net The not initilized network of type network
 * @param layers The number of neuron layers to allocate
 */
void initilize_network(network* net, u_int8_t layers) {
    net->init_size = layers;
    net->populated_layers = 0;
    net->map = malloc( layers * sizeof(u_int8_t*) );
    net->neurons = malloc( sizeof(neuron*) * layers);
    net->weights = malloc( sizeof(weight*) * (layers-1));
    net->activation = malloc( sizeof( float (*) ) * layers );
}

/**
 * @brief deallocates all memmory allocated by the functions 
 * initilize_network and create_add_layer.
 * 
 * @param net Network to delete
 */
void delete_network(network* net) {
    //free(net->map); // Does not work?
    //printf("\n%p", net->map);
    free(net->neurons);
    free(net->weights);
    //TODO: Remove the layers created by create_add_layer
}

/**
 * @brief Adds the specified layer to the specified network. This 
 * function is to not be used, use create_add_layer instead to add 
 * layers.
 * 
 * @param net The network to add a layer to
 * @param neuron_layer The neuron layer to add
 */
void add_layer(network* net, neuron* neuron_layer) {
    net->neurons[ net->populated_layers ];
}

// TODO: Split function into smaller functions

/**
 * @brief Create a add layer and random weights to the specified 
 * network. Adds bias to the layer aswell. Returns FUNC_OK on successfull
 *  execution and FUNC_ERROR otherwise.
 * 
 * @param net The network to add a layer to
 * @param fun_rand Pointer to a random number function for weights 
 * starting value
 * @param fun_activation Activation function for the layer
 * 
 * @return ERROR_ID Returns FUNC_OK if allocation worked and FUNC_ERROR if 
 * something went wrong
 */
ERROR_ID create_add_layer(network* net,
 int size, float (*fun_rand)(), float (*fun_activation)(float)) {

    // if layers full; TODO: Add dynamic allocation of layers
    if (net->populated_layers >= net->init_size)
        return FUNC_ERROR;

    int layer = net->populated_layers;

    // Allocates memory for an neuron array. + 1 is for a bias
    net->neurons[ layer ] = malloc( (sizeof(neuron) * size ) + 1 );

    // If failed allocated memory
    if ( net->neurons[ layer ] == NULL ) {
        printf("Failed to allocate memory for neuron layers");
        return FUNC_ERROR;
    }

    // Sets bias node to 1
    net->neurons[ layer ][size + 1] = 1;

    // Maps the network structure by layer size
    net->map[ layer ] = size;

    // Sets activation function for layer
    net->activation[ layer ] = fun_activation;

    // Tells how many layers are populated
    net->populated_layers++;

    // If there is a previous layer add weights
    if ( layer > 0 ) {
        // Amount of weights
        int weights = size * net->map[ layer-1 ];

        // Allocates memory for all weights between 
        net->weights[layer-1] 
         = malloc( sizeof(weight) * weights );

        // If failed allocated memory
        if ( net->weights[ layer-1 ] == NULL ) {
            printf("Failed to allocate memory for weights");
            return FUNC_ERROR;
            // TODO: Clean up the layer if allocation of weights failed
        }

        for (int i = 0; i < weights; i++) {
            net->weights[ layer-1 ][i] = (*fun_rand)();
        }
    }

    return FUNC_OK;
}

/**
 * @brief Propagates the input values through the network
 * 
 * @param net The network to propagate values through
 */
void compute_network(network* net) {
    for (int i = 0; i < net->populated_layers; i++) {
        compute_layer(net->map[i+1],
         net->map[i],
         net->weights[i],
         net->neurons[i],
         net->neurons[i+1],
         net->activation[i]);
    }
}

// TODO: Add transfer function

// M rows of matrix, output size
// N Columns of matrix, input size

/**
 * @brief Propagates the values of the input_layer through the weights
 *  to the next layer (output_layer). Does not use activation functions
 * 
 * @param m Amount of output neurons (Not including bias)
 * @param n Amount of input neurons
 * @param weights An array of weights thats between the two layers
 * @param input_layer The input neuron layer (Need to have values to 
 * propogate)
 * @param output_layer The neuron layer where the output values are 
 * to be stored
 */
void compute_layer(blasint m, blasint n, float* weights,
 float* input_layer, float* output_layer, float (*fun_activation)(float)) {

    cblas_sgemv(CblasRowMajor, CblasNoTrans, m, n, 1, weights, n,
     input_layer, 1, 0, output_layer, 1);

    for(int i = 0; i < m; i++) {
        output_layer[i] = (*fun_activation)( output_layer[i] );
    }
}


void print_weights(weight* w, int size) {
    for (int j = 0; j < size; j++) {
        printf("%.2f ", w[j]);
    }
}

void print_neurons(neuron* n, int size) {
    for (int j = 0; j < size; j++) {
        printf("%.2f ", n[j]);
    }
}

/**
 * @brief Prints the network to terminal
 * 
 * @param net The network to be printed
 */
void print_network(network* net) {
    for (int i = 0; i < net->populated_layers; i++) {
        if ( i > 0)
            print_weights(net->weights[i-1], net->map[i] * net->map[i-1]);

        printf("\n");
        
        print_neurons(net->neurons[i], net->map[i]);
            

        printf("\n---------------------------\n");
        
    }
    
}
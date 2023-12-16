#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_DICTIONARY_SIZE 50000
#define TRAIN_INSTANCE_NUM 160
#define TEST_INSTANCE_NUM  40
// Define model parameters
double w[MAX_DICTIONARY_SIZE]; // Initialize with random values

// Define hyperparameters
double learning_rate = 0.0001;
int epochs = 100;
double epsilon = 1e-15;

double calculate_cost(double y, double y_hat) {
    return 0.5 * pow((y_hat - y), 2.0);
}

// Implement forward propagation
double forward_propagation(double x[MAX_DICTIONARY_SIZE]) {
    double sum = 0;
    for (int i = 0; i < MAX_DICTIONARY_SIZE; i++) {
        sum += w[i] * x[i];
    }
    return tanh(sum);
}

void gradient_descent(double x[MAX_DICTIONARY_SIZE], double y) {
    double y_hat = forward_propagation(x);
    double error = y_hat - y;

    // Update parameters
    for (int i = 0; i < MAX_DICTIONARY_SIZE; i++) {
        double derivative = 1.0 - pow(tanh(y_hat), 2.0); // Derivative of tanh
        w[i] -= learning_rate * error * derivative * x[i];
    }
}

// Main training loop
// Main training loop
void train(double **training_data, double labels[],int num_instances) {
    clock_t begining = clock();
    
    FILE *eploss = fopen("sgdepochloss.txt","w+");
    FILE *timeloss = fopen("sgdtimeloss.txt","w+");
    for (int epoch = 0; epoch < epochs; epoch++) {

	double *avg = malloc(MAX_DICTIONARY_SIZE * sizeof(double));
	for(int i = 0;i < MAX_DICTIONARY_SIZE;i++){
	    double sum = 0;
	    for(int j = 0;j < num_instances;j++){
		    sum += training_data[j][i];
	    }
	    avg[i] = (double)(sum / ((double)num_instances + epsilon));
	}

	double avgy = 0;
	for(int i = 0;i < num_instances;i++){
	    avgy += labels[i];
	}
	avgy = (double)(avgy / ((double)num_instances + epsilon));
	
	fprintf(eploss, "%d %lf", epoch,calculate_cost(avgy,forward_propagation(avg)));
	fprintf(eploss,"\n");

	srand(time(NULL));
	
	int x_index = rand() % num_instances;
	int y_index = rand() % num_instances;
	gradient_descent(training_data[x_index], labels[y_index]);
    }
    fclose(eploss);
}

// Main function
int main() {
    // Load training data, labels, and test data
    FILE *train_file = fopen("hotv_train.txt", "r");
    FILE *test_file = fopen("hotv_test.txt", "r");

    for(int i = 0;i < MAX_DICTIONARY_SIZE;i++){
	w[i] = -0.001;
    }	

    // Read training data
    double **training_data = malloc(TRAIN_INSTANCE_NUM * sizeof(double *));
    for (int i = 0; i < TRAIN_INSTANCE_NUM; i++) {
        training_data[i] = malloc(MAX_DICTIONARY_SIZE * sizeof(double));
        for (int j = 0; j < MAX_DICTIONARY_SIZE; j++) {
            fscanf(train_file, "%lf", &training_data[i][j]);
        }
    }

    // first 80 instances are positive, last 80 instances are negative
    double labels[TRAIN_INSTANCE_NUM];
    for (int i = 0; i < TRAIN_INSTANCE_NUM; i++) {
        if (i < TRAIN_INSTANCE_NUM / 2) {
            labels[i] = 1;
        } else {
            labels[i] = -1;
        }
    }
    // Train the model
    train(training_data, labels, TRAIN_INSTANCE_NUM);
    // Test the model on the test set
    double **test_data = malloc(TEST_INSTANCE_NUM * sizeof(double *));
    for (int i = 0; i < TEST_INSTANCE_NUM; i++) {
        test_data[i] = malloc(MAX_DICTIONARY_SIZE * sizeof(double));
        for (int j = 0; j < MAX_DICTIONARY_SIZE; j++) {
            fscanf(test_file, "%lf", &test_data[i][j]);
        }
    }
    // first 20 instances are positive, last 20 instances are negative
    double test_labels[TEST_INSTANCE_NUM];
    for (int i = 0; i < TEST_INSTANCE_NUM; i++) {
        if (i < TEST_INSTANCE_NUM / 2) {
            test_labels[i] = 1;
        } else {
            test_labels[i] = -1;
        }
    }
    // Calculate accuracy
    int correct = 0;
    for (int i = 0; i < TEST_INSTANCE_NUM; i++) {
        double *x = test_data[i];
        double y = test_labels[i];
        double y_hat = forward_propagation(x);
        if (y_hat >= 0 && y == 1) {
            correct++;
        } else if (y_hat < 0 && y == -1) {
            correct++;
        }
    }
    printf("Accuracy: %lf\n", (double) correct / TEST_INSTANCE_NUM);

    fclose(train_file);
    fclose(test_file);

    free(training_data);
    free(test_data);

    return 0;
}

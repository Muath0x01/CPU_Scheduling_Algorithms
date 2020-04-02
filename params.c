/* Note: You should not modify this file. */

#include <stdio.h>
#include <stdlib.h>
#include "params.h"

int num_tasks; 
int max_burst_time;
int iat;
int quantum_time;
int rand_seed;

void get_params()
{
	int ret;

	printf("Number of tasks: ");
	ret = scanf("%d", &num_tasks);
	if (ret == EOF || ret == 0) {
		fprintf(stderr, "Input error.\n");
		exit(-1);
	}

	printf("Max burst time: ");
	ret = scanf("%d", &max_burst_time);
	if (ret == EOF || ret == 0) {
		fprintf(stderr, "Input error.\n");
		exit(-1);
	}

	printf("Inter-arrival time: ");
	ret = scanf("%d", &iat);
	if (ret == EOF || ret == 0) {
		fprintf(stderr, "Input error.\n");
		exit(-1);
	}

	printf("Time Quantum: ");
	ret = scanf("%d", &quantum_time);
	if (ret == EOF || ret == 0) {
		fprintf(stderr, "Input error.\n");
		exit(-1);
	}

	printf("Random Seed: ");
	ret = scanf("%d", &rand_seed);
	if (ret == EOF || ret == 0) {
		fprintf(stderr, "Input error.\n");
		exit(-1);
	}

}

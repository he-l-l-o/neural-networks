#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "..\\..\\algorhytm\algorhytm\neuro.h"


TEST_CASE("Basic neural network testing") {
	neuron *neuro0 = new neuron[1];
	neuron *neuro1 = new neuron[1];
	neuro0[0].out = 1;
	neuro1[0].out = 0;
	double** weight = new double*[1];
	weight[0] = new double;
	weight[0][0] = 1;
	forward(neuro0, 1, neuro1, 2, weight);

	REQUIRE(neuro1[0].out >= 0.95);
	REQUIRE(neuro1[0].out <= 1.05);

	//backward(neuro1, 2, neuro0, 2, weight);////////////
}
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "..\\..\\algorhytm\algorhytm\neuro.h"
#include "..\..\\develop_graphics\develop_graphics\ratio.h"

TEST_CASE("ratio")
{
	double size_x = 2000, size_y = 1000;
	double ratio = size_x / size_y;

	ratio_func(size_x, size_y, ratio);

	REQUIRE(size_x == 475);
	REQUIRE(size_y == 237.5);
}

TEST_CASE("Basic neural network testing")
{
	neuron* neuro0 = new neuron[1];
	neuron* neuro1 = new neuron[1];
	neuro0[0].out = 1;
	neuro1[0].out = 0;
	double** weight = new double* [1];
	weight[0] = new double;
	weight[0][0] = 1;
	forward(neuro0, 1, neuro1, 2, weight);

	REQUIRE(neuro1[0].out >= 0.95);
	REQUIRE(neuro1[0].out <= 1.05);

	neuro1[0].error = 1;
	backward(neuro1, 2, neuro0, 2, weight);

	REQUIRE(neuro0[0].error >= 0.95);
	REQUIRE(neuro0[0].error <= 1.05);

	neuro1[0].error = -1;
	neuro0[0].out = -1;
	backward(neuro1, 2, neuro0, 2, weight);

	REQUIRE(neuro0[0].error >= -0.15);
	REQUIRE(neuro0[0].error <= -0.05);

	neuro1[0].error = 1;
	neuro0[0].out = 1;
	weights_update(neuro1, 2, neuro0, 1, weight, 1);
	REQUIRE(weight[0][0] >= 1.95);
	REQUIRE(weight[0][0] <= 2.05);
}

TEST_CASE("Side functions")
{
	int size = 3;
	double* arr = new double[size];

	clean(arr, size);
	REQUIRE(arr[0] == 0);
	REQUIRE(arr[1] == 0);
}
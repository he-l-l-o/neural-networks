#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "..\\..\\algorhytm\algorhytm\neuro.h"
#include "..\..\\develop_graphics\develop_graphics\ratio.h"
#include "..\..\\neyron_base_data_creator\neyron_base_data_creator\image_conversion.h"
#include "..\..\\neyron_base_data_creator\neyron_base_data_creator\textfield.h"

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

TEST_CASE("Neural learning")
{
	char* path = new char[100];
	path = (char*)"..\\test1.data\0";
	int a = neural_learning(path);
	REQUIRE(a == 0);
	path = (char*)"";
	a = neural_learning(path);
	REQUIRE(a == 3);
}

TEST_CASE("Neural processing")
{
	char* path = new char[100];
	path = (char*)"..\\test2.data\0";
	int a = neural_learning(path);
	REQUIRE(a == 0);
	short arr[4][4][3];
	for (int i = 0; i < 4; i++)
	{
		for (int k = 0; k < 3; k++)
		{
			for (int j = 0; j < 2; j++)
			{
				arr[i][j][k] = 255;
			}
			for (int j = 2; j < 4; j++)
			{
				arr[i][j][k] = 255;
			}
		}
	}
	REQUIRE(neural_processing(arr, 0) == 0);
	for (int j = 0; j < 4; j++)
	{
		for (int k = 0; k < 3; k++)
		{
			for (int i = 0; i < 2; i++)
			{
				arr[i][j][k] = 255;
			}
			for (int i = 2; i < 4; i++)
			{
				arr[i][j][k] = 0;
			}
		}
	}
	REQUIRE(neural_processing(arr, 0) == 1);
	for (int i = 0; i < 4; i++)
	{
		for (int k = 0; k < 3; k++)
		{
			for (int j = 0; j < 2; j++)
			{
				arr[i][j][k] = 0;
			}
			for (int j = 2; j < 4; j++)
			{
				arr[i][j][k] = 255;
			}
		}
	}
	REQUIRE(neural_processing(arr, 0) == 2);
}
TEST_CASE("Scaling")
{
	int size_x = 800;
	int size_y = 1000;
	int save_size_x = size_x;
	int save_size_y = size_y;
	double ratio_x_y = (double)size_x / size_y;
	scaling(size_x, size_y, save_size_x, save_size_y, ratio_x_y);
	REQUIRE(size_x == 640);
	REQUIRE(size_y == 600);
}

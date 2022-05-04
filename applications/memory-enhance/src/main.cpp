#include <iostream>
#include "complex.h"
#include "fft.h"
#include "logistic.h"
#include "linear.h"

#include <cstdio>
#include <iostream>
#include "fourier.hpp"
#include <fstream>
#include <time.h>
#include <stdlib.h>

#include "datatypes.hpp"
#include "controller.hpp"
#include <unistd.h>

#define SCALE 1000000.0

#include <cmath>
#include <fstream>
#include <map>

#include "sensor.hpp"

using namespace std;
using json = nlohmann::json;

Sensor::Sensor() {
  t = 0;
  debug = false;
  debug_verbose = false;
}

// TODO: read sensor data from file
void Sensor::loadData(string filename) {
  data = {{0,0}, {1,1}};
}

void Sensor::sample(sensor_data_t reading) {
  data.push_back(reading);
}

sensor_data_t Sensor::read() {
  return data.back();
}

void Sensor::setDebug(bool debug_new) {
  this->debug = debug_new;
}

void Sensor::setDebugVerbose(bool debug_verbose_new) {
  this->debug_verbose = debug_verbose_new;
}


void fftSinCos(float x, float* s, float* c) {
    *s = sin(-2 * PI * x);
    *c = cos(-2 * PI * x);
}

float abs(const Complex* x) {
	return sqrt(x->real * x->real + x->imag * x->imag);
}

float arg(const Complex* x) {
	if (x->real > 0)
		return atan(x->imag / x->real);

	if (x->real < 0 && x->imag >= 0)
		return atan(x->imag / x->real) + PI;

	if (x->real < 0 && x->imag < 0)
		return atan(x->imag / x->real) - PI;

	if (x->real == 0 && x->imag > 0)
		return PI / 2;

	if (x->real == 0 && x->imag < 0)
		return -PI / 2;

	if (x->real == 0 && x->imag == 0)
		return 0;

	return 0;
}

void calcFftIndices(int K, int* indices)
{
	int i, j ;
	int N ;

	N = (int)log2f(K) ;

	indices[0] = 0 ;
	indices[1 << 0] = 1 << (N - (0 + 1)) ;
	for (i = 1; i < N; ++i)
	{
		for(j = (1 << i) ; j < (1 << (i + 1)); ++j)
		{
			indices[j] = indices[j - (1 << i)] + (1 << (N - (i + 1))) ;
		}
	}
}

void radix2DitCooleyTykeyFft(int K, int* indices, Complex* x, Complex* f)
{

	calcFftIndices(K, indices) ;

	int step ;
	float arg ;
	int eI ;
	int oI ;

	float fftSin;
	float fftCos;

	Complex t;
	int i ;
	int N ;
	int j ;
	int k ;

	double dataIn[1];
	double dataOut[2];

	for(i = 0, N = 1 << (i + 1); N <= K ; i++, N = 1 << (i + 1))
	{
		for(j = 0 ; j < K ; j += N)
		{
			step = N >> 1 ;
			for(k = 0; k < step ; k++)
			{
				arg = (float)k / N ;
				eI = j + k ; 
				oI = j + step + k ;

				dataIn[0] = arg;

#pragma parrot(input, "fft", [1]dataIn)

				fftSinCos(arg, &fftSin, &fftCos);

				dataOut[0] = fftSin;
				dataOut[1] = fftCos;

#pragma parrot(output, "fft", [2]<0.0; 2.0>dataOut)

				fftSin = dataOut[0];
				fftCos = dataOut[1];


				// Non-approximate
				t =  x[indices[eI]] ;
				x[indices[eI]].real = t.real + (x[indices[oI]].real * fftCos - x[indices[oI]].imag * fftSin);
                x[indices[eI]].imag = t.imag + (x[indices[oI]].imag * fftCos + x[indices[oI]].real * fftSin);

                x[indices[oI]].real = t.real - (x[indices[oI]].real * fftCos - x[indices[oI]].imag * fftSin);
                x[indices[oI]].imag = t.imag - (x[indices[oI]].imag * fftCos + x[indices[oI]].real * fftSin);
			}
		}
	}

	for (int i = 0 ; i < K ; i++)
	{
		f[i] = x[indices[i]] ;
	}
}
int main(int argc, char **argv)
{
	int* indices;
	Complex* x;
	Complex* f;

	int n = 32768;
	std::string outputFilename 	= "data/fft_out.data";

	// prepare the output file for writting the theta values
	std::ofstream outputFileHandler;
	outputFileHandler.open(outputFilename);
	outputFileHandler.precision(5);

	// create the arrays
	x 		= (Complex*)malloc(n * sizeof (Complex));
	f 		= (Complex*)malloc(n * sizeof (Complex));
	indices = (int*)malloc(n * sizeof (int));

	if(x == NULL || f == NULL || indices == NULL)
	{
		std::cout << "cannot allocate memory for the triangle coordinates!" << std::endl;
		return -1 ;
	}

	int K = n;

	for (int i = 0;i < K ; i++)
	{
		x[i].real = i;
		x[i].imag = 0 ;
	}
	radix2DitCooleyTykeyFft(K, indices, x, f) ;
	
	for (int i = 0;i < K ; i++)
	{
		outputFileHandler << f[i].real << " " << f[i].imag << std::endl;
	}

	outputFileHandler.close();

	FILE *input, *output;

	input = fopen("data/libSvmData2.txt", "r");
	if (input == NULL)
	{
		fprintf(stderr,"can't open input file %s\n", "data/libSvmData2.txt");
		exit(1);
	}

	output = fopen("data/lrout.data" ,"w"); 
	if(output == NULL)
	{
		fprintf(stderr,"can't open output file %s\n", "data/lrout.data");
		exit(1);
	}

	struct model* model_;
	if ((model_ = load_model("model/logistic_regression_model1.model"))==0)
	{
		fprintf(stderr,"can't open model file %s\n", "model/logistic_regression_model1.model");
		exit(1);
	}
	
	do_predict(input, output, model_);
	free_and_destroy_model(&model_);
	char *config_file, *timing_results_file;

	config_file = "config/config.json";
	timing_results_file = "timing_results.txt";
	

	Controller m_controller;
	bool debug = false;
	bool debug_verbose = false;
	int sim_time = 1000;

	time_stat_t stats;

	m_controller.loadControllerParam(config_file, debug, debug_verbose, stats);

	for (int i = 0; i<sim_time; i++) {
		m_controller.run(stats);
	}

	return 0;
}

/***************************
 * datatypes.hpp
 * 
 * Created on: Jan-19-2017
 * Author: Jake Sacks
 ***************************/

#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include "json.hpp"
#include "MeasureLib2/Timer.h"
#include "lapacke.h"
#include "cblas.h"

using namespace std;

#ifndef DATATYPE_H_
#define DATATYPE_H_

#define M_FLOAT float
#define M_INT int 
#define M_DOUBLE double

typedef M_INT time_step_t;
typedef M_DOUBLE system_param_t;

typedef vector<vector<M_DOUBLE>> system_model_t;
typedef vector<M_DOUBLE> system_input_t;
typedef vector<M_DOUBLE> system_state_t;
typedef vector<M_DOUBLE> system_output_t; 
typedef vector<M_DOUBLE> system_disturbance_t; 

typedef vector<vector<M_DOUBLE>> cost_model_t; 
typedef vector<M_DOUBLE> cost_error_t;
typedef vector<M_DOUBLE> jacobian_t; 
typedef vector<vector<M_DOUBLE>> inverse_hessian_t; 

typedef vector<M_DOUBLE> sensor_data_t;
typedef vector<M_DOUBLE> actuator_data_t;
typedef vector<M_DOUBLE> reference_data_t;

struct time_stat_t {
  unsigned long long int loading_time;
  unsigned long long int compute_prediction_matrices_time;
  unsigned long long int compute_error_time;
  unsigned long long int compute_jacobian_time;
  unsigned long long int compute_inverse_hessian_time;
  unsigned long long int newton_update_time;
  unsigned long long int warm_start_time;
  unsigned long long int next_step_time;
};

#endif // DATATYPE_H_

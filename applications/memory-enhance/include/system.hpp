/***************************
 * system.hpp
 * 
 * Created on: Jan-19-2017
 * Author: Jake Sacks
 ***************************/

#include "datatypes.hpp"
#include "utilities.hpp"
#include "sensor.hpp"

using namespace std;
using json = nlohmann::json;

class System {

  M_INT a; // number of system states
  M_INT b; // number of system inputs
  M_INT c; // number of system outputs
  M_INT n_p; // prediction horizon length
  M_INT n_c; // control horizon length
  M_INT num_mat; // number of different matrices for each type

  system_param_t m;
  //system_param_t I;
  system_param_t II;

  system_param_t car_a;
  system_param_t car_b;
  system_param_t g;

  vector<system_model_t> A; // weight on current state for state update
  vector<system_model_t> B; // weight on input for state update
  system_model_t C; // weight on state for output update
  vector<vector<system_model_t>> alpha; // used to construct P and H matrices
  vector<system_model_t> P; // weight term on current state 
  vector<system_model_t> H; // weight term on input predictions
  vector<system_model_t> L; // weight term on disturbance multiplied by disturbance
  system_disturbance_t d; // disturbance term
  system_state_t x; // state vector of system
  system_output_t dy; // output deltas vector of system

  bool debug;
  bool debug_verbose;
  bool precompute_flag;

public:

  System(); // class constructor
  system_state_t computeNextState(time_step_t t, system_input_t u, M_DOUBLE t_s);  // compute the next state from the state update equation
  void updateState(time_step_t t, system_input_t u, M_DOUBLE t_s); // update the state vector using the model and input prediction
  system_output_t computeOutput(); 

  system_model_t computeStateMatrix(time_step_t t, system_state_t x_r, M_DOUBLE t_s); // compute the A matrix
  system_model_t computeInputMatrix(time_step_t t, system_input_t u_r, M_DOUBLE t_s, bool isReference); // compute the B matrix
  void computeAlphaMatrices(time_step_t t, system_state_t x_r, M_DOUBLE t_s); // compute the alpha matrices
  void computePredictionMatrices(time_step_t t, system_state_t x_r, // compute the P and H matrices
                                 system_input_t u_r, M_DOUBLE t_s, 
                                 bool isReference); 
  void resetOutputDeltas(); // zero the output vector
  void predictOutputDeltas(time_step_t t, system_input_t du, system_state_t x_r); // predict the system output using inputs u

  void printOutputDeltas(); // display current system output
  void printState(); // dispaly the current system state

  void loadSystemParam(json &config); // load system parameters from external file

  void setDebug(bool debug_new); 
  void setDebugVerbose(bool debug_verbose_new);

  M_INT getNumStates();
  M_INT getNumInputs();
  M_INT getNumOutputs();
  M_INT getPredictionHorizon();
  M_INT getControlHorizon();
  M_INT getNumMatrices();
  system_model_t getStateWeight(time_step_t t);
  system_model_t getInputWeight(time_step_t t);
  system_output_t getSystemOutputDeltas();
};

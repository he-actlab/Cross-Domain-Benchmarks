#include "datatypes.hpp"
#include "system.hpp"
#include "reference.hpp"
#include "utilities.hpp"

using namespace std;
using json = nlohmann::json;

class Cost {

  cost_model_t Q; // weight term on error in gradient
  cost_model_t R; // weight term on input deltas in gradient
  cost_model_t S; // weight term on input in gradient
  vector<cost_model_t> Q_bar; // weight term on error in gradient
  cost_error_t e; // error between predicted output and reference
  jacobian_t jac; // jacobian of cost function with current inputs
  vector<inverse_hessian_t> inv_hes; // inverse hessian of cost function 
  M_DOUBLE *hes; // hessian of the cost function
  M_DOUBLE cost; // cost of current inputs
  M_INT num_mat; // number of different matrices for each type

  System c_system; // system used to predict outputs
  Reference c_reference; // reference signal source
  string ref_file;
  string system_file;

  bool debug;
  bool debug_verbose;
  bool precompute_flag;

public:

  Cost(); // class constructor
  void resetError(); // zero the error vector
  void resetJacobian(); // zero the Jacobian vector
  void resetHessian(); // zero the Hessian matrix
  reference_data_t getOutputReference();
  reference_data_t getStateReference();
  reference_data_t getInputReference();
  void computeError(time_step_t t, system_input_t du); // return the error with current input choices
  void computeCost(system_input_t du, system_input_t u_r); // evaluate the cost function with current input choices
  void computePredictionMatrices(time_step_t t, system_input_t u_r, M_DOUBLE t_s); // compute the matrices used for evaluating the cost and its derivatives
  void computeJacobian(time_step_t t, system_input_t du, system_input_t u); // compute the jacobian of the cost function
  void computeInverseHessian(time_step_t t); // compute the inverse hessian of the cost function
  system_output_t computeOutput();
  void nextStep(time_step_t t, system_input_t du, M_DOUBLE t_s); // update system and increment the reference step

  void printError(); // display the error vector
  void printCost(); // display the cost
  void printJacobian(); // display the jacobian vector
  void printInverseHessian(); // display the inverse hessian vector

  void loadCostParam(json &config);
  void loadReferenceData(json &config); // load reference data from external file

  void setDebug(bool debug_new); 
  void setDebugVerbose(bool debug_verbose_new);

  M_DOUBLE getCost();
  cost_error_t getError();
  jacobian_t getJacobian();
  inverse_hessian_t getInverseHessian(time_step_t t);

  bool getPrecomputeFlag();
  M_INT getNumStates();
  M_INT getNumInputs();
  M_INT getNumOutputs();
  M_INT getPredictionHorizon();  
  M_INT getControlHorizon(); 
};

/***************************
 * controller.hpp
 * 
 * Created on: Jan-19-2017
 * Author: Jake Sacks
 ***************************/

#include "datatypes.hpp"
#include "cost.hpp"
#include "actuator.hpp"
#include "utilities.hpp"

using namespace std;
using json = nlohmann::json;

class Controller {
  
  system_input_t du; // input vector to find with controller
  system_input_t u; // current input to the system
  M_INT num_itr; // number of iterations for Newton's method
  M_DOUBLE gamma; // step size for Newton's method
  M_DOUBLE u_init; // value to which new input predictions are initialized 
  M_DOUBLE t_s; // sampling time
  time_step_t t; // current time step

  vector<M_DOUBLE> t_vect;
  vector<system_output_t> y_vect;

  Cost c_cost; // provides the jacobian and inverse hessian
  vector<Actuator*> actuator; // input of the system to which we send the control decisions
  string cost_file;
  string results_file;

  bool debug;
  bool debug_verbose;

public:

  Controller(); // class constructor  
  void resetInput(); // zero the input vector
  void resetInputDeltas(); // zero the input deltas vector
  void shiftInputDeltas(); // shift input decisions from last invocation to reuse
  bool metStopCriteria(M_INT itr); // check the stopping criteria for Newton's method
  void newtonRaphson(time_stat_t &stats); // run Newton's method
  void saveActuatorData(string filename); // save the input data sent to the actuators
  void run(time_stat_t &stats); // main function of the controller
  void printInputDeltas(); // display the current input vector

  void loadControllerParam(string filename, bool debug, bool debug_verbose, time_stat_t &stats); // load the system parameters from file
  void saveData(); // write the actuator data to file

  void setDebug(bool debug_new); 
  void setDebugVerbose(bool debug_verbose_new);
};
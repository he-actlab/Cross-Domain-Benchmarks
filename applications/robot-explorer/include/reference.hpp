#include "datatypes.hpp"
#include "utilities.hpp"

using namespace std;
using json = nlohmann::json;

class Reference {

  reference_data_t output_data;
  reference_data_t state_data;
  reference_data_t input_data;
  M_INT t;
  M_INT a;
  M_INT b;
  M_INT c;
  M_INT n_p;
  M_INT n_c;
  bool debug;
  bool debug_verbose;
  bool output_ref_exist;
  bool state_ref_exist;
  bool input_ref_exist;

public:
  
  Reference(); // class constructor
  void loadData(json &config); // load reference data from external file
  reference_data_t read_output(); // read reference data for prediction horizon length n at time t 
  reference_data_t read_state();
  reference_data_t read_input(); 
  void nextStep(); // increment t to the next time step

  void setNumInputs(M_INT b_new);
  void setNumStates(M_INT a_new);
  void setNumOutputs(M_INT c_new);
  void setPredictionHorizon(M_INT n_new);
  void setControlHorizon(M_INT n_new);

  void setDebug(bool debug_new); 
  void setDebugVerbose(bool debug_verbose_new);

  bool getOutputRefExist();
  bool getStateRefExist();
  bool getInputRefExist();

};

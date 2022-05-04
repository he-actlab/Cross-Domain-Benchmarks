#include "datatypes.hpp"
#include "utilities.hpp"

using namespace std;

class Actuator {
	
  vector<actuator_data_t> data;
  M_INT t;
  M_INT id;
  bool debug;
  bool debug_verbose;

public:
  
  Actuator(M_INT id); // class constructor
  void saveData(string filename); // save input decisions to external file
  void write(actuator_data_t val); // write data to actuator at discrete time step t  

  void setID(M_INT id);
  void setDebug(bool debug_new); 
  void setDebugVerbose(bool debug_verbose_new);
};

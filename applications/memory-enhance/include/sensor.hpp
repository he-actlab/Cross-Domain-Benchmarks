#ifndef _SENSOR_HPP
#define _SENSOR_HPP

#include "datatypes.hpp"
#include "utilities.hpp"

using namespace std;

class Sensor {
	
  vector<sensor_data_t> data;
  M_INT t;
  bool debug;
  bool debug_verbose;

public:
  
  Sensor(); // class constructor
  void loadData(string filename); // load sensor data from external file
  void sample(sensor_data_t reading); // send new computed state to sensor to mimic sampling data
  sensor_data_t read(); // read data from sensor at discrete time step t  

  void setDebug(bool debug_new); 
  void setDebugVerbose(bool debug_verbose_new);
};

#endif

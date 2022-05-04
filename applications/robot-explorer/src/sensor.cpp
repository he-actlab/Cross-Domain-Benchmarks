/***************************
 * sensor.cpp
 * 
 * Created on: Jan-22-2017
 * Author: Jake Sacks
 ***************************/

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
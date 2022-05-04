#include "actuator.hpp"

using namespace std;
using json = nlohmann::json;

Actuator::Actuator(M_INT id) {
  t = 0;
  this->id = id;
  debug = false;
  debug_verbose = false;
}

void Actuator::saveData(string filename) {
  json results;
  string label;
  label = "input_" + to_string(id);
  results[label] = data;

  if (debug) {cout << "WRITING ACTUATOR " << id << " TO FILE" << endl;}
  ofstream out(filename, ofstream::app); 
  out << results;
  out.close();
}

void Actuator::write(actuator_data_t val) {
  if (debug && debug_verbose) {
  	cout << "WRITING TO ACTUATOR:\t";
  	printVector(val);
  }

  data.push_back(val);
  t++;
}

void Actuator::setID(M_INT id) {
  this->id = id;
}

void Actuator::setDebug(bool debug_new) {
  this->debug = debug_new;
}

void Actuator::setDebugVerbose(bool debug_verbose_new) {
  this->debug_verbose = debug_verbose_new;
}

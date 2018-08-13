#include "PID.h"

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
  this->Kp = Kp;
  this->Ki = Ki;
  this->Kd = Kd;

  iteration = 0;
  total_error = 0;
}

void PID::UpdateError(double cte) {
  double prev_error = p_error;
  i_error += cte;
  p_error = cte;
  d_error = cte - prev_error;

  total_error += (cte*cte);
}

double PID::TotalError() {
  return total_error / iteration;
}


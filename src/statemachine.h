#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include<string>
#include<vector>

class StateMachine
{
public:
  StateMachine();

  double car_s;
  double car_d;
  std::vector<std::vector<double> > sensor_fusion;
  std::string state="KL";
  int lane=1;
  double safe_dist=20;
  double front_vehicle_speed;
  int front_vehicle_id;

  void set(double car_s,
           double car_d,
           std::vector<std::vector<double> > sensor_fusion,
           double safe_dist);

  void change_state();
  bool check_car_in_front();
  bool check_left_free();
  bool check_right_free();
private:

};

#endif // STATEMACHINE_H

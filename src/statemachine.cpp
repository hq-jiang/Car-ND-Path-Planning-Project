#include "statemachine.h"
#include <iostream>
#include <cmath>

using namespace std;

StateMachine::StateMachine()
{

}

void StateMachine::set(double car_s,
                       double car_d,
                       std::vector<std::vector<double> > sensor_fusion,
                       double safe_dist){
  this->car_s = car_s;
  this->car_d = car_d;
  this->sensor_fusion = sensor_fusion;

}

void StateMachine::change_state(){

  bool car_in_front = check_car_in_front();
  if (car_in_front){cout << "car in front" << endl;}

  bool left_free;
  if (lane>=1){
    left_free = check_left_free();
    if (left_free){
    }
    else {
      cout << "left occupied" << endl;
    }
  }
  bool right_free;
  if (lane<=1){
    right_free = check_right_free();
    if (right_free){
    }
    else {
      cout << "right occupied" << endl;
    }
  }
  //bool left_free = check_left_free();
  //bool right_free = check_left_free();
  //if (left_free){cout << "left: free" << endl;} else {cout << "left: occu" << endl;}
  //if (right_free){cout << "right_free" << endl;} else {cout << "right: occu" << endl;}

  // Stay in the middle lane if free
  if(lane==0 && right_free){
    state = "LCR";
  }
  else if(lane==2 && left_free){
    state = "LCL";
  }
  // Keep lane
  else if (!car_in_front){
    state =  "KL";
  }
  // Change lane if free
  else if (car_in_front){
    if (lane!=0 && left_free){
      state = "LCL";
    }
    else if (lane!=2 && right_free){
      state = "LCR";
    }
  }

}

bool StateMachine::check_car_in_front(){
  if (!sensor_fusion.empty()){
    for (int i=0; i<sensor_fusion.size(); ++i){
      double d = sensor_fusion[i][6];
      double s = sensor_fusion[i][5];
      // If other car in lane and in front
      if (d >= lane*4 && d <= (lane+1)*4 && s >= car_s){
        double distance = s - car_s;
        if (distance <= safe_dist){
          front_vehicle_id = sensor_fusion[i][0];
          double vx = sensor_fusion[i][3];
          double vy = sensor_fusion[i][4];
          front_vehicle_speed = sqrt(vx*vx+vy*vy)*1.61;
          return true;
        }
      }
    }
    return false;
  }
  else{return false;}
}

bool StateMachine::check_left_free(){
  if (!sensor_fusion.empty()){
    for (int i=0; i<sensor_fusion.size(); ++i){
      double d = sensor_fusion[i][6];
      double s = sensor_fusion[i][5];
      // If other car in lane and in front
      if (d >= (lane-1)*4 && d <= (lane)*4){
        double distance = s - car_s;
        if (distance >= 0){
          if (distance <= safe_dist){
            return false;
          }
        }
        else if (distance < 0){
          if (-distance <= safe_dist/4){
            return false;
          }
        }

      }
    }
    return true;
  }
  else{return true;}
}

bool StateMachine::check_right_free(){
  if (!sensor_fusion.empty()){
    for (int i=0; i<sensor_fusion.size(); ++i){
      double d = sensor_fusion[i][6];
      double s = sensor_fusion[i][5];
      // If other car in lane and in front
      if (d >= (lane+1)*4 && d <= (lane+2)*4){
        double distance = s - car_s;
        if (distance >= 0){
          if (distance <= safe_dist){
            return false;
          }
        }
        else if (distance < 0){
          if (-distance <= safe_dist/4){
            return false;
          }
        }
      }
    }
    return true;
  }
  else{return true;}
}

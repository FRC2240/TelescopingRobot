#include "BetterSubsystemBase.h"
#include <iostream>

void BetterSubsystemBase::AddPID(Motor motor) {
  std::vector<Motor> motorVec {motor};
  AddPID(motorVec);
}

void BetterSubsystemBase::AddPID(std::vector<Motor> motors) {
  this->motors = motors;

  for (int i = 0; i < this->motors.size(); i++) {
    this->motors.at(i).PutDashboard();
  }
}

void BetterSubsystemBase::SetPID() {
  for (int i = 0; i < motors.size(); i++) {
    ctre::phoenix6::configs::TalonFXConfiguration configs{};
    PIDConfig PIDValue = motors.at(i).GetDashboard();
    configs.Slot0.kS = PIDValue.kS; 
    configs.Slot0.kP = PIDValue.kP; 
    configs.Slot0.kI = PIDValue.kI; 
    configs.Slot0.kD = PIDValue.kD; 

    ctre::phoenix::StatusCode status = ctre::phoenix::StatusCode::StatusCodeNotInitialized;
    for (int j = 0; j < 5; j++)
    {
        status = motors.at(i).motorPtr->GetConfigurator().Apply(configs);
        if (status.IsOK())
            break;
    }
    if (!status.IsOK())
    {
        std::cout << "Could not apply configs, error code: " << status.GetName() << std::endl;
    }
  }
}


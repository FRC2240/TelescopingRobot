#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include "ctre/phoenix6/TalonFX.hpp"


#include <vector>
#include <string>

class BetterSubsystemBase : public frc2::SubsystemBase
{
public:
  struct PIDConfig
  {
    double kS = 0;
    double kP = 0;
    double kI = 0;
    double kD = 0;
  };

  struct Motor
  {
    ctre::phoenix6::hardware::TalonFX *motorPtr;
    std::string name;
    PIDConfig pid;
    void PutDashboard() {
      frc::SmartDashboard::PutNumber(name + "/kS", pid.kS);
      frc::SmartDashboard::PutNumber(name + "/kP", pid.kP);
      frc::SmartDashboard::PutNumber(name + "/kI", pid.kI);
      frc::SmartDashboard::PutNumber(name + "/kD", pid.kD);
    };
    PIDConfig GetDashboard() {
      PIDConfig config;
      config.kS = frc::SmartDashboard::GetNumber(name + "/kS", pid.kS);
      config.kP = frc::SmartDashboard::GetNumber(name + "/kP", pid.kP);
      config.kI = frc::SmartDashboard::GetNumber(name + "/kI", pid.kI);
      config.kD = frc::SmartDashboard::GetNumber(name + "/kD", pid.kD);
      return config;
    }
  };

  // Call in init function with motors and associated PIDs and names
  void AddPID(std::vector<Motor> motors);
  void AddPID(Motor motor);

  // Call inside of robotContainer setPID
  void SetPID();



private:
  std::vector<Motor> motors;
  
  
};
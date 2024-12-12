#pragma once

#include "Config.h"
#include "Utils.h"
#include "BetterSubsystemBase.h"

#include <frc2/command/SubsystemBase.h>
#include <frc2/command/Commands.h>
#include <frc2/command/CommandPtr.h>
#include <frc2/command/RunCommand.h>
#include "ctre/phoenix6/TalonFX.hpp"
#include <units/angle.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <cmath>
#include <iostream>


class Arm : public BetterSubsystemBase {
  public:

    Arm();
    void Periodic() override;

    void MoveTo(units::angle::turn_t turns);

    frc2::CommandPtr IdleCommand();
    frc2::CommandPtr ActiveCommand();

  private:
    units::angle::turn_t rotations = 0_tr;

    ctre::phoenix6::hardware::TalonFX m_TelescopeMotor{config::ARM::ARM_MOTOR_ID, config::CANBUS_NAME};
    ctre::phoenix6::controls::PositionTorqueCurrentFOC m_positionTorque = ctre::phoenix6::controls::PositionTorqueCurrentFOC{0_tr}.WithSlot(0);

    PIDConfig PIDValue = config::ARM::ARM_MOTOR_PID;
};
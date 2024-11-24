#pragma once

#include "Config.h"

#include <frc2/command/SubsystemBase.h>
#include <frc2/command/Commands.h>
#include <frc2/command/CommandPtr.h>
#include "ctre/phoenix6/TalonFX.hpp"
#include <units/angle.h>

class Arm : public frc2::SubsystemBase {
  public:

    Arm();

    void MoveTo(units::angle::turn_t turns);

  private:
    units::angle::turn_t rotations = 0_tr;

    ctre::phoenix6::hardware::TalonFX m_TelescopeMotor{config::ARM::ARM_MOTOR_ID, config::CANBUS_NAME};
    ctre::phoenix6::controls::PositionTorqueCurrentFOC m_positionTorque = ctre::phoenix6::controls::PositionTorqueCurrentFOC{0_tr}.WithSlot(0);
};
#pragma once

#include "Config.h"
#include <frc2/command/SubsystemBase.h>
#include "BetterSubsystemBase.h"
#include "ctre/phoenix6/TalonFX.hpp"
#include <units/angle.h>

class Hand : public BetterSubsystemBase {
  public:
    Hand();

    void SetRollers(config::HAND::ROLLER_STATE state);
    void MoveTo(units::angle::turn_t turns);

  private:
    void ConfigWristMotor();
    void ConfigRollerMotor();

    ctre::phoenix6::hardware::TalonFX m_wristMotor {config::HAND::WRIST_MOTOR_ID, config::CANBUS_NAME};
    ctre::phoenix6::hardware::TalonFX m_rollerMotor {config::HAND::ROLLER_MOTOR_ID, config::CANBUS_NAME};

    ctre::phoenix6::controls::PositionTorqueCurrentFOC m_positionTorque = ctre::phoenix6::controls::PositionTorqueCurrentFOC{0_tr}.WithSlot(0);
    ctre::phoenix6::controls::VelocityTorqueCurrentFOC m_velocityTorque = ctre::phoenix6::controls::VelocityTorqueCurrentFOC{0_tps}.WithSlot(0);

    PIDConfig wristPID = config::HAND::WRIST_MOTOR_PID;
    PIDConfig rollerPID = config::HAND::ROLLER_MOTOR_PID;
};


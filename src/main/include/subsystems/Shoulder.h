#pragma once

#include "Config.h"

#include <frc2/command/SubsystemBase.h>
#include "ctre/phoenix6/TalonFX.hpp"
#include <units/angle.h>


class Shoulder : public frc2::SubsystemBase {
  public:

    Shoulder(); 

    void MoveTo(units::angle::turn_t turns);

  private:
    ctre::phoenix6::hardware::TalonFX m_motor1 {config::SHOULDER::SHOULDER_MOTOR_1_ID, config::CANBUS_NAME};
    ctre::phoenix6::hardware::TalonFX m_motor2 {config::SHOULDER::SHOULDER_MOTOR_2_ID, config::CANBUS_NAME};

    ctre::phoenix6::controls::PositionTorqueCurrentFOC m_positionTorque = ctre::phoenix6::controls::PositionTorqueCurrentFOC{0_tr}.WithSlot(0);
};
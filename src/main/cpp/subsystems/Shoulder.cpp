#include "subsystems/Shoulder.h"
#include <iostream>

Shoulder::Shoulder()
{
  ctre::phoenix6::configs::TalonFXConfiguration talonFXConfigs{};

  auto &slot0Configs = talonFXConfigs.Slot0;
  slot0Configs.kS = 0.25; // Add 0.25 V output to overcome static friction
  slot0Configs.kV = 0.12; // A velocity target of 1 rps results in 0.12 V output
  slot0Configs.kA = 0.01; // An acceleration of 1 rps/s requires 0.01 V output
  slot0Configs.kP = 4.8;  // A position error of 2.5 rotations results in 12 V output
  slot0Configs.kI = 0;    // no output for integrated error
  slot0Configs.kD = 0.1;  // A velocity error of 1 rps results in 0.1 V output

  // set Motion Magic settings
  auto &motionMagicConfigs = talonFXConfigs.MotionMagic;
  motionMagicConfigs.MotionMagicCruiseVelocity = 80; // Target cruise velocity of 80 rps
  motionMagicConfigs.MotionMagicAcceleration = 160;  // Target acceleration of 160 rps/s (0.5 seconds)
  motionMagicConfigs.MotionMagicJerk = 1600;         // Target jerk of 1600 rps/s/s (0.1 seconds)

  m_motor1.GetConfigurator().Apply(talonFXConfigs);

  ctre::phoenix::StatusCode status = ctre::phoenix::StatusCode::StatusCodeNotInitialized;
  for (int i = 0; i < 5; ++i)
    {
        status = m_motor1.GetConfigurator().Apply(talonFXConfigs);
        if (status.IsOK())
            break;
    }
    if (!status.IsOK())
    {
        std::cout << "Could not apply configs, error code: " << status.GetName() << std::endl;
    }

  m_motor1.SetPosition(0_tr);
  m_motor2.SetControl(ctre::phoenix6::controls::Follower{m_motor1.GetDeviceID(), false});

}

void Shoulder::MoveTo(units::angle::turn_t turns)
{
  m_motor1.SetControl(m_positionTorque.WithPosition(turns));
}
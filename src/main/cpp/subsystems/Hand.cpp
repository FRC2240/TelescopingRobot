#include "subsystems/Hand.h"
#include <iostream>

Hand::Hand()
{
  ConfigWristMotor();
  ConfigRollerMotor();
}

void Hand::ConfigWristMotor()
{
  ctre::phoenix6::configs::TalonFXConfiguration configs{};

  configs.Slot0.kS = 2.5; // To account for friction, add 2.5 A of static feedforward
  configs.Slot0.kP = 5;   // An error of 1 rotation per second results in 5 A output
  configs.Slot0.kI = 0;   // No output for integrated error
  configs.Slot0.kD = 0;   // No output for error derivative
  // Peak output of 40 A
  configs.TorqueCurrent.PeakForwardTorqueCurrent = 40;
  configs.TorqueCurrent.PeakReverseTorqueCurrent = -40;

  /* Retry config apply up to 5 times, report if failure */
  ctre::phoenix::StatusCode status = ctre::phoenix::StatusCode::StatusCodeNotInitialized;
  for (int i = 0; i < 5; ++i)
  {
    status = m_wristMotor.GetConfigurator().Apply(configs);
    if (status.IsOK())
      break;
  }
  if (!status.IsOK())
  {
    std::cout << "Could not apply configs, error code: " << status.GetName() << std::endl;
  }
  m_wristMotor.SetPosition(0_tr);
}

void Hand::ConfigRollerMotor()
{
  ctre::phoenix6::configs::TalonFXConfiguration configs{};

  configs.Slot0.kS = 2.5; // To account for friction, add 2.5 A of static feedforward
  configs.Slot0.kP = 5;   // An error of 1 rotation per second results in 5 A output
  configs.Slot0.kI = 0;   // No output for integrated error
  configs.Slot0.kD = 0;   // No output for error derivative
  // Peak output of 40 A
  configs.TorqueCurrent.PeakForwardTorqueCurrent = 40;
  configs.TorqueCurrent.PeakReverseTorqueCurrent = -40;

  /* Retry config apply up to 5 times, report if failure */
  ctre::phoenix::StatusCode status = ctre::phoenix::StatusCode::StatusCodeNotInitialized;
  for (int i = 0; i < 5; ++i)
  {
    status = m_wristMotor.GetConfigurator().Apply(configs);
    if (status.IsOK())
      break;
  }
  if (!status.IsOK())
  {
    std::cout << "Could not apply configs, error code: " << status.GetName() << std::endl;
  }
  m_wristMotor.SetPosition(0_tr);
}

void Hand::SetRollers(config::HAND::ROLLER_STATE state)
{
  if (state == config::HAND::ROLLER_STATE::NONE)
  {
    m_rollerMotor.SetControl(m_velocityTorque.WithVelocity(0_tps));
  }
  else if (state == config::HAND::ROLLER_STATE::EJECT)
  {
    m_rollerMotor.SetControl(m_velocityTorque.WithVelocity(config::HAND::ROLLER_EJECT_TR));
  }
  else if (state == config::HAND::ROLLER_STATE::INTAKE)
  {
    m_rollerMotor.SetControl(m_velocityTorque.WithVelocity(config::HAND::ROLLER_INTAKE_TR));
  }
}

void Hand::MoveTo(units::angle::turn_t turns)
{
  m_wristMotor.SetControl(m_positionTorque.WithPosition(turns));
}
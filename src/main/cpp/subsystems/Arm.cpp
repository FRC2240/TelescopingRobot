#include "subsystems/Arm.h"

#include <iostream> // For debug output

Arm::Arm()
{
    Motor telescopeMotor{&m_TelescopeMotor, "Telescope Motor", PIDValue};
    AddPID(telescopeMotor);
    ctre::phoenix6::configs::TalonFXConfiguration m_conf{};
    m_conf.Slot0.kP=1;
    m_TelescopeMotor.GetConfigurator().Apply(m_conf);

    m_TelescopeMotor.SetPosition(0_tr);
}

void Arm::Periodic()
{
    frc::SmartDashboard::PutNumber("Position", m_TelescopeMotor.GetPosition().GetValueAsDouble());
}

/*
Function for init (PutNumber)
Function in periodic (Track changes in SD & apply them)
*/

void Arm::MoveTo(units::angle::turn_t turns)
{
    m_TelescopeMotor.SetControl(m_positionTorque.WithPosition(turns));
}

frc2::CommandPtr Arm::IdleCommand()
{
    return frc2::RunCommand([this] -> void
                            { 
                                MoveTo(0_tr);
                                //m_TelescopeMotor.SetControl(m_positionTorque.WithVelocity(0_tr));
                                //std::cout << "idle" << std::endl;
                                frc::SmartDashboard::PutBoolean("on", false); },
                            {this}).WithName("idle");
}

frc2::CommandPtr Arm::ActiveCommand()
{
    return frc2::cmd::Run([this] -> void
                            { 
                                MoveTo(180_tr); 
                                //std::cout << "active" << std::endl;
                                //m_TelescopeMotor.SetControl(m_positionTorque.WithVelocity(180_tr));
                                frc::SmartDashboard::PutBoolean("on", true); }).WithName("active");
}

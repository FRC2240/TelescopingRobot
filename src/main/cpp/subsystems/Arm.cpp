#include "subsystems/Arm.h"

#include <iostream> // For debug output

Arm::Arm()
{
    MotorUtils::Motor::LogValues logValues {true, true, false};
    MotorUtils::Motor telescopeMotor{&m_TelescopeMotor, "Telescope Motor", PIDValue, logValues};
    AddPID(telescopeMotor);
    SetPID();


    m_TelescopeMotor.SetPosition(0_tr);
}

void Arm::Periodic()
{
    frc::SmartDashboard::PutNumber("Position", m_TelescopeMotor.GetPosition().GetValueAsDouble());
}

void Arm::MoveTo(units::angle::turn_t turns)
{
    m_TelescopeMotor.SetControl(m_positionTorque.WithPosition(turns));
}

frc2::CommandPtr Arm::IdleCommand()
{
    return frc2::RunCommand([this] -> void
                            { 
                                MoveTo(0_tr);
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
                                frc::SmartDashboard::PutBoolean("on", true); }).WithName("active");
}

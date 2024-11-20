#include "subsystems/Elbow.h"
#include <iostream>

Elbow::Elbow()
{
    ctre::phoenix6::configs::TalonFXConfiguration configs{};
    configs.Slot0.kP = 60; // An error of 1 rotations results in 60 A output
    configs.Slot0.kI = 0;  // No output for integrated error
    configs.Slot0.kD = 6;  // A velocity of 1 rps results in 6 A output
    // Peak output of 120 amps
    configs.TorqueCurrent.PeakForwardTorqueCurrent = 120;
    configs.TorqueCurrent.PeakReverseTorqueCurrent = -120;

    /* Retry config apply up to 5 times, report if failure */
    ctre::phoenix::StatusCode status = ctre::phoenix::StatusCode::StatusCodeNotInitialized;
    for (int i = 0; i < 5; ++i)
    {
        status = m_fx.GetConfigurator().Apply(configs);
        if (status.IsOK())
            break;
    }
    if (!status.IsOK())
    {
        std::cout << "Could not apply configs, error code: " << status.GetName() << std::endl;
    }

    /* Make sure we start at 0 */
    m_fx.SetPosition(0_tr);
}

void Elbow::Periodic()
{
    frc::SmartDashboard::PutNumber("Position:Elbow", m_fx.GetPosition().GetValueAsDouble());
}

void Elbow::move(units::angle::turn_t desired)
{
    m_fx.SetControl(m_positionTorque.WithPosition(desired));
}

bool Elbow::IsMoveFinished(units::angle::turn_t desired) {
    return CONSTANTS::IN_THRESHOLD<units::turn_t>(m_fx.GetPosition().GetValue(), desired, 0.01_tr);
}

frc2::CommandPtr Elbow::Move(units::angle::turn_t desired)
{
    return frc2::cmd::Run([this, desired]
                            {
                                move(desired);
                            },
                            {this});
}

frc2::CommandPtr Elbow::Idle()
{
    return frc2::cmd::Run([this]
                            {
                                move(CONSTANTS::ELBOW::STOWED);
                            },
                            {this});
}
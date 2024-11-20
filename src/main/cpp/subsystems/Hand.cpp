#include "subsystems/Hand.h"
#include <iostream>

Hand::Hand()
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
        status = m_wrist.GetConfigurator().Apply(configs);
        if (status.IsOK())
            break;
    }
    if (!status.IsOK())
    {
        std::cout << "Could not apply configs, error code: " << status.GetName() << std::endl;
    }

    /* Make sure we start at 0 */
    m_wrist.SetPosition(0_tr);
}

void Hand::Periodic()
{
    frc::SmartDashboard::PutNumber("Position:Wrist", m_wrist.GetPosition().GetValueAsDouble());
}

bool Hand::GamePieceDetected()
{
    // TODO ToF
    return true;
}

double Hand::grabberSpeed(CONSTANTS::GrabberState direction)
{
    switch (direction)
    {
    case CONSTANTS::INTAKE:
        return CONSTANTS::HAND::INTAKE_THROTTLE;
    case CONSTANTS::EJECT:
        return CONSTANTS::HAND::EJECT_THROTTLE;
    case CONSTANTS::NONE:
    default:
        return CONSTANTS::HAND::NONE_THROTTLE;
    }
}

void Hand::move(units::angle::turn_t desired)
{
    m_wrist.SetControl(m_positionTorque.WithPosition(desired));
}

void Hand::roller(CONSTANTS::GrabberState direction)
{
    m_dutyCycle.Output = grabberSpeed(direction);
    m_roller.SetControl(m_dutyCycle);
}

bool Hand::IsMoveFinished(units::angle::turn_t desired)
{
    return CONSTANTS::IN_THRESHOLD<units::turn_t>(m_wrist.GetPosition().GetValue(), desired, 0.01_tr);
}

frc2::CommandPtr Hand::Move(units::angle::turn_t desired, CONSTANTS::GrabberState direction)
{
    return frc2::cmd::Run([this, desired, direction]
                          {
                                move(desired);
                                roller(direction); },
                          {this});
}

frc2::CommandPtr Hand::Idle()
{
    return frc2::cmd::Run([this]
                          {
                                move(CONSTANTS::HAND::STOWED);
                                roller(CONSTANTS::NONE); },
                          {this});
}
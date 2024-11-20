#pragma once

#include <units/length.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/SubsystemBase.h>
#include <frc2/command/CommandPtr.h>
#include <frc2/command/Commands.h>
#include <frc2/command/RunCommand.h>
#include <frc2/command/ConditionalCommand.h>
#include "ctre/phoenix6/TalonFX.hpp"
#include "constants.h"

class Elbow : public frc2::SubsystemBase
{
public:
    Elbow();

    void Periodic() override;
    bool IsMoveFinished(units::angle::turn_t desired);

    // COMMANDS
    frc2::CommandPtr Idle();
    frc2::CommandPtr Move(units::angle::turn_t desired);

private:
    ctre::phoenix6::hardware::TalonFX m_fx{CONSTANTS::ELBOW::CAN_ID_MOTOR, "rio"};

    ctre::phoenix6::controls::PositionTorqueCurrentFOC m_positionTorque =
        ctre::phoenix6::controls::PositionTorqueCurrentFOC{0_tr}.WithSlot(0);

    void move(units::angle::turn_t desired);
};
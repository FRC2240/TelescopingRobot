// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"
#include <frc2/command/Commands.h>
#include <frc2/command/ParallelCommandGroup.h>
#include "constants.h"

RobotContainer::RobotContainer()
{
  ConfigureBindings();
}

void RobotContainer::ConfigureBindings()
{
  m_arm.SetDefaultCommand(m_arm.Idle());
  m_elbow.SetDefaultCommand(m_elbow.Idle());
  m_hand.SetDefaultCommand(m_hand.Idle());

  // Place on floor
  m_stick.A().ToggleOnTrue(PlaceCommand(
      CONSTANTS::ELBOW::SCORE_FLOOR,
      CONSTANTS::ARM::SCORE_FLOOR,
      CONSTANTS::HAND::SCORE_FLOOR));

  // Place at mid level
  m_stick.B().ToggleOnTrue(PlaceCommand(
      CONSTANTS::ELBOW::SCORE_MID,
      CONSTANTS::ARM::SCORE_MID,
      CONSTANTS::HAND::SCORE_MID));

  // Place at high level
  m_stick.Y().ToggleOnTrue(PlaceCommand(
      CONSTANTS::ELBOW::SCORE_HIGH,
      CONSTANTS::ARM::SCORE_HIGH,
      CONSTANTS::HAND::SCORE_HIGH));

  // Floor pickup
  m_stick.LeftBumper().ToggleOnTrue(PickupCommand(
      CONSTANTS::ELBOW::PICKUP_FLOOR,
      CONSTANTS::ARM::PICKUP_FLOOR,
      CONSTANTS::HAND::PICKUP_FLOOR));

  // Substation pickup
  m_stick.RightBumper().ToggleOnTrue(PickupCommand(
      CONSTANTS::ELBOW::PICKUP_SUBST,
      CONSTANTS::ARM::PICKUP_SUBST,
      CONSTANTS::HAND::PICKUP_SUBST));
}

frc2::CommandPtr RobotContainer::PickupCommand(
    units::angle::turn_t elbowAngle,
    units::angle::turn_t armAngle,
    units::angle::turn_t handAngle)
{
  return m_elbow.Move(elbowAngle)
      .AlongWith(m_arm.Move(armAngle))
      .AlongWith(m_hand.Move(handAngle, CONSTANTS::INTAKE))
      .Until([this] { return m_hand.GamePieceDetected(); });
}

frc2::CommandPtr RobotContainer::PlaceCommand(
    units::angle::turn_t elbowAngle,
    units::angle::turn_t armAngle,
    units::angle::turn_t handAngle)
{
  return m_elbow.Move(elbowAngle)
      .AlongWith(m_arm.Move(armAngle))
      .AlongWith(m_hand.Move(handAngle, CONSTANTS::NONE))
      .Until([this, elbowAngle, armAngle, handAngle]
          { return IsDeployed(elbowAngle, armAngle, handAngle); })
      .AndThen(m_hand.Move(handAngle, CONSTANTS::EJECT))
      .WithTimeout(0.1_s);
}

bool RobotContainer::IsDeployed(
    units::angle::turn_t elbowAngle,
    units::angle::turn_t armAngle,
    units::angle::turn_t handAngle) {
    return m_elbow.IsMoveFinished(elbowAngle) && 
           m_arm.IsMoveFinished(armAngle)     && 
           m_hand.IsMoveFinished(handAngle);
}

frc2::CommandPtr RobotContainer::GetAutonomousCommand()
{
  return frc2::cmd::Print("No autonomous command configured");
}
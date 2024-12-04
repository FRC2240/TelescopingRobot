// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandPtr.h>
#include "subsystems/Arm.h"
#include "subsystems/Elbow.h"
#include "subsystems/Hand.h"
#include <frc2/command/button/CommandXboxController.h>
#include "Constants.h"

class RobotContainer
{
public:
  RobotContainer();

  frc2::CommandPtr GetAutonomousCommand();

  frc2::CommandPtr PickupCommand(
      units::angle::turn_t elbow,
      units::angle::turn_t arm,
      units::angle::turn_t hand);

  frc2::CommandPtr PlaceCommand(
      units::angle::turn_t elbow,
      units::angle::turn_t arm,
      units::angle::turn_t hand);
  
private:
  void ConfigureBindings();
  bool IsDeployed(
      units::angle::turn_t elbowAngle,
      units::angle::turn_t armAngle,
      units::angle::turn_t handAngle);

  frc2::CommandXboxController m_stick{0};
  
  Hand m_hand;
  Elbow m_elbow;
  Arm m_arm;
};

// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include "subsystems/Arm.h"
// #include "subsystems/Hand.h"
// #include "subsystems/Shoulder.h"
// #include "commands/MoveTo.h"
#include "Config.h"

#include <frc2/command/CommandPtr.h>
#include <frc2/command/button/CommandXboxController.h>


class RobotContainer {
 public:
  RobotContainer();

  frc2::CommandPtr GetAutonomousCommand();

  void SetPID();
  Arm m_arm;

 private:
  void ConfigureBindings();


  frc2::CommandXboxController m_stick{0};

  //Hand m_hand;
  //Shoulder m_shoulder;

  /*
  MoveTo* StowedCommand = new MoveTo(&m_arm, &m_hand, &m_shoulder, config::POSES::STOWED);

  MoveTo* PickupFloorCommand = new MoveTo(&m_arm, &m_hand, &m_shoulder, config::POSES::PICKUP_FLOOR);
  MoveTo* PickupSubstationCommand = new MoveTo(&m_arm, &m_hand, &m_shoulder, config::POSES::PICKUP_SUBSTATION);

  MoveTo* ScoreFloorCommand = new MoveTo(&m_arm, &m_hand, &m_shoulder, config::POSES::SCORE_FLOOR);
  MoveTo* ScoreMiddleCommand = new MoveTo(&m_arm, &m_hand, &m_shoulder, config::POSES::SCORE_MIDDLE);
  MoveTo* ScoreTopCommand = new MoveTo(&m_arm, &m_hand, &m_shoulder, config::POSES::SCORE_TOP);
  */
  
};

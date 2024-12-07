// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"

#include <frc2/command/Commands.h>
#include <iostream>

RobotContainer::RobotContainer()
{
  ConfigureBindings();
}

void RobotContainer::SetPID() {
  // m_arm.SetPID();
}

void RobotContainer::ConfigureBindings()
{

  // DO THIS NEXT
  /*
  m_stick.Button(1).OnTrue(ScoreTopCommand);
  m_stick.Button(2).OnTrue(StowedCommand);
  */

  // m_arm.SetDefaultCommand(m_arm.IdleCommand());
  m_stick.A().ToggleOnTrue(m_arm.ActiveCommand().AndThen(m_arm.IdleCommand()));
    // m_stick.B().ToggleOnTrue(m_arm.IdleCommand()).Debounce(20_ms);


}



frc2::CommandPtr RobotContainer::GetAutonomousCommand()
{
  return frc2::cmd::Print("No autonomous command configured");
}

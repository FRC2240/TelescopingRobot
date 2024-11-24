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

void RobotContainer::ConfigureBindings()
{

  // DO THIS NEXT
  m_stick.Button(1).OnTrue(ScoreTopCommand);
  m_stick.Button(2).OnTrue(StowedCommand);

}



frc2::CommandPtr RobotContainer::GetAutonomousCommand()
{
  return frc2::cmd::Print("No autonomous command configured");
}

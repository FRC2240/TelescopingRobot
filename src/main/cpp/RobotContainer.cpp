// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"
#include <frc2/command/Commands.h>
#include <frc2/command/button/CommandXboxController.h>


RobotContainer::RobotContainer() {
  ConfigureBindings();
}

void RobotContainer::ConfigureBindings() {
  m_arm.SetDefaultCommand(m_arm.IdleCommand());
  m_elbow.SetDefaultCommand(m_elbow.IdleCommand());
  m_hand.SetDefaultCommand(m_hand.IdleCommand());

  m_stick.A().ToggleOnTrue(m_arm.score_floor());
  m_stick.A().ToggleOnTrue(m_elbow.score_floor());
  m_stick.A().ToggleOnTrue(m_hand.score_floor());

  m_stick.B().ToggleOnTrue(m_arm.score_mid());
  m_stick.B().ToggleOnTrue(m_elbow.score_mid());
  m_stick.B().ToggleOnTrue(m_hand.score_mid());

  m_stick.Y().ToggleOnTrue(m_arm.score_high());
  m_stick.Y().ToggleOnTrue(m_elbow.score_high());
  m_stick.Y().ToggleOnTrue(m_hand.score_high());

  m_stick.LeftBumper().ToggleOnTrue(m_arm.PickupFloor());
  m_stick.LeftBumper().ToggleOnTrue(m_elbow.PickupFloor());
  m_stick.LeftBumper().ToggleOnTrue(m_hand.PickupFloor()r);

  m_stick.RightBumper().ToggleOnTrue(m_arm.pickup_subst());
  m_stick.RightBumper().ToggleOnTrue(m_elbow.pickup_subst());
  m_stick.RightBumper().ToggleOnTrue(m_hand.pickup_subst());

}

frc2::CommandPtr RobotContainer::GetAutonomousCommand() {
  return frc2::cmd::Print("No autonomous command configured");
}

// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/MoveTo.h"
#include <iostream>

MoveTo::MoveTo(Arm* arm, Hand* hand, Shoulder* shoulder, config::Pose pose) {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(arm);
  AddRequirements(shoulder);
  AddRequirements(hand);

  this->arm = arm;
  this->shoulder = shoulder;
  this->hand = hand;
  this->pose = pose;
}

// Called when the command is initially scheduled.
void MoveTo::Initialize() {
  arm->MoveTo(this->pose.armPosition);
  shoulder->MoveTo(this->pose.shoulderPosition);
  hand->MoveTo(this->pose.handPosition);
  hand->SetRollers(this->pose.rollerState);
}

// Called repeatedly when this Command is scheduled to run
void MoveTo::Execute() {}

// Called once the command ends or is interrupted.
void MoveTo::End(bool interrupted) {}

// Returns true when the command should end.
bool MoveTo::IsFinished() {
  return false;
}

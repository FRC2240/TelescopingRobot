// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include "Config.h"

#include <frc2/command/Command.h>
#include <frc2/command/CommandHelper.h>

#include "subsystems/Arm.h"
#include "subsystems/Hand.h"
#include "subsystems/Shoulder.h"

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending Command
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class MoveTo
    : public frc2::CommandHelper<frc2::Command, MoveTo>
{
public:
  MoveTo(Arm *arm, Hand *hand, Shoulder *shoulder, config::Pose pose);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

private:

  Arm* arm;
  Shoulder* shoulder;
  Hand* hand;

  config::Pose pose;

};

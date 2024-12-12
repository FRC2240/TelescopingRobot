#pragma once

#include <units/angle.h>
#include <units/angular_velocity.h>
#include <BetterSubsystemBase.h>

namespace config
{
  static constexpr char const *CANBUS_NAME = "rio";

  namespace ARM
  {
    constexpr int ARM_MOTOR_ID = 31;
    constexpr BetterSubsystemBase::PIDConfig ARM_MOTOR_PID {0.5, 10, 0.2, 1};
  }

  namespace SHOULDER
  {
    constexpr int SHOULDER_MOTOR_1_ID = 2;
    constexpr int SHOULDER_MOTOR_2_ID = 3;
  }

  namespace HAND
  {
    constexpr int ROLLER_MOTOR_ID = 4;
    constexpr int WRIST_MOTOR_ID = 5;
    constexpr int HAND_SENSOR_ID = 6;

    constexpr units::angular_velocity::turns_per_second_t ROLLER_EJECT_TR = -1_tps;
    constexpr units::angular_velocity::turns_per_second_t ROLLER_INTAKE_TR = 1_tps;

    constexpr BetterSubsystemBase::PIDConfig ROLLER_MOTOR_PID {0, 0, 0, 0};
    constexpr BetterSubsystemBase::PIDConfig WRIST_MOTOR_PID {0, 0, 0, 0};

    enum ROLLER_STATE
    {
      INTAKE,
      EJECT,
      NONE
    };
  }
  struct Pose
  {
    units::angle::turn_t armPosition;
    units::angle::turn_t shoulderPosition;
    units::angle::turn_t handPosition;

    HAND::ROLLER_STATE rollerState;
  };

  namespace POSES
  {
    const Pose STOWED{0_tr, 0_tr, 0_tr, HAND::ROLLER_STATE::NONE};

    const Pose PICKUP_FLOOR{1_tr, 1_tr, 1_tr, HAND::ROLLER_STATE::INTAKE};
    const Pose PICKUP_SUBSTATION{1_tr, 1_tr, 1_tr, HAND::ROLLER_STATE::INTAKE};

    const Pose SCORE_FLOOR{1_tr, 1_tr, 1_tr, HAND::ROLLER_STATE::EJECT};
    const Pose SCORE_MIDDLE{1_tr, 1_tr, 1_tr, HAND::ROLLER_STATE::EJECT};
    const Pose SCORE_TOP{1_tr, 1_tr, 1_tr, HAND::ROLLER_STATE::EJECT};
  }

}
